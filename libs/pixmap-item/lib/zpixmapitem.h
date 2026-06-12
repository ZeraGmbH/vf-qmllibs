#ifndef ZPIXMAPITEM_H
#define ZPIXMAPITEM_H

#include <QQuickPaintedItem>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <memory>

class ZPixmapItem : public QQuickPaintedItem
{
    Q_OBJECT
public:
    static void registerQml();
    explicit ZPixmapItem(QQuickItem *parent = nullptr);
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sigSourceChanged)
    Q_PROPERTY(bool hCenter READ getHCenter WRITE setHCenter NOTIFY sigHCenterChanged)

    QString getSource() const;
    void setSource(const QString &source);

    bool getHCenter() const;
    void setHCenter(bool hCenter);
signals:
    void sigSourceChanged();
    void sigHCenterChanged();

private:
    void paint(QPainter *painter) override;

    QString m_source;
    std::unique_ptr<QPixmap> m_pixmap;
    bool m_hCenter = false;
};

#endif // ZPIXMAPITEM_H
