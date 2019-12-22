# McIocContainer_Qt
QtCreator项目,可直接跨平台编译

# 2019/12/22
- 此版本为重构版，主要将容器内的对象使用QSharedPointer动态指针包裹，并且也只能注入QSharedPointer类型。
- getBean返回QSharedPointer<QObject>类型，同时增加getBeanToQVariant接口，返回QVariant类型，QVariant中包含的对象为QSharedPointer<Class>类型，可以直接转换到QSharedPointer<I>类型。但是getBean返回的对象只能调用QSharedPointer::dynamicCast函数来转换到QSharedPointer<I>
- 增加注入QVariant功能，即可以使用QList<QVariant> m_list;或QVariant m_text;来注入QVariant类型。
- 增加指定单例的功能，如果使用声明式方式，则使用mcRegisterComponent函数的最后一个参数来指定，默认为true，表示该bean为单例。XML文件中同样提供此功能，在bean元素中指定isSingleton属性即可，如果不指定默认为true。例：<bean name="hello" class="HelloWorld" isSingleton="false">
