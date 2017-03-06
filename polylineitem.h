#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include <abstractitem.h>
#include <QGraphicsItemGroup>
#include <lineitem.h>
#include <abstractline.h>


class PolyLineItem :public AbstractLine, public QGraphicsItemGroup
{
public:
    PolyLineItem(QGraphicsItemGroup *lineItem=0);
    ~PolyLineItem();

public:
    virtual QString prepareText() Q_DECL_OVERRIDE;
    virtual void setCooordinats() Q_DECL_OVERRIDE;
    void setVisible(bool visible);
    void setPos(const QPointF &pos);
    void addItem(LineItem* item);
    void addToGroup(LineItem *item);
    //void setPen(const QPen &pen, ParamLines _params);
    void setParams(const ParamLines &value);

protected:
    QVector<LineItem*> lines;
   // QVector<QPointF> points;


protected: //methods
    virtual QString paramToText() Q_DECL_OVERRIDE;
    void restorePoints();

    //virtual void paint();
};

#endif // POLYLINEITEM_H
