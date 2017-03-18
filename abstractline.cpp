#include "abstractline.h"

AbstractLine::AbstractLine()
    : AbstractItem()
{

}

QString AbstractLine::paramToText()
{
    QString tmpStr="";

    tmpStr+= borderColorToText() + ",";
    tmpStr+= width +",";
    tmpStr+=style;
    return tmpStr;
}

