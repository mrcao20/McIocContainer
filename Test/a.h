#ifndef A_H
#define A_H

#include <QObject>
#include <QSharedPointer>

class ReferenceBean;

class A: public QObject
{
    Q_OBJECT
public:
    A();
    Q_INVOKABLE QString a();
    QVariant bbb();
};

#endif // A_H
