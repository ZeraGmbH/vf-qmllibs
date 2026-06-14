#ifndef ZSVGITEM_H
#define ZSVGITEM_H

#include <QQuickPaintedItem>
#include <QSvgRenderer>

class ZSvgItem : public QQuickPaintedItem
{
    Q_OBJECT
public:
    static void registerQml();
    ZSvgItem(QQuickItem *parent = nullptr);

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
    std::unique_ptr<QSvgRenderer> m_svgRenderer;
    bool m_hCenter = false;
};

#endif // ZSVGITEM_H
