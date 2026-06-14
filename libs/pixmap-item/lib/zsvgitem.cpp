#include "zsvgitem.h"

void ZSvgItem::registerQml()
{
    qmlRegisterType<ZSvgItem>("ZSvgItem", 1, 0, "ZSvgItem");
}

ZSvgItem::ZSvgItem(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
}

QString ZSvgItem::getSource() const
{
    return m_source;
}

void ZSvgItem::setSource(const QString &source)
{
    if (m_source != source) {
        m_source = source;
        QUrl url(source);
        m_svgRenderer = std::make_unique<QSvgRenderer>(url.toLocalFile());

        emit sigSourceChanged();
        update();
    }
}

bool ZSvgItem::getHCenter() const
{
    return m_hCenter;
}

void ZSvgItem::setHCenter(bool hCenter)
{
    if (m_hCenter != hCenter) {
        m_hCenter = hCenter;

        emit sigHCenterChanged();
        update();
    }
}

void ZSvgItem::paint(QPainter *painter)
{
    if (m_svgRenderer != nullptr && m_svgRenderer->isValid()) {
        QRectF boundingRect = contentsBoundingRect();
        QSizeF boundingSize = boundingRect.size();
        QSizeF svgSize = m_svgRenderer->defaultSize();
        QSizeF svgSizeScaled = svgSize.scaled(boundingSize, Qt::KeepAspectRatio);

        double topLeftX = 0;
        if (m_hCenter)
            topLeftX = svgSizeScaled.width() < boundingRect.width() ? (boundingRect.width() - svgSizeScaled.width()) / 2 : 0;
        double topLeftY = 0;

        m_svgRenderer->render(painter, QRectF(topLeftX, topLeftY, svgSizeScaled.width(), svgSizeScaled.height()));
    }
}
