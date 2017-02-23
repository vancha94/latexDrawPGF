#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H
#include <QVector>
#include <QPointF>
#include <QGraphicsItem>
#include <QDebug>

class AbstractItem
{
protected:
    QVector<QPointF> points;
    QPointF scenePosition;
    bool isVis;
    int saturation;
    double saturationF;
    QString borderColor;
    QString backgroundColor;
    float borderAlpha;
    float  backgroundAlpha;


public:
    AbstractItem()
    {
        setBorderColor("Black");
        setBackgroundColor("White");
    }
  //  AbstractItem(QGraphicsItem *parent =0):QGraphicsItem(parent) {}
    virtual QString prepareText()=0;
//    virtual void setPos(QPointF &pos)=0;
//    virtual void setVisible(bool visible)=0;
    void setScenePosition(QPointF pos)
    {
        scenePosition = pos;
    }
    void setSaturation(int saturation_)
    {
        saturation = saturation_;
    }

    void setBorderColor(QString str)
    {
       // borderColor = str;
        borderColor = QString(str);
        qDebug() <<str << borderColor;

    }

    void setBackgroundColor(QString str)
    {
        backgroundColor = str;
        qDebug() << str <<  backgroundColor;
    }

    virtual void setCooordinats()=0;

    void setBorderAlpha(float value)
    {
        borderAlpha = value;
    }
    void setBackgroundAlpha(float value)
    {
        backgroundAlpha = value;
    }

private:
    QString saturationToText()
    {
        saturationF = 100*saturation/255.0*100;
        if (saturationF>=100)
            return "";
        else if (saturationF>=0)
            return "!" + QString::number(saturationF);
    }
};

#endif // ABSTRACTITEM_H
