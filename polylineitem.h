#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include "lineitem.h"
#include <QGraphicsItemGroup>


class PolyLineItem : public LineItem, public QGraphicsItemGroup
{
public:
    PolyLineItem(QGraphicsItemGroup *groupItem,QGraphicsLineItem *lineItem=0);
    ~PolyLineItem();

    // AbstractItem interface
public:
    virtual QString prepareText() Q_DECL_OVERRIDE;
    virtual void setCooordinats() Q_DECL_OVERRIDE;

protected:
    virtual QString paramToText() Q_DECL_OVERRIDE;
};

#endif // POLYLINEITEM_H
