#include "polylineitem.h"
#include <qpainter.h>

PolyLineItem::PolyLineItem(QGraphicsPathItem *lineItem)
    :AbstractLine(), QGraphicsPathItem(lineItem)
{
    //    QBrush tmpBrush;
    //    tmpBrush.set
    i=0;
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
        //int j = i;
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
    // QGraphicsItemGroup::addToGroup(item);
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
    // TODO: додумать, что тут писать
    QPainterPath tmpPath;

    //currentPositionPath = tmpPath.currentPosition();
    if(!_path.isEmpty())
    {
        tmpPath = _path;
        tmpPath.moveTo(currentPositionPath);
    }
    if(lines.size())
    {
        auto tmpIndex = lines.size()-1;
       // qDebug() << lines[tmpIndex]->line();
        auto tmpLine = lines[tmpIndex]->line();
        tmpPath.lineTo(tmpLine.dx(),tmpLine.dy());
        qDebug() << tmpPath;
        qDebug() << i;


        if(isEnd)
        {

            //_path.moveTo(-currentPositionPath);
            _path.lineTo(tmpLine.dx(),tmpLine.dy());
            currentPositionPath = _path.currentPosition();
            //_path = tmpPath;
          //   setPath(_path);
             _path.closeSubpath();
             qDebug() << "end"<< tmpPath;
             ++i;
             return;
        }
        if(i==0)
        {
           setPath(tmpPath);
           qDebug() << i;
        }
    }


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





