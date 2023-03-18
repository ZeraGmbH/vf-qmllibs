#ifndef CONNECTIONTREEINTERFACE_H
#define CONNECTIONTREEINTERFACE_H


#include <QObject>
#include <QList>
#include <QMap>
#include <QString>
#include <QVariant>


#include <QLatin1String>

#include <NetworkManagerQt/ActiveConnection>
#include <NetworkManagerQt/Connection>
#include <NetworkManagerQt/ConnectionSettings>
#include <NetworkManagerQt/Manager>
#include <NetworkManagerQt/Settings>
#include <NetworkManagerQt/Manager>


#include <NetworkManagerQt/Setting>

#include <QtCore/QUuid>
#include <QQueue>

#include <NetworkManagerQt/Utils>

#include <iostream>

#include <globalDefines.h>
#include <connectionmodel.h>
#include <QList>

#include "abstractnetwork.h"

class ConModelItem;
class StoredNetworks;
class ActiveNetworks;
class DeviceManager;

/**
 * @brief The ConnectionTreeInterface class
 *
 * This class connects the qml part with the C++ part.
 * Offers the
 */
class ConnectionTreeInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel* dataList READ getDataListQml NOTIFY dataListChanged)
public:
    ConnectionTreeInterface(QObject* paretn = nullptr);

    void init();
    void reinit();


    Q_INVOKABLE void removeConnection(QString path);

    Q_INVOKABLE QList<QString> getDevices(int p_type);
    Q_INVOKABLE QString getDevice(QString p_connection);

    Q_INVOKABLE void connect(QString p_conPath, QString p_devPath,bool force = true);
    Q_INVOKABLE void disconnect(QString p_conPath);




//    QList<QObject*> getDataList() const;
    QAbstractListModel* getDataListQml() const;


private:
    QList<AbstractNetwork*> m_networkTypeList;

    DeviceManager* m_devManager;
    ConnectionModel* m_model;
signals:
    void dataListChanged();
    void authFailed(const QString &name,const QString &path,const QString &device);
};

#endif // CONNECTIONTREEINTERFACE_H
