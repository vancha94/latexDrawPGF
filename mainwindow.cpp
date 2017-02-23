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
    createColorToolBar();


    // colorWidget->show();


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

ColorLatexWidget* MainWindow::setWidgetPointner()
{
    switch (clickedColorButton)
    {
    case BACKGROUND:
        return colorBackgroundWidget;
        break;
    case BORDER:
        return colorBorderWidget;
        break;
    case TEXT:
        return colorTextWidget;
        break;
    default:

        break;
    }
}

void MainWindow::buttonColorClicked()
{
    //QRect colorToolBar->geometry();
    QPushButton *button = setButtonPointner();
    ColorLatexWidget * widget;


    widget = setWidgetPointner();
    QRect rectToolbar =  colorToolBar->geometry();
    QRect rectButton = button->geometry();

    QRect rectWindow = this->geometry();
    QRect rectPallete = colorBorderWidget->geometry();

    widget->setGeometry(rectButton.x()+rectWindow.x(),
                             rectWindow.y()-
                             4*rectButton.y()-
                             rectPallete.height()+
                             rectButton.height()+rectToolbar.y(),
                             rectPallete.width(),rectPallete.height());
    widget->show();
}

QPushButton * MainWindow::setButtonPointner()
{
    QPushButton *button;
    switch (clickedColorButton)
    {
    case colorButtons::BACKGROUND:
        button = buttonBackground;
        break;
    case colorButtons::BORDER:
        button = buttonBorder;
        break;
    case colorButtons::TEXT:
        button = buttonText;
        break;
    default:
        break;
    }
    return button;
}

void MainWindow::colorButtonChange(QColor color, QString string)
{
    QPushButton *button = setButtonPointner();
    QPalette pal = button->palette();
    pal.setColor(QPalette::Button, color);
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->setText(string);
    button->update();
}

void MainWindow::bakgroundButtonClicked()
{
    clickedColorButton = colorButtons::BACKGROUND;
}

void MainWindow::borderButtonClicked()
{
    clickedColorButton = colorButtons::BORDER;
}

void MainWindow::textButtonClicked()
{
     clickedColorButton = colorButtons::TEXT;
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

void MainWindow::createColorToolBar()
{
    colorBorderWidget = new ColorLatexWidget();
    colorBorderWidget->show();

    colorBackgroundWidget = new ColorLatexWidget(true);
    colorBackgroundWidget->show();

    colorTextWidget = new ColorLatexWidget();
    colorTextWidget->show();

    colorToolBar = new QToolBar;
    addToolBar(Qt::BottomToolBarArea,colorToolBar);


    clickedColorButton = colorButtons::BORDER;
    buttonBorder = new QPushButton;
    colorButtonChange(QColor("#000000"),"Black");
    buttonBorder->setToolTip("Border");




    clickedColorButton = colorButtons::BACKGROUND;
    buttonBackground = new QPushButton;
    colorButtonChange(QColor("#ffffff"),"White");
     buttonBackground->setToolTip("Background");

    clickedColorButton = colorButtons::TEXT;
    buttonText = new QPushButton;
    colorButtonChange(QColor("#000000"),"Black");
    buttonText->setToolTip("Text");


    connect(buttonBorder,SIGNAL(clicked(bool)),this,SLOT(borderButtonClicked()));
    connect(buttonBackground,SIGNAL(clicked(bool)),this,SLOT(bakgroundButtonClicked()));
    connect(buttonText,SIGNAL(clicked(bool)),this,SLOT(textButtonClicked()));


    connect(buttonBorder,SIGNAL(clicked(bool)),this,SLOT(buttonColorClicked()));
    connect(buttonBackground,SIGNAL(clicked(bool)),this,SLOT(buttonColorClicked()));
    connect(buttonText,SIGNAL(clicked(bool)),this,SLOT(buttonColorClicked()));
    //connect(buttonText)

    connect(colorBorderWidget,SIGNAL(colorChanged(QColor,QString)),this,SLOT(colorButtonChange(QColor,QString)));
    connect(colorBackgroundWidget,SIGNAL(colorChanged(QColor,QString)),this,SLOT(colorButtonChange(QColor,QString)));
    connect(colorTextWidget,SIGNAL(colorChanged(QColor,QString)),this,SLOT(colorButtonChange(QColor,QString)));

    connect(colorBorderWidget,SIGNAL(colorChanged(QColor,QString)),scene,SLOT(setBorderColor(QColor,QString)));
    connect(colorBackgroundWidget,SIGNAL(colorChanged(QColor,QString)),scene,SLOT(setBackgroundColor(QColor,QString)));

    colorToolBar->addWidget(buttonBorder);
    colorToolBar->addWidget(buttonBackground);
  //  colorToolBar->addWidget(buttonText);

    connect(colorBorderWidget,SIGNAL(saturationChanged(int)),scene,SLOT(setBorderAlpha(int)));
    connect(colorBackgroundWidget,SIGNAL(saturationChanged(int)),scene,SLOT(setBacgroundAlpha(int)));


}
