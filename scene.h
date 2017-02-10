#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QAction>
#include <QGraphicsView>
#include <QKeyEvent>
#include <lineitem.h>
#include <QGraphicsItem>
#include <qstack.h>
#include <QUndoStack>
#include <commands.h>
#include <QUndoView>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode {NoMode, SelectObject, DrawLine};
    Scene(QObject* parent = 0);

    void setMode(Mode mode);

    void undo();
    void redo();

    void pushStack(QGraphicsItem *item);
    void popStack();
    void resetText();


protected: //events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
signals:
    void transmitText(QString str);
private:
    Mode sceneMode;
    // draw properties
    QPointF origPoint;
    LineItem *lineItem;
    QGraphicsItem *drawItem;
    QGraphicsLineItem* itemToDraw;
    // undo/redo properties
    QUndoStack *undoStack;
    QAction *undoAction;
    QAction *redoAction;
    QList<QPointF> oldPos, newPos;
    bool isMoveElemnts;
    //text properties
    QStack<QGraphicsItem*> itemStack;
    QStack<QString> textStack;


private: //methods
    void makeItemsControllable(bool areControllable);
    void connectSignals();
    void addLine(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event);
    void movingElementsEnd();
    void movingsElementsStart();
    void addCommandConnectSignal(AddCommand *addCommand);
    void addText(QGraphicsItem *item);
    void attachStrings();
};

#endif // SCENE_H
