#include "rectangleltem.h"

Rectangleltem::Rectangleltem(QGraphicsItem *item)
    :AbstractShape(),QGraphicsRectItem(item)
{

}

QString Rectangleltem::prepareText()
{
    // qDebug() << points << scenePosition;
    qreal startX =scenePosition.x()+points[0].x();
    qreal startY = -(scenePosition.y()+points[0].y());
    qreal endX = scenePosition.x()+points[1].x()+points[0].x();
    qreal endY = -(scenePosition.y()+ points[1].y()+points[0].y());

    QString tmpStr = AbstractShape::prepareText();
    tmpStr += "("+QString::number(startX)+",";
    tmpStr += QString::number(startY) + ")";
    tmpStr += "rectangle";
    tmpStr += "(" + QString::number(endX) +",";
    tmpStr += QString::number(endY) + ");";
    return isVis?tmpStr:"";
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
