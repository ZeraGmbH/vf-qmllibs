#ifndef TIMEZONEBASEMODEL_H
#define TIMEZONEBASEMODEL_H

#include "abstracttimedate1connection.h"
#include "timedate1connection.h"
#include <QAbstractListModel>
#include <QList>
#include <memory>

class TimezoneBaseModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TimezoneBaseModel(std::shared_ptr<AbstractTimedate1Connection> timedateConnection =
                               std::make_shared<Timedate1Connection>());
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    enum Roles {
        TimezoneRole = Qt::UserRole,
    };

private slots:
    bool fillModel();
private:
    struct ModelEntry {
        QString m_timezone;
    };
    QList<ModelEntry> m_modelEntries;
    std::shared_ptr<AbstractTimedate1Connection> m_timedateConnection;
};

#endif // TIMEZONEBASEMODEL_H
