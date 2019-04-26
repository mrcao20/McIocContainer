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
