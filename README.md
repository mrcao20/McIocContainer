# McIocContainer
基于QT的IOC容器

# 目前已有功能
- 通过xml文件注入：可以注入基本类型；引用类型；list系列容器(包括QList，QVector，QSet)，该系列容器可以只使用list标签，具体容器类型只需在bean中声明
(vector、set标签也能用，效果一样)
- 通过声明Component来自动注入

# 用法
- 在McBeanGlobal.h头文件下提供了MC_DECL_STATIC和MC_STATIC/MC_STATIC_END宏来实现类似于静态代码块的功能
~~~
.h
MC_DECL_STATIC(Test)
.cpp
MC_STATIC(Test)
mcRegisterComponent<Test *>("Test");
mcRegisterListConverter<QList<IHelloWorld *>>();
mcRegisterListConverter<QList<QList<IHelloWorld>>>();
MC_STATIC_END
~~~
上面三行代码将在进入主函数之前执行
- 上面代码中mcRegisterComponent为注册组件，被注册的组件将会被自动注入到内置容器McContainer中，如果不想使用自动注入，直接调用mcRegisterBeanFactory即
可，mcRegisterListConverter的作用是注册list系列容器的转换器，如果bean中使用的list系列的容器，如QList<int>，则需要将这个容器注册进框架中(只需注册一次)
也可以不使用静态代码块的方式注册，在main函数中McContainer容器初始化之前注册也行
- 在程序运行之前需要调用McContainer::getInstance()->initContainer();来初始化，所有自动注入的bean都在这个容器中
- 可以通过实现IMcPropertyParser或IMcPropertyParserCollection接口来实现对解析器的扩展，插件放在程序运行目录下plugins/McIocContainer目录中
- 如果类A实现了一个接口IA，而类B中使用的IA接口，则需要使用mcRegisterBeanFactory<A *, IA *>来注册A的转换，对应的组件方式注册为mcRegisterComponent<A *, IA *>

# 注意
- 不能存在一样的bean name，如果存在，则只会保留最后一个。在XML文件中最后面的为最后一个，但是用声明式方法时无法确保先后
- 不要声明一个beanName为this的bean
  
# 2020-2-28
- 将原IOCContainer中的业务提取到AnnotationApplicationContext中
- 提供IocBoot和其静态函数run，以提供一个默认的QML到C++交互的方式：
   1. 在QML中提供一个名为$的请求器，并提供invoke函数的两种重载函数来请求Controller，invoke函数为C++函数，不可重写
   2. 在$中又提供了get和post两个函数以此封装invoke函数，这两个函数时js函数，可以重新赋值
   3. 以上函数的请求方式均为异步请求
   4. 以上函数的返回值为Response，可以调用then方法来获取请求结果。then方法接收一个js function，并通过一个参数表现其返回值
   5. 通过以上方法请求Controller时可以传递包括QObject\*在内的任何QT元对象能获取到的类型。QObject\*对应js中的object。必须使用QSharedPointer\<QObject\>。同时返回值亦为所有类型，但建议只是用QString、QJsonObject、QObject*
   6. 请求方式为
   ~~~
   $.get("beanName.funcName?param1=1&param2=2")
   ~~~
   或者
   ~~~
   $.post("beanName.funcName", {
       param1: 1,
       param2: "2",
       param3: {
           param1: 1
       }
   })
   ~~~
   上面beanName为mcRegisterBeanFactory注册时的参数，funcName为Controller的函数，param1、param2、param3为函数的参数名，其后的值为将要赋值的参数值，其中param3将会被构造成一个QSharedPointer\<QObject\>
   
   7. Controller需要使用Q_CLASSINFO(MC_COMPONENT, MC_CONTROLLER)来声明

# 2020-2-29
1. 增加QObject信号槽的自动连接方式：
   - 使用声明式方法为Mc::Ioc::connect("property", "signal", "property", "slot")。使用方法和QObject::connect一致，只不过将具体的信号和槽换成字符串。但需要注意的是，如果某一个property指定为this，则代表当前对象本身。
   - 使用XML注入则可以使用多种格式：
   ~~~
   <connect>
     <sender>this</sender>
     <signal>signal_bean(QSharedPointer&lt;A&gt;)</signal>
     <receiver>helloWorld</receiver>
     <slot>slot_hello(QSharedPointer&gt;A&gt;)</slot>
     <ConnectionType>Qt::AutoConnection | Qt::UniqueConnection</ConnectionType>
   </connect>
   ~~~
   或者
   ~~~
   <connect>
     <sender name="this">this</sender>
     <signal name="signal_bean(QSharedPointer&lt;A&gt;)"></signal>
     <receiver name="helloWorld"></receiver>
     <slot name="slot_hello(QSharedPointer&gt;A&gt;)"></slot>
     <ConnectionType name="Qt::AutoConnection | Qt::UniqueConnection"></ConnectionType>
   </connect>
   ~~~
   甚至可以使用
   ~~~
   <connect sender="" signal="" receiver="" slot="" ConnectionType=""></connect>
   ~~~
   或者组合使用
2. 注意，无论使用哪种方式连接信号槽，都只能连接对象本身或者其拥有的属性
