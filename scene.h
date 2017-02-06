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

class Scene : public QGraphicsScene
{
public:
    enum Mode {NoMode, SelectObject, DrawLine};
    Scene(QObject* parent = 0);

    void setMode(Mode mode);
    void undo();
    void redo();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
signals:
    void transmitText(QString str);
private:
    Mode sceneMode;
    QPointF origPoint;
    LineItem *lineItem;
    QGraphicsItem *drawItem;
    QGraphicsLineItem* itemToDraw;
    QUndoStack *undoStack;
    QAction *undoAction;
    QAction *redoAction;
    QList<QPointF> oldPos, newPos;
    bool isMoveElemnts;



private: //methods
    void makeItemsControllable(bool areControllable);
    void connectSignals();
    void addLine(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event);
    void movingElementsEnd();
    void movingsElementsStart();
};

#endif // SCENE_H
