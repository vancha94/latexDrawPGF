#include "abstractitem.h"



ParamLines AbstractItem::getParams() const
{
    return params;
}

void AbstractItem::setParams(const ParamLines &value)
{
    params = value;
    setAllValues(params);
   // setAllValues(params);
}

QPen AbstractItem::getUserPen() const
{
    return userPen;
}

QBrush AbstractItem::getUserBrush() const
{
    return userBrush;
}

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

void AbstractItem::setBorderColor(QString str)
{
    borderColor = QString(str);
}

void AbstractItem::setBackgroundColor(QString str)
{
    backgroundColor = str;
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

void AbstractItem::setStyle(QString str)
{
    style = str;
}

void AbstractItem::setAllValues(ParamLines _params)
{
    params = _params;

    style = _params.style;
    backgroundColor = _params.backgroundCOlor;
    borderColor = _params.borderColor;
}

void AbstractItem::setPen(const QPen &pen, ParamLines _params)
{
    userPen = pen;
    setBorderColor(_params.borderColor);
    setWidth(pen.widthF());
    setBorderAlpha(pen.color().alphaF()*100);
    setAllValues(_params);
}

void AbstractItem::setBrush(const QBrush &brush, ParamLines _params)
{
    userBrush = brush;
    setBackgroundColor(_params.backgroundCOlor);
    setBackgroundAlpha(brush.color().alphaF()*100);
    setAllValues(_params);
}



QString AbstractItem::borderColorToText()
{
    return borderColor+"!"+QString::number(borderAlpha);
}

QString AbstractItem::backgroundColorToText()
{
     return backgroundColor+"!"+QString::number(backgroundAlpha);
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
