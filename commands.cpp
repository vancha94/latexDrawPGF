#include "commands.h"
#include <abstractitem.h>

AddCommand::AddCommand(QGraphicsItem *line, QUndoCommand *parentUndo, QObject *parentObj )
    : QObject(parentObj), QUndoCommand(parentUndo)
{
    static int itemCount = 0;
    item = line;
    // item.line = line;
    // myGraphicsScene->addItem(line);
    // scene->update();
    ++itemCount;
    emit pushStackItem(item);
    flag = true;
}

void AddCommand::undo()
{
    item->setVisible(false);
    emit popStackItem();
}

void AddCommand::redo()
{
    item->setVisible(true);
    // bool tmp = signalsBlocked();
    if(!flag)
    {
        emit pushStackItem(item);
    }
    else
    {
        flag = false;
    }
}



AddCommand::~AddCommand()
{
    //QObject::~QObject();

}

MoveCommand::MoveCommand(QList<QGraphicsItem *> _itemList,
                         QList<QPointF> _oldPos,
                         QList<QPointF> _newPos,
                         QUndoCommand *parent, QObject *parentObj)
    :QObject(parentObj), QUndoCommand(parent)
{
    oldPos = _oldPos;
    newPos = _newPos;
    itemsList = _itemList;
}

MoveCommand::~MoveCommand()
{

}

void MoveCommand::undo()
{
    auto size = itemsList.size();
    for (int i=0;i<size;++i)
    {
        itemsList[i]->setPos(oldPos[i]);
    }
    emit useCommand();
}

void MoveCommand::redo()
{
    auto size = itemsList.size();
    for (int i=0;i<size;++i)
    {
        itemsList[i]->setPos(newPos[i]);
    }
    emit useCommand();
}

DeleteCommand::DeleteCommand(QList<QGraphicsItem *> _itemList, QUndoCommand *parent, QObject *parentObj)
    :QObject(parentObj), QUndoCommand(parent)
{
    itemsList = _itemList;
}

DeleteCommand::~DeleteCommand()
{

}

void DeleteCommand::undo()
{
    foreach(QGraphicsItem* item, itemsList)
    {
        item->setVisible(true);

    }
    emit useCommand();
}

void DeleteCommand::redo()
{
    foreach(QGraphicsItem* item, itemsList)
    {
        item->setVisible(false);
    }
    emit useCommand();
}
