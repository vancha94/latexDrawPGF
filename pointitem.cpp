#include "pointitem.h"

PointItem::PointItem(EllipseItem *item)
    :EllipseItem(item)
{
  radius = 20;
}

void PointItem::setRect(qreal x, qreal y)
{
    x -= radius/2;
    y -= radius/2;
    EllipseItem::setRect(x,y,radius,radius);
}

void PointItem::setRect(QPointF point)
{
    setRect(point.x(),point.y());
}
