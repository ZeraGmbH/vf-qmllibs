#ifndef TIMEDATE1CONNECTION_H
#define TIMEDATE1CONNECTION_H

#include "timedate1interface.h"

class Timedate1Connection : public QObject
{
    Q_OBJECT
public:
    Timedate1Connection();
    void connectDbus();
signals:
    void sigConnected(bool connected);

private:
    std::unique_ptr<org::freedesktop::timedate1> m_timedateInterface;
    QStringList m_timezones;
};

#endif // TIMEDATE1CONNECTION_H
