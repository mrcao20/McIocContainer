#include "include/Middleware/Transfer/impl/McControllerContainer.h"

#include <qdebug.h>
#include <qmetaobject.h>

#include "include/McIocBoot.h"
#include "include/ApplicationContext/IMcApplicationContext.h"
#include "include/Middleware/Utils/McRestResponse.h"
#include "include/Middleware/Utils/McJsonUtils.h"
#include "include/McIocBoot.h"

MC_DECLARE_PRIVATE_DATA(McControllerContainer)
QMap<QString, QSharedPointer<QObject>> controllers;	// 键为beanName，值为controller对象
MC_DECLARE_PRIVATE_DATA_END()

McControllerContainer::McControllerContainer(QObject *parent)
	: QObject(parent)
    , MC_NEW_PRIVATE_DATA(McControllerContainer)
{
}

McControllerContainer::~McControllerContainer(){
}

void McControllerContainer::init(const QSharedPointer<McIocBoot> &boot) noexcept {
    MC_D(McControllerContainer);
    auto appCtx = boot->getApplicationContext();
	auto beanNames = boot->getComponent(MC_CONTROLLER);
    for (const auto &beanName : beanNames) {
        auto obj = appCtx->getBean(beanName);
        if(!obj) {
            qCritical() << QString("controller for named '%1' not exists").arg(beanName);
            continue;
        }
        d->controllers.insert(beanName, obj);
    }
}

QVariant McControllerContainer::invoke(const QString &uri, const QVariant &body) noexcept {
    switch (static_cast<QMetaType::Type>(body.type())) {
    case QMetaType::Type::UnknownType:
        return invoke(uri);
    case QMetaType::Type::QJsonObject:
        return invoke(uri, body.toJsonObject());
    default:
        return McJsonUtils::responseToJson(McRestResponse<QString>::fail("请求体为不支持的类型"));
    }
}

QVariant McControllerContainer::invoke(const QString &uri) noexcept {
	auto list = uri.split('?', QString::SkipEmptyParts);
	if (list.isEmpty())
		return McJsonUtils::responseToJson(McRestResponse<QString>::fail("访问路径不存在"));
    QSharedPointer<QObject> bean;
    QString func;
    QJsonObject errRet;
    if(!splitBeanAndFunc(list.at(0), bean, func, errRet)) {
        return errRet;
    }
	QString param = list.size() == 2 ? list.at(1) : "";
    // <参数名，参数值>
	QMap<QString, QVariant> args = splitParam(param);
	return invokeForUri(bean, func, args);
}

QVariant McControllerContainer::invoke(const QString &uri, const QJsonObject &data) noexcept {
    QSharedPointer<QObject> bean;
    QString func;
    QJsonObject errRet;
    if(!splitBeanAndFunc(uri, bean, func, errRet)) {
        return errRet;
    }
    // <参数名，参数值>
	QMap<QString, QVariant> args = data.toVariantMap();
	return invokeForUri(bean, func, args);
}

bool McControllerContainer::splitBeanAndFunc(
        const QString &uri
        , QSharedPointer<QObject> &bean
        , QString &func
        , QJsonObject &errRet) noexcept {
    
    MC_D(McControllerContainer);
    auto beanAndFunc = uri.split('.', QString::SkipEmptyParts);
    if (beanAndFunc.size() != 2) {
        errRet = McJsonUtils::responseToJson(McRestResponse<QString>::fail("访问路径不存在"));;
        return false;
    }
    if(!d->controllers.contains(beanAndFunc.at(0))) {
        errRet = McJsonUtils::responseToJson(McRestResponse<QString>::fail("访问路径不存在"));
        return false;
    }
    bean = d->controllers[beanAndFunc.at(0)];
    func = beanAndFunc.at(1);
    return true;
}

