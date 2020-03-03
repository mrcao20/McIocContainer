#pragma once

#include <QObject>

#include <McMacroGlobal.h>
#include <ApplicationContext/McContainerGlobal.h>
#include <Middleware/Transfer/impl/qs/McSession.h>

class QmlSocketTest : public QObject {
    Q_OBJECT
    Q_CLASSINFO(MC_COMPONENT, MC_QML_SOCKET)
    MC_DECL_STATIC(QmlSocketTest)
public:
    Q_INVOKABLE explicit QmlSocketTest(QObject *parent = nullptr);
    ~QmlSocketTest();
    
    Q_INVOKABLE
    MC_ON_OPEN
    void onOpen(const QSharedPointer<McSession> &session) noexcept;
    
    Q_INVOKABLE
    MC_ON_CLOSE
    void onClose(const QSharedPointer<McSession> &session) noexcept;
    
    Q_INVOKABLE
    MC_ON_ERROR
    void onError(const QSharedPointer<McSession> &session) noexcept;
    
    Q_INVOKABLE
    MC_ON_MESSAGE
    void onMessage(const QSharedPointer<McSession> &session, const QString &msg) noexcept;
    
};

MC_DECLARE_METATYPE(QmlSocketTest)
