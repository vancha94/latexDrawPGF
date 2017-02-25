#include "abstractitem.h"



AbstractItem::AbstractItem()
{
    setBorderColor("Black");
    setBackgroundColor("White");


    fillHash();

}

void AbstractItem::setScenePosition(QPointF pos)
{
    scenePosition = pos;
}

//void AbstractItem::setSaturation(int saturation_)
//{
//    saturation = saturation_;
//}

void AbstractItem::setBorderColor(QString str)
{
    // borderColor = str;
    borderColor = QString(str);
    qDebug() <<str << borderColor;

}

void AbstractItem::setBackgroundColor(QString str)
{
    backgroundColor = str;
    qDebug() << str <<  backgroundColor;
}

void AbstractItem::setBorderAlpha(float value)
{
    borderAlpha = value;
}

void AbstractItem::setBackgroundAlpha(float value)
{
    backgroundAlpha = value;
}

void AbstractItem::setWidth(qreal value)
{
    width = widthHash[value];
}

void AbstractItem::setPen(const QPen &pen, QString str)
{
    setBorderColor(str);
    setWidth(pen.widthF());
}



void AbstractItem::fillHash()
{

    //    0,1	0,5
    //    0,2	1
    //    0,4	2
    //    0,6	3
    //    0,8	4
    //    1,2	6
    //    1,6	8
    widthHash[0.5] =  "ultra thin";
    widthHash[1]   =  "very thin";
    widthHash[2]   =  "thin";
    widthHash[3]   =  "semithick";
    widthHash[4]   =  "thick";
    widthHash[6]   =  "very thick";
    widthHash[8]   =  "ultra thick";
}
