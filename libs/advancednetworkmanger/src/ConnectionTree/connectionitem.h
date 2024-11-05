#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QString>
#include <QVariant>
#include <QMap>

enum class ConType{Cable, Wifi};

class ConnectionItem
{
private:
    int uid;
public:
    QString Groupe;
    bool Stored;
    QString Name;
    QString NmPath;
    bool Available;
    int SignalStrength;
    ConType Type;
    bool Connected;
    QMap<QString, QVariant> Devices;
    QString Ipv4;
    friend class ConnectionList;
};

#endif // CONNECTIONITEM_H
