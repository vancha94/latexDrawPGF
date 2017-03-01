#include "lineitem.h"
#include <QDebug>
#include <QPen>

LineItem::LineItem(QGraphicsLineItem* item):
     AbstractItem(),QGraphicsLineItem(item)
{
    setCooordinats();
}


QString LineItem::prepareText()
{

    QString tmpStr;
    if(isVis)
    {
        auto tmp = points[1];
//        tmpStr = "\\draw[" + borderColor;
//        tmpStr+="!" +QString::number(borderAlpha) + ",";
//        tmpStr+= width +"] (";
        tmpStr = "\\draw";
        tmpStr+="["+paramToText() +"]";
        tmpStr+=" ("+QString::number(scenePosition.x())+",";
        tmpStr+=QString::number(-scenePosition.y())+") -- (";
        tmpStr+=QString::number(tmp.x()+scenePosition.x())+",";
        tmpStr+=QString::number(-(tmp.y()+scenePosition.y()))+");";
    }
    else tmpStr = "";
    return tmpStr;
}

void LineItem::setPos(const QPointF &pos)
{
    QGraphicsLineItem::setPos(pos);

    setCooordinats();


}

void LineItem::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
{
    // qDebug() << scenePos() << scenePosition;
    QGraphicsLineItem::setLine(x1,y1,x2,y2);
    setCooordinats();
   // qDebug() << scenePos() << scenePosition << points[0] << points[1];

}

void LineItem::setVisible(bool visible)
{
    QGraphicsLineItem::setVisible(visible);
    setCooordinats();
}

void LineItem::setPen(const QPen &pen, ParamLines _params)
{
    QGraphicsLineItem::setPen(pen);
    AbstractItem::setPen(pen,_params);


}

QString LineItem::paramToText()
{

        QString tmpStr="";

        tmpStr+= backgroundColorToText() + ",";
        tmpStr+= width +",";
        tmpStr+=style;


        return tmpStr;
}

void LineItem::setCooordinats()
{
    setScenePosition(scenePos());
    auto tmp = line();
    if (points.length())
        points.clear();
    points << tmp.p1() << tmp.p2();
    isVis = isVisible();
}
