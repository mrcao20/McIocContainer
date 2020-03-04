#pragma once

#include <QAbstractListModel>

#include "ApplicationContext/McContainerGlobal.h"

class ListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_CLASSINFO(MC_COMPONENT, MC_MODEL)
    MC_DECL_STATIC(ListModel)
public:
    enum Roles {
        SongNameRole = Qt::UserRole + 1,
        AlbumNamesRole,
        ArtistNamesRole
    };
    Q_INVOKABLE ListModel(QObject *parent = 0);
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    
private:
    QStringList m_list;
};

MC_DECLARE_METATYPE(ListModel)
