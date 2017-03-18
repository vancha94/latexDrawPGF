#ifndef LINEITEM_H
#define LINEITEM_H

#define private public
#include <QGraphicsLineItem>
#include "abstractline.h"
#undef private

class LineItem: public AbstractLine, public QGraphicsLineItem
{
public:
 //   LineItem();
    LineItem(QGraphicsLineItem* item=0);

    virtual QString prepareText();
    void setPos(const QPointF &pos);// Q_DECL_OVERRIDE;
    void setLine(qreal x1, qreal y1, qreal x2, qreal y2);
    void setVisible(bool visible);// Q_DECL_OVERRIDE;
    void setPen(const QPen &pen,ParamLines _params);
    void setCooordinats();
};

#endif // LINEITEM_H
