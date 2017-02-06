#include "scene.h"
//#define private public
#include <QDebug>
#include <commands.h>

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    sceneMode = NoMode;
    lineItem = 0;
    drawItem = 0;
    undoStack = new QUndoStack(this);
    undoAction = undoStack->createUndoAction(this);
    redoAction = undoStack->createRedoAction(this);

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
    undoAction->trigger();
    // qDebug() << 1;
}

void Scene::redo()
{
    redoAction->trigger();
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

void Scene::addLine(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event)
{
    if(!lineItem)
    {

        lineItem = new LineItem();
        addCommand = new AddCommand(lineItem);
        undoStack->push(addCommand);
        this->addItem(lineItem);
        lineItem->setPen(QPen(Qt::black, 3, Qt::SolidLine));
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
        if(oldPos.first() != newPos.first() &&
                oldPos.size() == newPos.size())
        {
            QUndoCommand *moveCommand = new MoveCommand(tmpList,oldPos,newPos);
            undoStack->push(moveCommand);
        }
        isMoveElemnts = false;

    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    //if(sceneMode == DrawLine && lineItem)
    //emit lineItem->itemChanged();
    // Move
    if(sceneMode == SelectObject)
    {
        movingElementsEnd();

    }
    lineItem = 0;
    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        auto tmpList = selectedItems();
        if(tmpList.size())
        {
            QUndoCommand *deleteCommand = new DeleteCommand(tmpList);
            undoStack->push(deleteCommand);
        }


    }
    else
        QGraphicsScene::keyPressEvent(event);
}
