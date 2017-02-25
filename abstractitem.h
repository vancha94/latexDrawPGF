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

    int saturation;
    double saturationF;
    QString borderColor;
    QString backgroundColor;

    float borderAlpha;
    float  backgroundAlpha;

    QHash<qreal, QString>  widthHash;
    QString width;



public:


    AbstractItem()
    {
        setBorderColor("Black");
        setBackgroundColor("White");


        fillHash();

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


    void setWidth(qreal value)
    {
        width = widthHash[value];
    }

    virtual void setPen(const QPen &pen,QString str)
    {
        setBorderColor(str);
        setWidth(pen.widthF());
    }

   // void
private:
    QString saturationToText()
    {
        saturationF = 100*saturation/255.0*100;
        if (saturationF>=100)
            return "";
        else if (saturationF>=0)
            return "!" + QString::number(saturationF);
    }
    void fillHash()
    {

        //    0,1	0,5
        //    0,2	1
        //    0,4	2
        //    0,6	3
        //    0,8	4
        //    1,2	6
        //    1,6	8
        widthHash[0.5] =  "ultra thin";
        widthHash[1]   =  "very thin";
        widthHash[2]   =  "thin";
        widthHash[3]   =  "semithick";
        widthHash[4]   =  "thick";
        widthHash[6]   =  "very thick";
        widthHash[8]   =  "ultra thick";
    }
};

#endif // ABSTRACTITEM_H
