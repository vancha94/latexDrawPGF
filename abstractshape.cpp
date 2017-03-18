#include "abstractshape.h"

AbstractShape::AbstractShape()
    :AbstractLine()
{

}

QString AbstractShape::prepareText()
{
    return "\\filldraw ["+paramToText()+"]";
}

QString AbstractShape::paramToText()
{
    QString tmpStr = "";
    tmpStr+="fill=";
    tmpStr+=backgroundColorToText()+",";
    tmpStr+="draw=";
    tmpStr+= AbstractLine::paramToText();
    return tmpStr;
    // fill = green!50,draw=BrickRed!100,thin,dashed
}
