#include "polylineitem.h"
#include <qpainter.h>

PolyLineItem::PolyLineItem(bool _isPencil, QGraphicsItem *lineItem)
    :AbstractLine(), QGraphicsPolygonItem(lineItem)
{
    isPencil = _isPencil;
    params.jointStyle = "miter";
}

PolyLineItem::~PolyLineItem()
{

}
// TODO: решить баг с повторением некоторых точек менее костыльно
QString PolyLineItem::prepareText()
{
    QString tmpStr="";
    tmpStr = "\\draw";
    tmpStr+="["+paramToText() +"]";
    if(points.size())
    {
        for(int i =0;i<points.size()-1;++i)
        {
            tmpStr+= "("+QString::number(scenePos().x()+ points[i].x()) + ",";
            tmpStr+= QString::number(-(scenePos().y()+ points[i].y()))+")";

            if(i!=points.size()-2)
                tmpStr+=" -- ";
        }
        tmpStr+= ";";
    }

    return isVis?tmpStr:"";
}

void PolyLineItem::setCooordinats()
{
  //  qDebug() <<flags();

    setScenePosition(scenePos());
    isVis = isVisible();

    auto tmp = polygon();
    if (points.length())
        points.clear();
    for(int i =0;i<polygon().size();++i)
        points << tmp[i];
}

void PolyLineItem::setVisible(bool visible)
{
    QGraphicsPolygonItem::setVisible(visible);
    setCooordinats();
}

void PolyLineItem::setPos(const QPointF &pos)
{
    QGraphicsPolygonItem::setPos(pos);
    setCooordinats();
}

void PolyLineItem::setParams(const ParamLines &value)
{
    AbstractLine::setParams(value);
    params = value;
}

void PolyLineItem::setPen(const QPen &pen, ParamLines _params)
{
    QGraphicsPolygonItem::setPen(pen);
    AbstractItem::setPen(pen,_params);
}

void PolyLineItem::setPolygon(const QPolygonF &polygon)
{
    QGraphicsPolygonItem::setPolygon(polygon);
    setCooordinats();
}


QString PolyLineItem::paramToText()
{
    //TODO: добавить необходимые параметры полиллинии
    if(isPencil)
        params.jointStyle = "round";
    QString tmpStr ="line join="+params.jointStyle+",";
    return  tmpStr+ AbstractLine::paramToText() ;
}

void PolyLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    painter->setBrush(Qt::NoBrush);
    painter->drawPolyline(polygon());
    if(flags() && isSelected())
    {
        painter->setPen(Qt::DashLine);
        painter->drawRect(boundingRect());
    }
}

QRectF PolyLineItem::boundingRect() const
{
    return  QGraphicsPolygonItem::boundingRect();
}

QPainterPath PolyLineItem::shape() const
{
    return QGraphicsPolygonItem::shape();
}
