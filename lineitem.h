#ifndef LINEITEM_H
#define LINEITEM_H

#define private public
#include <QGraphicsLineItem>
#include "abstractitem.h"
#undef private

class LineItem: public AbstractItem, public QGraphicsLineItem
{
public:
 //   LineItem();
    LineItem(QGraphicsLineItem* item=0);
//    QRectF boundingRect();
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
    QString prepareText();
    void setPos(const QPointF &pos);// Q_DECL_OVERRIDE;
    void setLine(qreal x1, qreal y1, qreal x2, qreal y2);
    void setVisible(bool visible);// Q_DECL_OVERRIDE;
    void setPen(const QPen &pen, QString str);
//    void setb
//private: //methods
public:
    void setCooordinats();
};

#endif // LINEITEM_H
