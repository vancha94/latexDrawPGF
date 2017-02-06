#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H
#include <QVector>
#include <QPointF>

class AbstractItem
{
protected:
    QVector<QPointF> points;
    QPointF scenePosition;
    bool isVis;
public:
    AbstractItem() {}
    virtual QString prepareText()=0;
    void setScenePosition(QPointF pos)
    {
        scenePosition = pos;
    }
};

#endif // ABSTRACTITEM_H
