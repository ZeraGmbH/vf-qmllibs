#ifndef TESTTIMEDATE1STORAGE_H
#define TESTTIMEDATE1STORAGE_H

#include <QObject>

class TestTimedate1Storage : public QObject
{
    Q_OBJECT
public:
    static TestTimedate1Storage* getInstance();

    static QString getTimezone();
    void setTimezone(const QString &timezone);
    Q_SIGNAL void sigTimezoneChanged();
    static void setInitialTimezone(const QString &timezone);

    static bool getNtpActive();
    void setNtpActive(bool active) ;
    Q_SIGNAL void sigNtpActiveChanged();

private:
    TestTimedate1Storage() = default;
    static QString m_timezone;
    static bool m_ntpActive;
    static TestTimedate1Storage* m_instance;
};

#endif // TESTTIMEDATE1STORAGE_H
