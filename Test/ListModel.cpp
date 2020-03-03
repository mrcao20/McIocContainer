#include "ListModel.h"

MC_STATIC(ListModel)
mcRegisterComponent<ListModel>("ListModel");
MC_STATIC_END()

ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_list << "aaaa"
           << "bbbb"
           << "cccccc";
}

int ListModel::rowCount(const QModelIndex &parent) const {
	return m_list.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	if (row < 0 || row >= m_list.size()) {
		return QVariant();
	}
	auto ret = m_list.at(row);
	switch (role) {
	case SongNameRole:
		return ret;
    }

	return QVariant();
}

QHash<int, QByteArray> ListModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[SongNameRole] = "songName";
	return roles;
}
