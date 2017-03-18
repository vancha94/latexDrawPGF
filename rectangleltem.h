#ifndef RECTANGLELTEM_H
#define RECTANGLELTEM_H

#include <abstractshape.h>
#include <QGraphicsRectItem>

class Rectangleltem: public AbstractShape, public QGraphicsRectItem
{
public:
    Rectangleltem(QGraphicsItem* item=0);
    QString prepareText();
    void setPos(const QPointF &pos);
    void setVisible(bool visible);
    void setPen(const QPen &pen,ParamLines _params);
    void setRect(qreal x, qreal y, qreal width, qreal height);
    void setBrush(const QBrush &brush, ParamLines _params);
    void setCooordinats();



};

#endif // RECTANGLELTEM_H
