#include "scene.h"
//#define private public
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
    borderColor = "Black";

    background.setColor(QColor("#ffffff"));
    backgroundColor = "White";


    border.setWidth(3);


    //QGraphicsItem* tmpit = new QGraphicsItem();
    //  view = new QUndoView(undoStack);
    //   view->show();



    // connectSignals();
}

void Scene::setMode(Mode mode)
{
    sceneMode = mode;
    QGraphicsView::DragMode vMode =
            QGraphicsView::NoDrag;
    if(mode == DrawLine)
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
    //Q_ASSERT(false);
    undoAction->trigger();

    // qDebug() << 1;
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
    auto tmp = itemStack.pop();
    auto tmp1 = textStack.pop();
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
    backgroundColor = str;
}

void Scene::setBorderColor(QColor color, QString str)
{
    border.setColor(color);
    borderColor = str;
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
        origPoint = event->scenePos();

    QGraphicsScene::mousePressEvent(event);
}

void Scene::addCommandConnectSignal(AddCommand *addCommand)
{
    connect(addCommand,&AddCommand::pushStackItem,this,&Scene::pushStack);
    connect(addCommand,&AddCommand::popStackItem,this,&Scene::popStack);


}

void Scene::addLine(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event)
{
    if(!lineItem)
    {

        lineItem = new LineItem();

        lineItem->setBorderAlpha(border.color().alphaF()*100);

        addCommand = new AddCommand(lineItem);
        addCommandConnectSignal(dynamic_cast<AddCommand*>(addCommand));
        undoStack->push(addCommand);
        this->addItem(lineItem);
        lineItem->setPen(border,borderColor);
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

    if(sceneMode == DrawLine)
    {

        addLine(addCommand, event);

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
    //  lineItem = 0;
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