QVariant McControllerContainer::invokeForUri(
        const QSharedPointer<QObject> &bean
        , const QString &func
        ,  const QMap<QString, QVariant> &args) noexcept {
    
	const QMetaObject *metaBean = bean->metaObject();
	int methodOffsetEnd = metaBean->methodOffset() + metaBean->methodCount();
	for (int i = metaBean->methodOffset(); i < methodOffsetEnd; ++i) {
		QMetaMethod method = metaBean->method(i);
		if(method.name() != func)
			continue;
		if (!isMethodMatching(method, args.keys()))
			continue;
		return invokeForArgs(bean, method, args);
	}
	return McJsonUtils::responseToJson(McRestResponse<QString>::fail("请求参数错误"));
}

QMap<QString, QVariant> McControllerContainer::splitParam(const QString &param) noexcept {
	QMap<QString, QVariant> args;
	QStringList params = param.split('&', QString::SkipEmptyParts);
	for (const auto &p : params) {
		QStringList nameAndValue = p.split('=', QString::SkipEmptyParts);
		if(nameAndValue.isEmpty())
			continue;
        QString key = nameAndValue.at(0);
        QVariant value;
        if(nameAndValue.size() == 2)
            value = nameAndValue.at(1);
        else
            value = "";
		args.insert(key, value);
	}
	return args;
}

bool McControllerContainer::isMethodMatching(const QMetaMethod &m, const QList<QString> &names) noexcept {
	QList<QByteArray> methodParamNames = m.parameterNames();
	if (methodParamNames.size() > names.size())
		return false;
	QList<QString> argNames = names;
	if (methodParamNames.size() == argNames.size()) {
        QList<QByteArray> list;
		removeDuplication(argNames, methodParamNames, list);
		if (methodParamNames.isEmpty())
			return true;
		else
			return false;
	}
	else {
		QList<QByteArray> methodParamTypes = m.parameterTypes();
		removeDuplication(argNames, methodParamNames, methodParamTypes);
		if (methodParamNames.isEmpty())
			return false;
		for (const QByteArray &type : methodParamTypes) {
			if (!type.endsWith('*'))
				return false;
			int typeId = QMetaType::type(type);
			if (typeId == QMetaType::UnknownType)
				return false;
			const QMetaObject *mobj = QMetaType::metaObjectForType(typeId);
			for (const QString &name : argNames) {
				if (mobj->indexOfProperty(name.toLocal8Bit()) == -1)
					continue;
				argNames.removeOne(name);
			}
		}
		if (argNames.isEmpty())
			return true;
		else
			return false;
	}
}

void McControllerContainer::removeDuplication(QList<QString> &argNames, QList<QByteArray> &paramNames, QList<QByteArray> &paramTypes) noexcept {
	for (int i = 0; i < paramNames.size(); ++i) {
		if (!argNames.contains(paramNames.at(i)))
			continue;
		argNames.removeOne(paramNames.at(i));
		paramNames.removeAt(i);
		paramTypes.removeAt(i);
		--i;
	}
}

QVariant McControllerContainer::invokeForArgs(const QSharedPointer<QObject> &bean, const QMetaMethod &method, const QMap<QString, QVariant> &args) noexcept {
    auto returnType = method.returnType();
    if(strcmp(method.typeName(), "QAbstractItemModel*") == 0) {
        returnType = QMetaType::type("QObject*");
    }
    if(returnType == QMetaType::Type::UnknownType) {
        qCritical() << "if you want to return a model to QML. the return type "
                       "must be QObject* or QAbstractItemModel*";
        return McJsonUtils::responseToJson(
                    McRestResponse<QString>::fail("无法在元对象系统中找到该返回值类型"));
    }
    QVariant returnValue(static_cast<QVariant::Type>(returnType));
	QGenericReturnArgument returnArg;
	if (method.returnType() == QMetaType::Void)
		returnValue = "调用成功";
    else {
        // 由于调用函数时需要对比类型名，所以这里类型名需要具体指定，不能再用QVariant
//		returnArg = Q_RETURN_ARG(QVariant, returnValue);
        returnArg = QGenericReturnArgument(method.typeName(), returnValue.data());
    }
	QVector<QGenericArgument> arguments;
	arguments.resize(10);
	
    bool ok = false;
    QVariant errMsg;
    auto values = makeValues(method, args, arguments.size(), &errMsg, &ok);
    if(!ok) {
        return errMsg;
    }
    for(int i = 0; i < values.size(); ++i) {
        // 由于Q_ARG宏所调用的函数是直接取value的地址，所以value不能是局部变量
//		arguments.replace(i, Q_ARG(QVariant, values[i]));
        /* 由于业务需要，调用函数的方式为直接连接，通过源代码分析，直接连接的类型名
         * 不需要使用，只需要保证它不为空即可
         */
        arguments.replace(i, QGenericArgument("QVariant", values[i].data()));
    }
	if (!method.invoke(bean.data(),
        Qt::DirectConnection, 
        returnArg,
        // 由于Q_ARG宏所调用的函数是直接取value的地址，所以value不能是局部变量
		arguments.at(0),
		arguments.at(1),
		arguments.at(2),
		arguments.at(3),
		arguments.at(4),
		arguments.at(5),
		arguments.at(6),
		arguments.at(7),
		arguments.at(8),
		arguments.at(9)))
		return McJsonUtils::responseToJson(McRestResponse<QString>::fail("函数调用失败"));
	return returnValue;
}

