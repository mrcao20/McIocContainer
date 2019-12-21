#pragma once

#include <QObject>

#include <qlist.h>

class IMcPropertyParser;

class McPropertyParserPlugins : public QObject {
	Q_OBJECT

    explicit McPropertyParserPlugins(QObject *parent = nullptr);
	Q_DISABLE_COPY(McPropertyParserPlugins)
public:
	~McPropertyParserPlugins();

	static McPropertyParserPlugins *getInstance() noexcept;

	void loadPlugin() noexcept;
	const QList<IMcPropertyParser *> &getParsers() const noexcept {
		return m_parsers;
	}

private:
	static McPropertyParserPlugins *instance;

	QList<IMcPropertyParser *> m_parsers;
};
