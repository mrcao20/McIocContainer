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
- 受QT自身插件系统性质影响，同一个插件在同一个程序中只能创建一次，即不能将同一个插件声明两次bean：
~~~
<bean plugin="p1"></bean>
<bean plugin="p1"></bean>
~~~
~~~
<bean plugin="p1"></bean>
<list plugins="包含文件p1的路径"></list>
~~~
即上面的用法是错误的，因为QT的插件在同一个程序中是单例的，这会造成多次析构同一个插件。但可以将同一个插件bean多处使用。
- 框架提供返回单个model的方法，但是返回的类型只能为QObject\*或者QAbstractItemModel\*，如果你需要一次性返回多个model，那么可以使用QT内建类型QVariantList或者QVariantMap来实现，即函数的返回值使用这两个中的任意一种。如果使用QVariantList，那么可以当做JS中的Array，如果使用QVariantMap，则可当做JS中的object
- getBean时生成的bean的生存线程问题。由于QT对线程的强控制，所以在getBean之后可能会存在线程冲突问题，所以容器内使用自动和手动指定线程的两种形式:
   1. 如果指定的目标线程为空，那么获取到的bean及其QObject属性都将生存在调用getBean时的线程中。注意: 
      - 这里的getBean指的是IMcBeanFactory的getBean，而不是IMcApplicationContext。因为IMcApplicationContext存在refresh函数自动加载bean，此时bean的生存线程将是调用refresh时的线程，如果不调用refresh，那么bean的生存线程才是getBean时的线程
      - 有如下形式: 
         1. 如果在次线程中创建appContext，如果在次线程中调用getBean，那么获取到的bean的线程为次线程。如果在主线程调用getBean，那么获取到的bean的线程为主线程。
         2. 如果在次线程中创建appContext，如果在次线程中调用了refresh函数，那么getBean获取到的bean的线程永远在次线程，反之，如果在主线程中调用refresh，那么bean的线程在主线程。
         3. 上面两种情况只适用于将isSingleton设置为true时的情况，如果isSingleton为false，那么每次调用getBean时都会创建一个新对象，此时获取到的bean就永远为调用getBean时的线程。
   2. 可以在调用getBean或refresh函数时指定一个目标线程，那么目标bean的生存线程将为指定的线程。同样的，只适用于isSingleton为true的情况。同时，如果isSingleton指定为true，但是在次线程中调用了refresh函数，就算在主线程中调用getBean时指定了目标线程也不会起作用，因为只能在对象创建时才能指定线程。
   3. 提供上面形式的线程指定方式的主要目的在于，如果XML中声明的对象结构过于复杂，对象的创建可能耗时太长，那么可以在子线程中完成创建，并且能指定目标线程。
  
# 2020-2-28
- 将原IOCContainer中的业务提取到AnnotationApplicationContext中
- 提供IocBoot和其静态函数run，以提供一个默认的QML到C++交互的方式：
   1. 在QML中提供一个名为$的请求器，并提供invoke函数的两种重载函数来请求Controller，invoke函数为C++函数，不可重写
   2. 在$中又提供了get和post两个函数以此封装invoke函数，这两个函数时js函数，可以重新赋值
   3. 以上函数的请求方式均为异步请求
   4. 以上函数的返回值为Response，可以调用then方法来获取请求结果。then方法接收一个js function，并通过一个参数表现其返回值。同时，由于QML自身性质限制，部分操作不能在其它线程，所以提供了一个同步版本的syncThen函数来让线程所有权回到主线程时再调用回调函数
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
   - 使用声明式方法为Mc::Ioc::connect("beanName", "property", "signal", "property", "slot")。第一个参数为某一个bean的beanName，其他参数使用方法和QObject::connect一致，只不过将具体的信号和槽换成字符串。值得注意的是，如果某一个property指定为this，则表示指定bean自身。
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
3. 同时，如果既指定了connect的属性，connect子节点的属性和connect子节点的包裹文本，那么优先级为connect子节点的包裹文本 \> connect子节点的属性 \> connect的属性。即如果使用以下形式，那么最终获得的值为bbb
~~~
<connect sender="this">
   <sender name="aaa">bbb</sender>
