#ifndef TESTTIMEDATE1STORAGE_H
#define TESTTIMEDATE1STORAGE_H

#include <QObject>

class TestTimedate1Storage : public QObject
{
    Q_OBJECT
public:
    static TestTimedate1Storage* getInstance();

    QString getTimezone() const;
    void setTimezone(const QString &timezone);
    Q_SIGNAL void sigTimezoneChanged();
    static void setInitialTimezone(const QString &timezone);

    bool getNtpActive() const;
    void setNtpActive(bool active) ;
    Q_SIGNAL void sigNtpActiveChanged();

private:
    TestTimedate1Storage() = default;
    static QString m_timezone;
    static bool m_ntpActive;
    static TestTimedate1Storage* m_instance;
};

#endif // TESTTIMEDATE1STORAGE_H
