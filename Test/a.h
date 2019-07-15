#ifndef A_H
#define A_H

#include <QObject>

class A: public QObject
{
    Q_OBJECT
public:
    A();
    Q_INVOKABLE QString a();
};

#endif // A_H
