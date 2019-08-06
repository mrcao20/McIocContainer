#include "../include/McPropertyParserPlugins.h"

#include <QtCore/qcoreapplication.h>
#include <qmutex.h>
#include <qdir.h>
#include <qpluginloader.h>
#include <qdebug.h>

#include "../include/IMcPropertyParser.h"
#include "../include/IMcPropertyParserCollection.h"
#include "./McParserPlugin/McPropertyParsers.h"

McPropertyParserPlugins *McPropertyParserPlugins::instance = nullptr;

McPropertyParserPlugins::McPropertyParserPlugins(QObject *parent)
	: QObject(parent)
#ifdef MC_STATIC_BUILD
    , m_parserCollection(new McPropertyParsers(this))
#endif
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
	qDeleteAll(m_parsers);
	m_parsers.clear();
#ifdef MC_STATIC_BUILD
    loadFromStatic();
#elif
    loadFromShared();
#endif
}

#ifdef MC_STATIC_BUILD
void McPropertyParserPlugins::loadFromStatic() noexcept{
    m_parsers = m_parserCollection->customParsers();
}
#elif
void McPropertyParserPlugins::loadFromShared() noexcept{
#ifdef Q_OS_ANDROID
    QDir pluginDir(qApp->applicationDirPath());
#elif defined(Q_OS_WIN) || defined(Q_OS_LINUX)
    QDir pluginDir(qApp->applicationDirPath() + "/plugins/McIocContainer");
#endif
    QStringList pluginNames = pluginDir.entryList(QDir::Files);
    QPluginLoader loader;
    for (const QString &pluginName : pluginNames) {
        QString pluginPath = pluginDir.absoluteFilePath(pluginName);
        if (!QLibrary::isLibrary(pluginPath)){
            qInfo() << pluginPath << "is not a library";
            continue;
        }
        loader.setFileName(pluginPath);
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
                m_parsers.append(parser);
        }
    }
}
#endif
