#ifndef LINEITEM_H
#define LINEITEM_H

#define private public
#include <QGraphicsLineItem>
#include "abstractitem.h"
#undef private

class LineItem : public QGraphicsLineItem, public AbstractItem
{
public:
    LineItem();
    QString prepareText();
    void setPos(const QPointF &pos);
    void setLine(qreal x1, qreal y1, qreal x2, qreal y2);
    void setVisible(bool visible);
private: //methods

    void setCooordinats();
};

#endif // LINEITEM_H
