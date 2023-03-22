#ifndef NOTIFICATIONMSG_H
#define NOTIFICATIONMSG_H

#include <QObject>
#include <QColor>
#include <memory>

class NotificationMsg : public QObject
{
    Q_OBJECT
public:
    NotificationMsg(QString msg);
    QString getMsg() const;
    int getId() const;

    Q_PROPERTY(QColor backGroundColor READ getBackGroundColor WRITE setBackGroundColor NOTIFY backGroundColorChanged)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QString text READ getMsg)
    Q_PROPERTY(int radius READ getRadius WRITE setRadius NOTIFY radiusChanged)
    //Q_PROPERTY(item anchorsCenter READ anchorsCenter WRITE setAnchorsCenter NOTIFY anchorsCenterChanged)
    Q_PROPERTY(int verticalAlignment READ verticalAlignment WRITE setVerticalAlignment NOTIFY verticalAlignmentChanged)
    Q_PROPERTY(int horizontalAlignment READ horizontalAlignment WRITE setHorizontalAlignment NOTIFY horizontalAlignmentChanged)

    QColor getBackGroundColor();
    QColor getBorderColor();
    QColor getTextColor();
    int getRadius();
    //item anchorsCenter();
    int verticalAlignment();
    int horizontalAlignment();

    void setBackGroundColor(QColor backGroundColor);
    void setBorderColor(QColor borderColor);
    void setTextColor(QColor textColor);
    void setRadius(int radius);
    void setVerticalAlignment(int verticalAlignment);
    void setHorizontalAlignment(int horizontalAlignment);
signals:
    void sigFadeOut(int id);

    void backGroundColorChanged();
    void borderColorChanged();
    void textColorChanged();
    void radiusChanged();
    void anchorsCenterChanged();
    void verticalAlignmentChanged();
    void horizontalAlignmentChanged();

protected:
    const int m_id;
private:
    const QString m_msg;

    QColor m_backGroundColor;
    QColor m_borderColor;
    QColor m_textColor;
    int m_radius;
    //item m_anchorsCenter;
    int m_verticalAlignment;
    int m_horizontalAlignment;
};

typedef std::shared_ptr<NotificationMsg> NotificationMsgPtr;

#endif // NOTIFICATIONMSG_H
