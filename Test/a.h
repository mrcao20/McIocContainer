#ifndef A_H
#define A_H

#include <QObject>

#include <functional>

#include <QSharedPointer>
#include <QJsonObject>
#include <QJSValue>

#include "ApplicationContext/McContainerGlobal.h"

class ReferenceBean;

class A: public QObject
{
    Q_OBJECT
    MC_DECL_STATIC(A)
public:
    Q_INVOKABLE A();
    ~A();
    Q_INVOKABLE QObject *a();
    Q_INVOKABLE QJsonObject b(const QJsonObject &o);
    Q_INVOKABLE void c(QJSValue func);
    QVariant bbb();
    
public slots:
    void slot_a();
    
private:
    
};

MC_DECLARE_METATYPE(A)

#endif // A_H
