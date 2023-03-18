#ifndef NMCPPNOTIFICATION_H
#define NMCPPNOTIFICATION_H

#include <QObject>
#include <QString>

class NmCppNotification : public QObject
{
    Q_OBJECT
public:
    explicit NmCppNotification(QObject *parent = nullptr);
    ~NmCppNotification();
    static void sendNotifiaction(QString p_head, QString p_text);
private:
   static NmCppNotification* m_exemplar;
signals:
    void notification(QString p_head, QString p_text);
};

#endif // NMCPPNOTIFICATION_H
