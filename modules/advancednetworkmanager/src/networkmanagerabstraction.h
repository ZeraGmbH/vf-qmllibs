#ifndef NETWORKMANAGERABSTRACTION_H
#define NETWORKMANAGERABSTRACTION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <NetworkManagerQt/Manager>

class NetworkmanagerAbstraction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList aps READ getAvailableSsids() NOTIFY apsChanged)

public:
    NetworkmanagerAbstraction(QObject *parent = nullptr);
    ~NetworkmanagerAbstraction();
public:
    Q_INVOKABLE QStringList getAvailableSsids();
    Q_INVOKABLE void realoadConnections();
signals:
    void apsChanged();
};

#endif // NETWORKMANAGERABSTRACTION_H
