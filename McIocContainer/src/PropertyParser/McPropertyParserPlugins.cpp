#include "include/PropertyParser/McPropertyParserPlugins.h"

#include <QtCore/qcoreapplication.h>
#include <qmutex.h>
#include <qdir.h>
#include <qpluginloader.h>
#include <qdebug.h>

#include "include/PropertyParser/IMcPropertyParser.h"
#include "include/PropertyParser/IMcPropertyParserCollection.h"

McPropertyParserPlugins *McPropertyParserPlugins::instance = nullptr;

McPropertyParserPlugins::McPropertyParserPlugins(QObject *parent)
    : QObject(parent)
{
}

McPropertyParserPlugins::~McPropertyParserPlugins(){
}

McPropertyParserPlugins *McPropertyParserPlugins::getInstance() noexcept {
    static QMutex mtx;
    if (!instance) {
        QMutexLocker locker(&mtx);
        if (!instance) {
            instance = new McPropertyParserPlugins(qApp);
        }
    }
    return instance;
}

void McPropertyParserPlugins::loadPlugin() noexcept {
    m_parsers.clear();
#ifdef Q_OS_ANDROID
    QString pluginsPath = qApp->applicationDirPath();
#elif defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    QString pluginsPath = qApp->applicationDirPath() + "/plugins/McIocContainer";
#endif
    qDebug() << "load plugins from:" << pluginsPath;
    QDir pluginDir(pluginsPath);
    QStringList pluginNames = pluginDir.entryList(QDir::Files);
    QStringList loadedPluginNames;
    QPluginLoader loader;
    for (const QString &pluginName : pluginNames) {
        QString pluginPath = pluginDir.absoluteFilePath(pluginName);
        qDebug() << "the bean parser plugin path:" << pluginPath;
        if (!QLibrary::isLibrary(pluginPath)){
            qInfo() << pluginPath << "is not a library";
            continue;
        }
        loader.setFileName(pluginPath);
        QString targetPluginPath = loader.fileName();
        if(loadedPluginNames.contains(targetPluginPath)) {
            qWarning() << "the plugin:" << targetPluginPath << "is loaded";
            continue;
        }
        loadedPluginNames.append(targetPluginPath);
        if (!loader.load()) {
            qWarning() << pluginPath << "cannot load!!" << "the error string is:" << loader.errorString();
            continue;
        }
        QObject *obj = loader.instance();
        if (!obj) {
            qWarning() << pluginPath << "cannot instanced to QObject!!";
            continue;
        }
        IMcPropertyParserCollection *parsers = qobject_cast<IMcPropertyParserCollection *>(obj);
        if (parsers) {
            m_parsers.append(parsers->customParsers());
        }
        else {
            IMcPropertyParser *parser = qobject_cast<IMcPropertyParser *>(obj);
            if(parser)
                m_parsers.append(QSharedPointer<IMcPropertyParser>(parser));
        }
        loader.unload();    // Ð¶ÔØ²¢Îö¹¹²å¼þ
    }
}
