#include "zpixmapitem.h"
#include <QUrl>

void ZPixmapItem::registerQml()
{
    qmlRegisterType<ZPixmapItem>("ZPixmapItem", 1, 0, "ZPixmapItem");
}

ZPixmapItem::ZPixmapItem(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

QString ZPixmapItem::getSource() const
{
    return m_source;
}

void ZPixmapItem::setSource(const QString &source)
{
    if (m_source != source) {
        m_source = source;
        QUrl url(source);
        m_pixmap = std::make_unique<QPixmap>(url.toLocalFile());

        emit sigSourceChanged();
        update();
    }
}

bool ZPixmapItem::getHCenter() const
{
    return m_hCenter;
}

void ZPixmapItem::setHCenter(bool hCenter)
{
    if (m_hCenter != hCenter) {
        m_hCenter = hCenter;

        emit sigHCenterChanged();
        update();
    }
}

void ZPixmapItem::paint(QPainter *painter)
{
    if (m_pixmap != nullptr && !m_pixmap->isNull()) {
        QRectF boundingRect = contentsBoundingRect();
        QSize boundingSize = boundingRect.size().toSize();
        QPixmap scaledPixmap = m_pixmap->scaled(boundingSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QSize scaledSize = scaledPixmap.size();

        int topLeftX = 0;
        if (m_hCenter)
            topLeftX = scaledSize.width() < boundingRect.width() ? (boundingRect.width() - scaledSize.width()) / 2 : 0;
        painter->drawPixmap(QPoint(topLeftX, 0), scaledPixmap);
    }
}
