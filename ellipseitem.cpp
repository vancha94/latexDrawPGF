#include "ellipseitem.h"

EllipseItem::EllipseItem(QGraphicsItem *item)
    :AbstractShape(),QGraphicsEllipseItem(item)
{

}

QString EllipseItem::prepareText()
{
    qreal startX =scenePosition.x()+points[0].x();
    qreal startY = -(scenePosition.y()+points[0].y());
    qreal endX = scenePosition.x()+points[1].x()+points[0].x();
    qreal endY = -(scenePosition.y()+ points[1].y()+points[0].y());

    QString tmpStr = AbstractShape::prepareText();
    tmpStr+="("+QString::number((startX+endX)/2)+",";
    tmpStr+=QString::number((startY+endY)/2)+")";
    tmpStr+= " circle ";
    tmpStr+="[ x radius =";
    tmpStr+=QString::number((endX-startX)/2) +",";
    tmpStr+="y radius = ";
    tmpStr+=QString::number((startY-endY)/2)+"];";

    return isVis?tmpStr:"";

}

void EllipseItem::setPos(const QPointF &pos)
{
    QGraphicsEllipseItem::setPos(pos);
    setCooordinats();
}

void EllipseItem::setVisible(bool visible)
{
    QGraphicsEllipseItem::setVisible(visible);
    setCooordinats();
}

void EllipseItem::setPen(const QPen &pen, ParamLines _params)
{
    QGraphicsEllipseItem::setPen(pen);
    AbstractLine::setPen(pen,_params);
}

void EllipseItem::setRect(qreal x, qreal y, qreal width, qreal height)
{
    QGraphicsEllipseItem::setRect(x,y,width,height);
    setCooordinats();
}

void EllipseItem::setBrush(const QBrush &brush, ParamLines _params)
{
    QGraphicsEllipseItem::setBrush(brush);
    AbstractItem::setBrush(brush,_params);
}

void EllipseItem::setCooordinats()
{
     setScenePosition(scenePos());
      isVis = isVisible();
      auto tmp = rect();
      if (points.length())
          points.clear();
    points << QPointF(tmp.x(),tmp.y())
           << QPointF(tmp.width(),tmp.height());
}









