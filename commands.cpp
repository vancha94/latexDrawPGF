#include "commands.h"

AddCommand::AddCommand(QGraphicsItem *line, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;
    item = line;
   // item.line = line;
   // myGraphicsScene->addItem(line);
   // scene->update();
    ++itemCount;

}

void AddCommand::undo()
{
    item->setVisible(false);
}

void AddCommand::redo()
{
    item->setVisible(true);
}

AddCommand::~AddCommand()
{
    item = NULL;
}


MoveCommand::MoveCommand(QList<QGraphicsItem *> _itemList,
                         QList<QPointF> _oldPos,
                         QList<QPointF> _newPos,
                         QUndoCommand *parent)
    : QUndoCommand(parent)
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
}

void MoveCommand::redo()
{
    auto size = itemsList.size();
   for (int i=0;i<size;++i)
   {
       itemsList[i]->setPos(newPos[i]);
   }
}

DeleteCommand::DeleteCommand(QList<QGraphicsItem *> _itemList, QUndoCommand *parent)
    : QUndoCommand(parent)
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
}

void DeleteCommand::redo()
{
    foreach(QGraphicsItem* item, itemsList)
    {
        item->setVisible(false);
    }
}
