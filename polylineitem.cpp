#include "polylineitem.h"
#include <qpainter.h>

PolyLineItem::PolyLineItem(QGraphicsItemGroup *lineItem)
    :AbstractLine(), QGraphicsItemGroup(lineItem)
{

}

PolyLineItem::~PolyLineItem()
{

}

QString PolyLineItem::prepareText()
{
   QString tmpStr="";
   if(isVis)
   {
       // TODO: дописать преобразование координат
       tmpStr = "\\draw";
       tmpStr+="["+paramToText() +"]";
   }
   return tmpStr;
}

void PolyLineItem::setCooordinats()
{
    setScenePosition(scenePos());
    auto tmpList = childItems();
    if(points.length())
    {
        points.clear();
    }
    for(int i=0;i<tmpList.length();++i)
    {
       auto tmpLine = dynamic_cast<LineItem*>(tmpList[i]);
       points << tmpLine->line().p1();
        //points << tmpList[i]->
    }
    auto tmpSize = tmpList.size();
    points << dynamic_cast<LineItem*>(tmpList[tmpSize-1])->line().p2();
    isVis = isVisible();


}

void PolyLineItem::setVisible(bool visible)
{
    QGraphicsItemGroup::setVisible(visible);
    setCooordinats();
}

void PolyLineItem::setPos(const QPointF &pos)
{
    QGraphicsItemGroup::setPos(pos);
    setCooordinats();
}

void PolyLineItem::addItem(LineItem *item)
{
    lines.push_back(item);
     restorePoints();
     //paint();
}

void PolyLineItem::addToGroup(LineItem *item)
{
    QGraphicsItemGroup::addToGroup(item);
    if(points.size()!=0)
        points.remove(points.size()-1);
    points.push_back(item->line().p1());
    points.push_back(item->line().p2());
    //TODO: наладить нормальную взятие параметров (а то что-то не так)
    setParams(item->getParams());
    setPen(item->pen(),getParams());
   // params = item->getParams();

}

void PolyLineItem::setParams(const ParamLines &value)
{
    AbstractLine::setParams(value);
    params = value;
}

//void PolyLineItem::setPen(const QPen &pen, ParamLines _params)
//{
//    //QGraphicsItemGroup::setP
//}

QString PolyLineItem::paramToText()
{
    //TODO: добавить необходимые параметры полиллинии
    QString tmpStr ="";
    return  AbstractLine::paramToText() + tmpStr;
}



void PolyLineItem::restorePoints()
{

    if(points.size()!=0)
        points.remove(points.size()-1);
    auto sizeLines = lines.size()-1;
    points.push_back(lines[sizeLines]->line().p1());
    points.push_back(lines[sizeLines]->line().p2());


}

