#include "timezonebasemodel.h"

TimezoneBaseModel::TimezoneBaseModel(std::shared_ptr<AbstractTimedate1Connection> timedateConnection) :
    m_timedateConnection(timedateConnection)
{
    if(!fillModel()) {
        connect(m_timedateConnection.get(), &AbstractTimedate1Connection::sigAvailTimezonesChanged,
                this, &TimezoneBaseModel::fillModel);
    }
}

QHash<int, QByteArray> TimezoneBaseModel::roleNames() const
{
    static QHash<int, QByteArray> roles {
        { TimezoneRole, "timezone" }
    };
    return roles;
}

int TimezoneBaseModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_modelEntries.count();
}

QVariant TimezoneBaseModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    if(row < 0 || row >= m_modelEntries.count())
        return QVariant();

    const ModelEntry &entry = m_modelEntries.at(row);

    switch(role) {
    case TimezoneRole:
        return entry.m_timezone;
    }
    return QVariant();
}

bool TimezoneBaseModel::fillModel()
{
    const QStringList availTimezones = m_timedateConnection->getAvailTimezones();
    if(availTimezones.isEmpty())
        return false;
    beginResetModel();
    m_modelEntries.clear();
    for(const QString &timezone : availTimezones) {
        ModelEntry entry;
        entry.m_timezone = timezone;

        m_modelEntries.append(entry);
    }
    endResetModel();
    return true;
}
