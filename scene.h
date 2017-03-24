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
#include <paramslines.h>
#include <polylineitem.h>
#include <rectangleltem.h>
#include <ellipseitem.h>
#include <polygonitem.h>
#include <textitem.h>

#include <QGraphicsTextItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode {NoMode, SelectObject, DrawLine,DrawPolyLine,
              DrawPencil,DrawRectangle,DrawEllipse,
               DrawPolygon, DrawText};
    Scene(QObject* parent = 0);

    void setMode(Mode mode);

    void undo();
    void redo();

    void pushStack(QGraphicsItem *item);
    void popStack();
    void resetText();

public Q_SLOTS:
    void setBackgroundColor(QColor color,QString str);
    void setBorderColor(QColor color, QString str);

    void setBorderAlpha(int value);
    void setBacgroundAlpha(int value);

    void setPenWidth(qreal value);
    void setPenStyle(QString str);
    void setPenStyle(QString str, QVector<qreal> vector, qreal offset = 0);

    void setJointStyle(QString value, Qt::PenJoinStyle style);

    void textChanged(QString str, TextItem *item);
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
    PolyLineItem *polylineitem;
    Rectangleltem *rectItem;
    EllipseItem *ellipseItem;
    PolygonItem *polygonItem;
    TextItem *textItem;


    bool firstClick;
    bool isPencilDrawed;

    // undo/redo properties

    QUndoStack *undoStack;
    QAction *undoAction;
    QAction *redoAction;
    QList<QPointF> oldPos, newPos;
    bool isMoveElemnts;

    //text properties
    QStack<QGraphicsItem*> itemStack;
    QStack<QString> textStack;

    //color Properties
    QBrush background;
    QPen border;

    //style properties
    QHash<QString, QVector<qreal>> listOfLineStyles;

    ParamLines params;

    //tst
private: //methods
    void makeItemsControllable(bool areControllable);
    void connectSignals();
    void addLine(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event, bool isPoly=false);
    void movingElementsEnd();
    void movingsElementsStart();
    void addCommandConnectSignal(AddCommand *addCommand);
    void addText(QGraphicsItem *item);
    void attachStrings();
    void createLineStyles();
    void addLineStyle(QString str, QPen tmpPen, qreal delta = 0);
    void addUndo(QUndoCommand *addCommand);
    void setNewItemParams(QGraphicsItem* item);
    void addPolyLine(QGraphicsSceneMouseEvent *event,bool isPencil = false);
    void changePenItemParams();
    void changeBrushItemParams();
    void addRectangle(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event);
    void addPencil(QGraphicsSceneMouseEvent *event);
    void addElipse(QUndoCommand *addCommand, QGraphicsSceneMouseEvent *event);
    void addPolygon(QGraphicsSceneMouseEvent *event);
    void drawPolygon(QGraphicsSceneMouseEvent *event);
};

#endif // SCENE_H
