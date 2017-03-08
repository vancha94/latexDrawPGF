#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include <abstractitem.h>
#include <QGraphicsPathItem>
#include <lineitem.h>
#include <abstractline.h>


class PolyLineItem :public AbstractLine, public QGraphicsPathItem
{
public:
    PolyLineItem(QGraphicsPathItem *lineItem=0);
    ~PolyLineItem();

public:
    // не забыть, что для последующий симоволо userType  - менять
   // enum {Polyline = UserType +1};
    virtual QString prepareText() Q_DECL_OVERRIDE;
    virtual void setCooordinats() Q_DECL_OVERRIDE;
    void setVisible(bool visible);
    void setPos(const QPointF &pos);
   // void addItem(LineItem* item);
    void addToGroup(LineItem *item);
    //void setPen(const QPen &pen, ParamLines _params);
    void setParams(const ParamLines &value);
    void setPen(const QPen &pen, ParamLines _params);
    void drawOneLine(bool isEnd = false);
protected:
    QVector<LineItem*> lines;
    QPainterPath _path;
    QPointF currentPositionPath;
   // QVector<QPointF> points;
    //tmp
    int i ;


protected: //methods
    virtual QString paramToText() Q_DECL_OVERRIDE;


    //virtual void paint();
};

#endif // POLYLINEITEM_H
