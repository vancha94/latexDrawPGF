#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H
#include <QVector>
#include <QPointF>
#include <QGraphicsItem>
#include <QDebug>
#include <QPen>

class AbstractItem
{
protected:
    QVector<QPointF> points;
    QPointF scenePosition;
    bool isVis;


    QString borderColor;
    QString backgroundColor;
    float borderAlpha;
    float  backgroundAlpha;

    QHash<qreal, QString>  widthHash;
    QString width;



public:


    AbstractItem();
    virtual QString prepareText()=0;
    virtual void setCooordinats()=0;

    void setScenePosition(QPointF pos);


    void setBorderColor(QString str);
    void setBackgroundColor(QString str);
    void setBorderAlpha(float value);
    void setBackgroundAlpha(float value);


    void setWidth(qreal value);
    virtual void setPen(const QPen &pen,QString str);


protected: //metods
//    virtual QString paramToText();
private:

    void fillHash();
};

#endif // ABSTRACTITEM_H
