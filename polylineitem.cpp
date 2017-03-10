#include "polylineitem.h"
#include <qpainter.h>

PolyLineItem::PolyLineItem(QGraphicsPathItem *lineItem)
    :AbstractLine(), QGraphicsPathItem(lineItem)
{
    isFirstLine = true;
    params.jointStyle = "miter";
}

PolyLineItem::~PolyLineItem()
{

}

QString PolyLineItem::prepareText()
{
    QString tmpStr="";
    if(isVis)
    {

        tmpStr = "\\draw";
        tmpStr+="["+paramToText() +"]";
        tmpStr+=" (" + QString::number(scenePosition.x())+",";
        tmpStr+=QString::number(-scenePosition.y())+") ";
        {
            for(int i=0; i<points.size();++i)
            {
                tmpStr += "-- ++("+ QString::number(points[i].x()) + ",";
                tmpStr += QString::number(-points[i].y()) + ")";
            }
            tmpStr +=";";
        }
    }
    return tmpStr;
}

void PolyLineItem::setCooordinats()
{
    setScenePosition(scenePos());
    if(points.size())
    {
        points.clear();
    }
    for(int i=0;i<lines.size();i++)
    {
        QPointF tmpPoint;
        tmpPoint.setX(lines[i]->line().dx());
        tmpPoint.setY(lines[i]->line().dy());
        points.push_back(tmpPoint);
    }
    isVis = isVisible();



}

void PolyLineItem::setVisible(bool visible)
{
    QGraphicsPathItem::setVisible(visible);
    setCooordinats();
}

void PolyLineItem::setPos(const QPointF &pos)
{
    QGraphicsPathItem::setPos(pos);
    setCooordinats();
}



void PolyLineItem::addToGroup(LineItem *item)
{
    if(points.size()==0)
        setPos(item->scenePos());


    setParams(item->getParams());
    setPen(item->pen(),getParams());
    lines.push_back(item);
    setPath(_path);

}

void PolyLineItem::setParams(const ParamLines &value)
{
    AbstractLine::setParams(value);
    params = value;
}

void PolyLineItem::setPen(const QPen &pen, ParamLines _params)
{
    QGraphicsPathItem::setPen(pen);
    AbstractItem::setPen(pen,_params);
}

void PolyLineItem::drawOneLine(bool isEnd)
{
    QPainterPath tmpPath;
    QPointF currentPositionPath;
       //  костыль для решения бага с измнением позиции сцены при рисовании второй линии
    if(_path.isEmpty())
        scenPosTmp = scenePos();
    else if(_path.elementCount()==2)
         setPos(scenPosTmp);
   if(!_path.isEmpty())
    {
        tmpPath = _path;
        currentPositionPath =tmpPath.currentPosition();
    }
    if(lines.size())
    {
        auto tmpIndex = lines.size()-1;
        auto tmpLine = lines[tmpIndex]->line();
        QPointF tmpPoint = QPointF(tmpLine.dx(),tmpLine.dy());
        tmpPath.lineTo(currentPositionPath+tmpPoint);;
        if(isEnd)
        {
            QPainterPath::Element pathElement;
            if(!_path.isEmpty())
              pathElement = _path.elementAt(_path.elementCount());
            auto tmpElement = tmpPath.elementAt(tmpPath.elementCount());
            if(pathElement!=tmpElement)
            _path = tmpPath;
            setPath(_path);
             return;
        }
           setPath(tmpPath);
    }


}


QString PolyLineItem::paramToText()
{
    //TODO: добавить необходимые параметры полиллинии
    QString tmpStr ="line join="+params.jointStyle+",";
    return  tmpStr+ AbstractLine::paramToText() ;
}





