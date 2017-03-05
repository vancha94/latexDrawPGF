#include "scene.h"
#include <QDebug>
//#include <commands.h>

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    sceneMode = NoMode;
    lineItem = 0;
    drawItem = 0;
    undoStack = new QUndoStack(this);
    undoAction = undoStack->createUndoAction(this);
    redoAction = undoStack->createRedoAction(this);

    border.setColor(QColor("#000000"));
    params.borderColor = "Black";


    background.setColor(QColor("#ffffff"));
    params.backgroundCOlor="White";

    firstClick = true;

    createLineStyles();


    //test code





}

void Scene::setMode(Mode mode)
{
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    if(mode == DrawLine ||
            mode == DrawPolyLine)
    {
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    else if(mode == SelectObject)
    {
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;
        //vMode = QGraphicsView::ScrollHandDrag;
    }

    QGraphicsView* mView = views().at(0);
    if(mView)
        mView->setDragMode(vMode);
}

void Scene::undo()
{
    undoAction->trigger();
}

void Scene::redo()
{
    redoAction->trigger();
}

void Scene::addText(QGraphicsItem *item)
{
    QString tmpStr;
    AbstractItem *tmpItem = dynamic_cast<AbstractItem*>(item);
    tmpItem->setCooordinats();
    tmpStr=tmpItem->prepareText();
    textStack.push(tmpStr);

}

void Scene::attachStrings()
{
    QString tmpString = "";
    foreach (QString str, textStack)
    {
        if(str!="")
            tmpString+=str + "\n";
    }
    emit transmitText(tmpString);
}

void Scene::addLineStyle(QString str, QPen pen, qreal delta)
{
    QVector<qreal> tmpVector = pen.dashPattern();

    // для "просторных" стилей не видно что. что они более широкие, чем стандартные
    // поэтому для видимости увеличиваем разрыв
    if(delta>0)
        delta*=3;

    for (int i =1; i<tmpVector.size();i+=2)
        tmpVector[i]+=delta;
#include <QGraphicsLineItem>
    // обработка ситуации для стиля solid
    // для данного стиля dashPattern() возвращает пустой список
    if (!tmpVector.size())
        tmpVector << 10 << 0;
    listOfLineStyles[str] = tmpVector;
}



void Scene::createLineStyles()
{
    // текстовые константы из LaTeX'а

    // эта константа подобрана экспирементально
    qreal deltaDensity=0.6;

    QPen tmpPen;



    tmpPen.setStyle(Qt::SolidLine);
    addLineStyle("solid",tmpPen);
    params.style = "solid";


    tmpPen.setStyle(Qt::DotLine);
    addLineStyle("dotted",tmpPen);
    addLineStyle("densely dotted",tmpPen,-deltaDensity);
    addLineStyle("loosely dotted",tmpPen,deltaDensity);

    tmpPen.setStyle(Qt::DashLine);
    addLineStyle("dashed",tmpPen);
    addLineStyle("densely dashed",tmpPen,-deltaDensity);
    addLineStyle("loosely dashed",tmpPen,deltaDensity);

    tmpPen.setStyle(Qt::DashDotLine);
    addLineStyle("dashdotted",tmpPen);
    addLineStyle("densely dashdotted",tmpPen,-deltaDensity);
    addLineStyle("loosely dashdotted",tmpPen,deltaDensity);

    tmpPen.setStyle(Qt::DashDotDotLine);
    addLineStyle("dashdotdotted",tmpPen);
    addLineStyle("densely dashdotdotted",tmpPen,-deltaDensity);
    addLineStyle("loosely dashdotdotted",tmpPen,deltaDensity);

}

void Scene::pushStack(QGraphicsItem *item)
{
    addText(item);
    itemStack.push(item);
    attachStrings();
}

void Scene::popStack()
{
    //  if (!(itemStack.isEmpty() && textStack.isEmpty()))
    //  {
    itemStack.pop();
    textStack.pop();
    //auto tmp = itemStack.pop();
    //   auto tmp1 = textStack.pop();
    attachStrings();
    //}
}

void Scene::resetText()
{
    textStack.clear();
    foreach (QGraphicsItem* item, itemStack)
    {
        addText(item);
    }
    attachStrings();
}

void Scene::setBackgroundColor(QColor color, QString str)
{
    background.setColor(color);
    params.backgroundCOlor = str;
}

void Scene::setBorderColor(QColor color, QString str)
{
    border.setColor(color);
    params.borderColor = str;
}

void Scene::setBorderAlpha(int value)
{
    if (value > 255)
        value = 255;
    else if(value < 0)
        value = 0;
    auto tmp  = border.color();
    tmp.setAlpha(value);
    border.setColor(tmp);
}

void Scene::setBacgroundAlpha(int value)
{
    if (value > 255)
        value = 255;
    else if(value < 0)
        value = 0;
    auto tmp = background.color();
    tmp.setAlpha(value);
    background.setColor(tmp);
    //.color().setAlpha(value);
}

void Scene::setPenWidth(qreal value)
{
    border.setWidthF(value);
}

void Scene::setPenStyle(QString str)
{

    border.setDashPattern(listOfLineStyles[str]);
    params.style = str;
}

void Scene::setPenStyle(QString str, QVector<qreal> vector, qreal offset)
{
    params.style = str;
    border.setDashPattern(vector);
    border.setDashOffset(offset);
}

void Scene::makeItemsControllable(bool areControllable)
{
    foreach(QGraphicsItem* item, items())
    {
        item->setFlag(QGraphicsItem::ItemIsSelectable,
                      areControllable);
        item->setFlag(QGraphicsItem::ItemIsMovable,
                      areControllable);
    }
}

void Scene::connectSignals()
{
    //connect(lineItem,&LineItem::transmitText,this,&Scene::transmitText);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(sceneMode == DrawLine)
    {
        origPoint = event->scenePos();
        if(!firstClick)
            lineItem=0;
            firstClick=true;
    }

    if(sceneMode == DrawPolyLine)
    {
        if(firstClick &&
                event->button() == Qt::LeftButton)
        {
            origPoint = event->scenePos();
            firstClick = false;
            polylineitem = new PolyLineItem();
            QUndoCommand* addCommand = new AddCommand(polylineitem);
            addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
            undoStack->push(addCommand);
            this->addItem(polylineitem);
        }
        else if (!firstClick)
        {

            lineItem = 0;
            if(event->button() == Qt::RightButton)
            {
                firstClick = true;
                pushStack(polylineitem);
                polylineitem = 0;
            }
            origPoint = event->scenePos();

        }

        // polylineitem->setPen(border,params);


    }

    QGraphicsScene::mousePressEvent(event);
}

void Scene::addCommandConnectSignal(AddCommand *addCommand)
{
    connect(addCommand,&AddCommand::pushStackItem,this,&Scene::pushStack);
    connect(addCommand,&AddCommand::popStackItem,this,&Scene::popStack);


}

void Scene::addLine(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event,bool isPoly)
{
    if(!lineItem)
    {

        lineItem = new LineItem();
        lineItem->setBorderAlpha(border.color().alphaF()*100);
        if(!isPoly)
        {
            addCommand = new AddCommand(lineItem);
            addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
            undoStack->push(addCommand);
            this->addItem(lineItem);
        }
        else if(isPoly)
            polylineitem->addToGroup(lineItem);


        lineItem->setPen(border,params);
        // lineItem->setPen(QPen());
        // lineItem->setPen(QPen(Qt::black, 3, Qt::SolidLine));
        lineItem->setPos(origPoint);

    }
    lineItem->setLine(0,0,
                      event->scenePos().x() - origPoint.x(),
                      event->scenePos().y() - origPoint.y());
}

void Scene::movingsElementsStart()
{
    oldPos.clear();
    newPos.clear();
    isMoveElemnts = true;
    foreach (QGraphicsItem *item, selectedItems())
    {
        oldPos << item->pos();
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QUndoCommand *addCommand;




    if(sceneMode == DrawLine &&
            event->buttons() & Qt::LeftButton)
    {

        addLine(addCommand, event);

    }
    else if (sceneMode == DrawPolyLine)
    {
        if(!firstClick)
            addLine(addCommand,event,true);
    }

    if(sceneMode == SelectObject && !isMoveElemnts &&
            !selectedItems().isEmpty())
    {
        movingsElementsStart();


    }
    else
        QGraphicsScene::mouseMoveEvent(event);
}

void Scene::movingElementsEnd()
{
    if(isMoveElemnts)
    {

        auto tmpList = selectedItems();
        foreach (QGraphicsItem *item, tmpList)
        {
            newPos << item->pos();
        }
        if( !newPos.isEmpty() &&
                !oldPos.isEmpty())
        {
            if(oldPos.first() != newPos.first() &&
                    oldPos.size() == newPos.size())
            {
                MoveCommand *moveCommand = new MoveCommand(tmpList,oldPos,newPos);
                connect(moveCommand,&MoveCommand::useCommand,this,&Scene::resetText);
                undoStack->push(dynamic_cast<QUndoCommand*>(moveCommand));
            }

        }
        isMoveElemnts = false;

    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{


    if(sceneMode == DrawLine)
    {
        if(lineItem)
            pushStack(lineItem);
        lineItem=0;
    }
    if(sceneMode == SelectObject)
    {
        movingElementsEnd();

    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        auto tmpList = selectedItems();
        if(tmpList.size())
        {
            DeleteCommand *deleteCommand = new DeleteCommand(tmpList);
            connect(deleteCommand,&DeleteCommand::useCommand,this,&Scene::resetText);
            undoStack->push(dynamic_cast<QUndoCommand*>(deleteCommand));
        }


    }
    else
        QGraphicsScene::keyPressEvent(event);
}
