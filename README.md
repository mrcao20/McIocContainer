# McIocContainer_Qt
QtCreator项目,可直接跨平台编译

# 2019/12/22
- 此版本为重构版，主要将容器内的对象使用QSharedPointer动态指针包裹，并且也只能注入QSharedPointer类型。
- 每一个需要使用本容器的类都需要使用MC_DECLARE_METATYPE(Class)将Class添加进元对象系统，通常我们在一个类定义完成后面调用该宏来声明。
- 通常的，我们建议在每一个自定义类(包括接口)中都使用MC_DEFINE_TYPELIST宏来构建一个TypeList，以方便将最底层子类转换到它的每一个父类。该宏的参数为本类的所有基类和基类中的TypeList。例如：MC_DEFINE_TYPELIST(QObject, MC_TYPELIST(BaseClass))，BaseClass为自定义类型，如果BaseClass中包含TypeList，那么我们提供了MC_TYPELIST宏来方便同时声明基类和基类中的TypeList。同样的，需要在静态代码块中使用mcRegisterBeanFactory\<Class, Class::TypeList\>来注册，以方便本类只有转换到任何基类，同样的，我们提供了MC_DECL_TYPELIST来方便使用mcRegisterBeanFactory\<MC_DECL_TYPELIST(Class)\>。如果你能确定本类只会转换到固定基类，那么可以仍然使用原来的方式注册：mcRegisterBeanFactory\<Class, BaseClass\>.
- getBean返回QSharedPointer\<QObject\>类型，同时增加getBeanToQVariant接口，返回QVariant类型，QVariant中包含的对象为QSharedPointer\<Class\>类型，可以直接转换到QSharedPointer\<I\>类型。但是getBean返回的对象只能调用QSharedPointer::dynamicCast函数来转换到QSharedPointer\<I\>
- 增加注入QVariant功能，即可以使用QList\<QVariant\> m_list;或QVariant m_text;来注入QVariant类型。
- 增加指定单例的功能，如果使用声明式方式，则使用mcRegisterComponent函数的最后一个参数来指定，默认为true，表示该bean为单例。XML文件中同样提供此功能，在bean元素中指定isSingleton属性即可，如果不指定默认为true。例：\<bean name="hello" class="HelloWorld" isSingleton="false"\>
