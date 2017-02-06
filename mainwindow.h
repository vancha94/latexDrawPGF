#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QToolBar>
#include "scene.h"
#include <QAction>
#include <latextext.h>
#include <QHBoxLayout>
#include <QUndoStack>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow();
    ~MainWindow();
public slots:
    void actionGroupClicked(QAction*);
private:
    QGraphicsView* view;
    Scene* scene;
    LatexText* latexText;
    //QHBoxLayout* horizontallLayout;


    QAction* lineAction;
    QAction* selectAction;
    QActionGroup *drawActionGroup;

    QAction* undoAction;
    QAction* redoAction;


    QToolBar* drawingToolBar;
    QToolBar* colorToolBar;
    QToolBar* textToolBar;

    QDockWidget* dock;

    QUndoStack* stack;
private: //methods
    void createActions();
    void createConnections();
    void createDrawToolBar();



};

#endif // MAINWINDOW_H
