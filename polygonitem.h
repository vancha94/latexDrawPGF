#ifndef POLYGONITEM_H
#define POLYGONITEM_H


#include <abstractshape.h>
#include <QGraphicsPolygonItem>

class PolygonItem: public AbstractShape, public QGraphicsPolygonItem
{
public:
    PolygonItem(QGraphicsItem* item=0);
    QString prepareText();
    void setPos(const QPointF &pos);
    void setVisible(bool visible);
    void setPen(const QPen &pen,ParamLines _params);
    void setBrush(const QBrush &brush, ParamLines _params);
    void setCooordinats();
    void setPolygon(const QPolygonF &polygon);
};

#endif // POLYGONITEM_H
