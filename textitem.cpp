#include "textitem.h"
#include <qdebug.h>

TextItem::TextItem(QGraphicsTextItem *item)
    :QGraphicsTextItem(item), AbstractItem()
{
    setPlainText("");
}

TextItem::~TextItem()
{

}

QString TextItem::prepareText()
{
    qreal centreX = scenePos().x() + boundingRect().width()/2;
    qreal centreY = scenePos().y() + boundingRect().height()/2;

    QString tmpStr = "\\draw ["+paramToText()+"]";
    tmpStr+="("+QString::number(centreX)+",";
    tmpStr+=QString::number(-centreY) +")";
    tmpStr+=" node {";
    tmpStr+=toPlainText() +"};";

    return isVis?tmpStr:"";
}

void TextItem::setCooordinats()
{
    setScenePosition(scenePos());
    isVis = isVisible();
}

void TextItem::setPos(const QPointF &pos)
{
    QGraphicsTextItem::setPos(pos);

    setCooordinats();
}

void TextItem::setVisible(bool visible)
{
    QGraphicsTextItem::setVisible(visible);
    setCooordinats();
}

void TextItem::setPen(const QPen &pen, ParamLines _params)
{
    //QGraphicsTextItem::setPen(pen);
    setDefaultTextColor(pen.color());
    AbstractItem::setPen(pen,_params);
}

QString TextItem::paramToText()
{
    return borderColorToText();
}

bool TextItem::isText()
{
    return true;
}

void TextItem::focusOutEvent(QFocusEvent *event)
{
    if(oldText != toPlainText())
        emit textChanged(oldText, this);
    QGraphicsTextItem::focusOutEvent(event);
}

void TextItem::focusInEvent(QFocusEvent *event)
{
    oldText = toPlainText();
    QGraphicsTextItem::focusInEvent(event);
}