</connect>
~~~

# 另
- 现发现C++Model赋值到QML中的View的model并不是单纯的赋值操作，猜测这一步赋值其实是连接QML View和C++ Model相应的信号和槽，因为就算C++的Model处于另一个线程时亦可完成赋值操作，而且赋值完成后如果把C++的Model删除掉亦不会对QML的View造成崩溃性错误，就像QT/C++中的信号槽自然断开一样。

# 2019/12/22
- 此版本为重构版，主要将容器内的对象使用QSharedPointer动态指针包裹，并且也只能注入QSharedPointer类型。
- 每一个需要使用本容器的类都需要使用MC_DECLARE_METATYPE(Class)将Class添加进元对象系统，通常我们在一个类定义完成后面调用该宏来声明。
- 通常的，我们建议在每一个自定义类(包括接口)中都使用MC_DEFINE_TYPELIST宏来构建一个TypeList，以方便将最底层子类转换到它的每一个父类。该宏的参数为本类的所有基类和基类中的TypeList。例如：MC_DEFINE_TYPELIST(QObject, MC_TYPELIST(BaseClass))，BaseClass为自定义类型，如果BaseClass中包含TypeList，那么我们提供了MC_TYPELIST宏来方便同时声明基类和基类中的TypeList。同样的，需要在静态代码块中使用mcRegisterBeanFactory\<Class, Class::TypeList\>来注册，以方便本类只有转换到任何基类，同样的，我们提供了MC_DECL_TYPELIST来方便使用mcRegisterBeanFactory\<MC_DECL_TYPELIST(Class)\>。如果你能确定本类只会转换到固定基类，那么可以仍然使用原来的方式注册：mcRegisterBeanFactory\<Class, BaseClass\>.
- getBean返回QSharedPointer\<QObject\>类型，同时增加getBeanToQVariant接口，返回QVariant类型，QVariant中包含的对象为QSharedPointer\<Class\>类型，可以直接转换到QSharedPointer\<I\>类型。但是getBean返回的对象只能调用QSharedPointer::dynamicCast函数来转换到QSharedPointer\<I\>
- 增加注入QVariant功能，即可以使用QList\<QVariant\> m_list;或QVariant m_text;来注入QVariant类型。
- 增加指定单例的功能，如果使用声明式方式，则使用mcRegisterComponent函数的最后一个参数来指定，默认为true，表示该bean为单例。XML文件中同样提供此功能，在bean元素中指定isSingleton属性即可，如果不指定默认为true。例：\<bean name="hello" class="HelloWorld" isSingleton="false"\>

# 2020/3/3
- 增加QML到C++的长连接QmlSocket通信方式：
   1. C++端声明一个Component，并使用Q_CLASSINFO(MC_COMPONENT, MC_QML_SOCKET)附加额外属性。然后按照需求实现最多四个函数，并使用四种宏标志四个函数以接收各种消息，具体参照QmlSocketTest或者Java Spring WebSocket。注意：每一个函数的执行都是在另外的线程。
   2. QML端可以使用$.qs("beanName")来发起一个请求，该函数会返回一个对象，参照JS WebSocket。同时$.qs函数拥有第二个参数，可以直接指定onOpen等回调函数。同时因为部分界面操作不能在其他线程执行，所以$.qs的第二个参数中可以指定isOpenSync等参数来让某一个回调函数回到主线程后再执行。具体参照main.qml

# 后续
由于部分的接口和代码需要做调整，再加上后面的功能超出了IOC功能的范畴，所以整理过后的代码放在新仓库中<br/>
见新项目McQuickBoot
