#ifndef POINTITEM_H
#define POINTITEM_H

#include <ellipseitem.h>


class PointItem: public EllipseItem
{
public:
    PointItem(EllipseItem *item =0);

    // EllipseItem interface
public:
    void setRect(qreal x, qreal y);
    void setRect(QPointF point);

private:
    qreal radius;
};

#endif // POINTITEM_H
