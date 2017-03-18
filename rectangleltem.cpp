#include "rectangleltem.h"

Rectangleltem::Rectangleltem(QGraphicsItem *item)
    :AbstractShape(),QGraphicsRectItem(item)
{

}

QString Rectangleltem::prepareText()
{
    QString tmpStr = AbstractShape::prepareText();
    tmpStr += "("+QString::number(scenePosition.x())+",";
    tmpStr += QString::number(-scenePosition.y()) + ")";
    tmpStr += "rectangle";
    tmpStr += "(" + QString::number(points[1].y()) +",";
    tmpStr += QString::number(-points[1].x()) + ");";
    return tmpStr;
}

void Rectangleltem::setPos(const QPointF &pos)
{
    QGraphicsRectItem::setPos(pos);
    setCooordinats();

}

void Rectangleltem::setVisible(bool visible)
{
    QGraphicsRectItem::setVisible(visible);
    setCooordinats();
}

void Rectangleltem::setPen(const QPen &pen, ParamLines _params)
{
    QGraphicsRectItem::setPen(pen);
    AbstractLine::setPen(pen,_params);
}

void Rectangleltem::setRect(qreal x, qreal y, qreal width, qreal height)
{
    QGraphicsRectItem::setRect(x,y,width,height);
    setCooordinats();

}

void Rectangleltem::setBrush(const QBrush &brush, ParamLines _params)
{
    QGraphicsRectItem::setBrush(brush);
    AbstractItem::setBrush(brush,_params);
}

void Rectangleltem::setCooordinats()
{
    setScenePosition(scenePos());
    auto tmp = rect();
    if (points.length())
        points.clear();
  points << QPointF(tmp.x(),tmp.y())
         << QPointF(tmp.width(),tmp.height());
    isVis = isVisible();
}
