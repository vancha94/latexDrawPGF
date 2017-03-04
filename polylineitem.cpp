#include "polylineitem.h"

PolyLineItem::PolyLineItem(QGraphicsItemGroup *groupItem, QGraphicsLineItem *lineItem)
    :LineItem(lineItem),QGraphicsItemGroup(groupItem)
{

}

PolyLineItem::~PolyLineItem()
{

}

QString PolyLineItem::prepareText()
{

}

void PolyLineItem::setCooordinats()
{

}

QString PolyLineItem::paramToText()
{
    //TODO: добавить необходимые параметры полиллинии
    QString tmpStr ="";
    return LineItem::paramToText() + tmpStr;
}
