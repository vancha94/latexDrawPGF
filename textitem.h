#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <abstractitem.h>
#include <QGraphicsTextItem>
#include <QLineEdit>

#include <QDebug>

class TextItem:public QGraphicsTextItem, public AbstractItem
{
    Q_OBJECT
public:
    TextItem(QGraphicsTextItem *item=0);
    ~TextItem();


    // AbstractItem interface
public:
    virtual QString prepareText() Q_DECL_OVERRIDE;
    virtual void setCooordinats() Q_DECL_OVERRIDE;
    void setPos(const QPointF &pos);// Q_DECL_OVERRIDE;
    void setVisible(bool visible);// Q_DECL_OVERRIDE;
    void setPen(const QPen &pen,ParamLines _params);
 //   void focusOutEvent(QFocusEvent *event)

    Q_SIGNAL void textChanged(QString str, TextItem *item);

protected:
    virtual QString paramToText() Q_DECL_OVERRIDE;

    // AbstractItem interface
public:
    virtual bool isText() Q_DECL_OVERRIDE;

    // QGraphicsItem interface
protected:
    virtual void focusOutEvent(QFocusEvent *event) Q_DECL_OVERRIDE;
    virtual void focusInEvent(QFocusEvent *event) Q_DECL_OVERRIDE;

    QString oldText;
};

#endif // TEXTITEM_H
