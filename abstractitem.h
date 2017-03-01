#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H
#include <QVector>
#include <QPointF>
#include <QGraphicsItem>
#include <QDebug>
#include <QPen>
#include <paramslines.h>

class AbstractItem
{
protected:
    QVector<QPointF> points;
    QPointF scenePosition;
    bool isVis;


    ParamLines params;

    QString borderColor;
    QString backgroundColor;
    float borderAlpha;
    float  backgroundAlpha;

    QHash<qreal, QString>  widthHash;
    QString width;

    QString style;



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
    void setStyle(QString str);
    virtual void setPen(const QPen &pen, ParamLines _params);


    QString getStyle() const;

    void setAllValues(ParamLines _params);

protected: //metods
    // в подготовке текста вызывать данный метод только в таков виде
    // "["+ paramToText() + "]"
    virtual QString paramToText()=0;
    QString backgroundColorToText();
private:

    void fillHash();

    void setAllvalues(ParamLines _params);
};

#endif // ABSTRACTITEM_H
