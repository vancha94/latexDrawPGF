#ifndef ELLIPSEITEM_H
#define ELLIPSEITEM_H

#include <abstractshape.h>
#include <QGraphicsEllipseItem>


class EllipseItem: public AbstractShape, public QGraphicsEllipseItem
{
public:
    EllipseItem(QGraphicsItem* item=0);
    QString prepareText();
    void setPos(const QPointF &pos);
    void setVisible(bool visible);
    void setPen(const QPen &pen,ParamLines _params);
    void setRect(qreal x, qreal y, qreal width, qreal height);
    void setBrush(const QBrush &brush, ParamLines _params);
    void setCooordinats();
};

#endif // ELLIPSEITEM_H
