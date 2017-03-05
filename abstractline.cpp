#include "abstractline.h"

AbstractLine::AbstractLine()
    : AbstractItem()
{

}

QString AbstractLine::paramToText()
{
    QString tmpStr="";

    tmpStr+= backgroundColorToText() + ",";
    tmpStr+= width +",";
    tmpStr+=style;


    return tmpStr;
}

