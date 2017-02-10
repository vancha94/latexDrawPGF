#include "mainwindow.h"
#include <QDockWidget>
#include <QDebug>

MainWindow::MainWindow()
{

    scene = new Scene(this);
    scene->setSceneRect(0,0,200,200);
    view = new QGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing);

    dock = new QDockWidget(QString("Latex text"),this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
   // dock->setWindowFlags(Qt::WindowTitleHint);

    latexText = new LatexText(dock);
    dock->setWidget(latexText);


 //   setLayout(horizontallLayout);
  //  setCentralWidget(horizontallLayout);

    setCentralWidget(view);
    addDockWidget(Qt::RightDockWidgetArea,dock);
   // setCentralWidget(latexText);

    createActions();
    createConnections();
    createDrawToolBar();


}

MainWindow::~MainWindow()
{
    delete scene;
    delete dock;
}

void MainWindow::createActions()
{
    lineAction = new QAction("Draw line", this);
    lineAction->setData(int(Scene::DrawLine));
    lineAction->setIcon(QIcon(":/icons/line.png"));
    lineAction->setCheckable(true);

    selectAction = new QAction("Select object", this);
    selectAction->setData(int(Scene::SelectObject));
    selectAction->setIcon(QIcon(":/icons/select.png"));
    selectAction->setCheckable(true);

    drawActionGroup = new QActionGroup(this);
    drawActionGroup->setExclusive(true);
    drawActionGroup->addAction(lineAction);
    drawActionGroup->addAction(selectAction);

    undoAction = new QAction("Undo",this);
    undoAction->setIcon(QIcon(":/icons/undo.png"));
    connect(undoAction,&QAction::triggered,scene,&Scene::undo);


    redoAction = new QAction("Redo", this);
    redoAction->setIcon(QIcon(":/icons/redo.png"));
    connect(redoAction,&QAction::triggered,scene,&Scene::redo);


}

void MainWindow::createConnections()
{
    connect(drawActionGroup, SIGNAL(triggered(QAction*)),
            this, SLOT(actionGroupClicked(QAction*)));
    connect(scene,&Scene::transmitText,latexText,&LatexText::addText);


}

void MainWindow::actionGroupClicked(QAction *action)
{
    scene->setMode(Scene::Mode(action->data().toInt()));
}


void MainWindow::createDrawToolBar()
{
    drawingToolBar = new QToolBar;
    addToolBar(Qt::TopToolBarArea, drawingToolBar);
    drawingToolBar->addAction(undoAction);
    drawingToolBar->addAction(redoAction);
    drawingToolBar->addSeparator();

    drawingToolBar->addAction(selectAction);
    drawingToolBar->addAction(lineAction);

}
