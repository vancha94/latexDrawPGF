#include "polygonitem.h"

PolygonItem::PolygonItem(QGraphicsItem *item)
    :AbstractShape(),QGraphicsPolygonItem(item)
{

}

QString PolygonItem::prepareText()
{


    QString tmpStr = "\\filldraw ["+AbstractShape::paramToText() + ",";
    tmpStr+="even odd rule]";
    if(points.size())
    {


        for(int i =0;i<points.size();++i)
        {
            tmpStr+= "("+QString::number(points[i].x()) + ",";
            tmpStr+= QString::number(-points[i].y())+") -- ";
        }

        tmpStr+= "("+QString::number(points[0].x()) + ",";
        tmpStr+= QString::number(-points[0].y())+");";
    }
    return isVis?tmpStr:"";
}

void PolygonItem::setPos(const QPointF &pos)
{
    QGraphicsPolygonItem::setPos(pos);
    setCooordinats();

}

void PolygonItem::setVisible(bool visible)
{
    QGraphicsPolygonItem::setVisible(visible);
    setCooordinats();
}

void PolygonItem::setPen(const QPen &pen, ParamLines _params)
{
    QGraphicsPolygonItem::setPen(pen);
    AbstractLine::setPen(pen,_params);
}



void PolygonItem::setBrush(const QBrush &brush, ParamLines _params)
{
    QGraphicsPolygonItem::setBrush(brush);
    AbstractItem::setBrush(brush,_params);
}

void PolygonItem::setCooordinats()
{
    setScenePosition(scenePos());
    isVis = isVisible();

    auto tmp = polygon();
    if (points.length())
        points.clear();
    for(int i =0;i<polygon().size();++i)
        points << tmp[i];


}

void PolygonItem::setPolygon(const QPolygonF &polygon)
{
    QGraphicsPolygonItem::setPolygon(polygon);
    setCooordinats();

}
