#include "../include/McPropertyParserPlugins.h"

#include <QtCore/qcoreapplication.h>
#include <qmutex.h>
#include <qdir.h>
#include <qpluginloader.h>
#include <qdebug.h>

#include "../include/IMcPropertyParser.h"
#include "../include/IMcPropertyParserCollection.h"

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
	qDeleteAll(m_parsers);
	m_parsers.clear();
#ifdef Q_OS_ANDROID
    QDir pluginDir(qApp->applicationDirPath());
#elif defined(Q_OS_WIN)
    QDir pluginDir(qApp->applicationDirPath() + "/plugins/McIocContainer");
#endif
    QStringList pluginNames = pluginDir.entryList(QDir::Files);
	QPluginLoader loader;
	for (const QString &pluginName : pluginNames) {
		QString pluginPath = pluginDir.absoluteFilePath(pluginName);
		if (!QLibrary::isLibrary(pluginPath))
			continue;
		loader.setFileName(pluginPath);
		if (!loader.load()) {
			qWarning() << pluginPath << "cannot load!!";
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
