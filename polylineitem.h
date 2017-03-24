#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H


#include <QGraphicsPolygonItem>
#include <abstractline.h>


class PolyLineItem :public AbstractLine, public QGraphicsPolygonItem
{
public:
    PolyLineItem(bool _isPencil = false, QGraphicsItem *lineItem=0);
    ~PolyLineItem();

public:

    virtual QString prepareText() Q_DECL_OVERRIDE;
    virtual void setCooordinats() Q_DECL_OVERRIDE;
    void setVisible(bool visible);
    void setPos(const QPointF &pos);
    void setParams(const ParamLines &value);
    void setPen(const QPen &pen, ParamLines _params);
    void setPolygon(const QPolygonF &polygon);


protected: //methods
    virtual QString paramToText() Q_DECL_OVERRIDE;

    bool isPencil;


    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual QPainterPath shape() const Q_DECL_OVERRIDE;
};

#endif // POLYLINEITEM_H
