#ifndef CONNECTIONTREEINTERFACE_H
#define CONNECTIONTREEINTERFACE_H

#include "connectionmodel.h"
#include "abstractnetwork.h"
#include <QList>

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

    QAbstractListModel* getDataListQml() const;
signals:
    void dummyNotify();
    void authFailed(const QString &name,const QString &path,const QString &device);

private:
    void init();
    QList<AbstractNetwork*> m_networkTypeList;
    DeviceManager* m_devManager;
    ConnectionModel* m_model;
};

#endif // CONNECTIONTREEINTERFACE_H
