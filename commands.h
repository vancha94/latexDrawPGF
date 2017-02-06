#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include <lineitem.h>

//union item
//{
//    LineItem *line;
//};

class AddCommand : public QUndoCommand
{
public:
    AddCommand(QGraphicsItem *line,  QUndoCommand *parent = 0);
    ~AddCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    //item newItem;
    QGraphicsItem *item;
};


class MoveCommand: public QUndoCommand
{
public:
    MoveCommand(QList<QGraphicsItem*> _itemList,
                QList<QPointF> _oldPos,
                QList<QPointF> _newPos,
                QUndoCommand *parent = 0);
    ~MoveCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    QList<QGraphicsItem*> itemsList;
    QList<QPointF> oldPos, newPos;


};


class DeleteCommand: public QUndoCommand
{
public:
    DeleteCommand(QList<QGraphicsItem*> _itemList, QUndoCommand *parent = 0);
    ~DeleteCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
private:
    QList<QGraphicsItem*> itemsList;

};
#endif // ADDCOMMAND_H