QVariantList McControllerContainer::makeValues(const QMetaMethod &method
                        , const QMap<QString, QVariant> &args
                        , int maxParamSize
                        , QVariant *errMsg
                        , bool *ok) noexcept {
    
    bool isOk = false;
    QVariant msg;
    if(ok == nullptr) {
        ok = &isOk;
    }
    if(errMsg == nullptr) {
        errMsg = &msg;
    }
    QList<QByteArray> paramNames = method.parameterNames(); // 和类型名数量一定相等
	QList<QByteArray> paramTypes = method.parameterTypes();
    if(paramTypes.size() > maxParamSize) {
        *errMsg = McJsonUtils::responseToJson(
                    McRestResponse<QString>::fail(
                        QString("函数参数个数不能大于%1").arg(maxParamSize)));
        *ok = false;
        return QVariantList();
    }
    QVariantList list;
	for (int i = 0; i < paramTypes.size(); ++i) {
		QByteArray type = paramTypes.at(i).simplified();
        QByteArray name = paramNames.at(i).simplified();
		QVariant value = args[name];     // 由于调用此函数时参数名一定存在，所以这里一定有值
		list.append(makeObjectValue(type, value));
	}
    *ok = true;
    return list;
}

QVariant McControllerContainer::makeObjectValue(const QByteArray &typeName, const QVariant &arg) noexcept {
    QByteArray objTypeName;
    if(!isSharedPointerObject(typeName, objTypeName)) {
        auto value = arg;
        value.convert(QMetaType::type(typeName));
        return value;
    }
    
	int typeId = QMetaType::type(objTypeName);
	if (typeId == QMetaType::UnknownType) {
		qCritical() << QString("类型名为%1的类没有注册!").arg(objTypeName.data());
		return QVariant();
	}
	const QMetaObject *mobj = QMetaType::metaObjectForType(typeId);
	QObject *obj = mobj->newInstance();
	int proOffsetEnd = mobj->propertyOffset() + mobj->propertyCount();
    auto args = arg.toMap();
	for (int i = mobj->propertyOffset(); i < proOffsetEnd; ++i) {
		QMetaProperty pro = mobj->property(i);
        auto name = pro.name();
		if(!args.contains(name))
			continue;
        auto value = args[name];
        value = makeObjectValue(pro.typeName(), value);
		if (!pro.write(obj, value))
			qCritical() << QString("类%1中的属性%2无法动态写入值").arg(objTypeName.data(), pro.name());
	}
    QSharedPointer<QObject> objPtr(obj);
    QVariant var;
    var.setValue(objPtr);
    var.convert(QMetaType::type(typeName));
	return var;
}

bool McControllerContainer::isSharedPointerObject(
        const QByteArray &typeName
        , QByteArray &objTypeName) noexcept {
    
    QByteArray prefix = "QSharedPointer<";
    QByteArray suffix = ">";
    if(typeName.startsWith(prefix) && typeName.endsWith(suffix)) {
        auto temp = typeName;
        temp.remove(0, prefix.size());
        temp.remove(temp.size() - suffix.size(), suffix.size());
        objTypeName = temp;
        return true;
    }
    return false;
}
