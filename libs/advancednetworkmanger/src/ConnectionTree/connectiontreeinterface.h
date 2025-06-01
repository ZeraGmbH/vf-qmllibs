#ifndef CONNECTIONTREEINTERFACE_H
#define CONNECTIONTREEINTERFACE_H

#include "connectionmodel.h"
#include "abstractnetwork.h"
#include <QList>
#include <memory>

/**
 * @brief The ConnectionTreeInterface class
 *
 * This class connects the qml part with the C++ part.
 * Offers the
 */
class ConnectionTreeInterface : public QObject
{
    Q_OBJECT
public:
    ConnectionTreeInterface(QObject* paretn = nullptr);
    Q_PROPERTY(QAbstractListModel* dataList READ getDataListQml NOTIFY dummyNotify)
    Q_INVOKABLE void removeConnection(QString path);
    Q_INVOKABLE QList<QString> getDevices(int p_type);
    Q_INVOKABLE QString getDevice(QString p_connection);
    Q_INVOKABLE void connect(QString p_conPath, QString p_devPath,bool force = true);
    Q_INVOKABLE void disconnect(QString p_conPath);

    QAbstractListModel* getDataListQml();
signals:
    void dummyNotify();
    void authFailed(const QString &name,const QString &path,const QString &device);

private:
    QList<std::shared_ptr<AbstractNetwork>> m_networkTypeList;
    std::shared_ptr<DeviceManager> m_devManager;
    ConnectionModel m_model;
};

#endif // CONNECTIONTREEINTERFACE_H
