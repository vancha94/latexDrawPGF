#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include <lineitem.h>
#include <QObject>
#include <paramslines.h>
#include <textitem.h>

class AddCommand : public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    AddCommand(QGraphicsItem *line, QUndoCommand *parentUndo = 0, QObject *parentObj=0);
    ~AddCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

signals:
    void pushStackItem(QGraphicsItem* stackItem);
    void popStackItem();



private:
    //item newItem;
    QGraphicsItem *item;
    bool flag;
};


class MoveCommand: public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    MoveCommand(QList<QGraphicsItem*> _itemList,
                QList<QPointF> _oldPos,
                QList<QPointF> _newPos,
                QUndoCommand *parent = 0,
                 QObject *parentObj=0);
    ~MoveCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

signals:
    void useCommand();
private:
    QList<QGraphicsItem*> itemsList;
    QList<QPointF> oldPos, newPos;


};


class DeleteCommand: public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    DeleteCommand(QList<QGraphicsItem*> _itemList, QUndoCommand *parent = 0,QObject *parentObj=0);
    ~DeleteCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

signals:
    void useCommand();
private:
    QList<QGraphicsItem*> itemsList;

};

class ChangePenCommand: public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    explicit ChangePenCommand(QList<QGraphicsItem*> _itemList, QPen _pen,ParamLines _newParams, QUndoCommand *parent = 0, QObject *parentObj=0);
    ~ChangePenCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

signals:
    void useCommand();
private:
    QList<QGraphicsItem*> itemsList;
    QList<QPen> oldPenList;
    QList<ParamLines> paramsList;
    QPen newPen;
    ParamLines newParams;

};

class ChangeBrushCommand: public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    explicit ChangeBrushCommand(QList<QGraphicsItem*> _itemList, QBrush _brush, ParamLines _newParams, QUndoCommand *parent = 0, QObject *parentObj=0);
    ~ChangeBrushCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

signals:
    void useCommand();
private:
    QList<QGraphicsItem*> itemsList;
    QList<QBrush> oldPenList;
    QList<ParamLines> paramsList;
    QBrush newBrush;
    ParamLines newParams;

};

class TextChanged: public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    explicit TextChanged(TextItem *item, QString _oldText, QString _newText);
    ~TextChanged();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

signals:
    void useCommand();
private:
    QString newText, oldText;
    TextItem *item;
};

#endif // ADDCOMMAND_H
