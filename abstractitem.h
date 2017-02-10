#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H
#include <QVector>
#include <QPointF>
#include <QGraphicsItem>

class AbstractItem//: public QGraphicsItem
{
protected:
    QVector<QPointF> points;
    QPointF scenePosition;
    bool isVis;
public:
    AbstractItem(){}
  //  AbstractItem(QGraphicsItem *parent =0):QGraphicsItem(parent) {}
    virtual QString prepareText()=0;
//    virtual void setPos(QPointF &pos)=0;
//    virtual void setVisible(bool visible)=0;
    void setScenePosition(QPointF pos)
    {
        scenePosition = pos;
    }
    virtual void setCooordinats()=0;
};

#endif // ABSTRACTITEM_H
