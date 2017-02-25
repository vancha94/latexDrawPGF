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
    drawingToolBar->setMovable(false);

    drawingToolBar->addAction(undoAction);
    drawingToolBar->addAction(redoAction);
    drawingToolBar->addSeparator();

    drawingToolBar->addAction(selectAction);
    drawingToolBar->addAction(lineAction);

}

void MainWindow::createColorWidgets()
{
    colorBorderWidget = new ColorLatexWidget();
    colorBorderWidget->show();

    colorBackgroundWidget = new ColorLatexWidget(true);
    colorBackgroundWidget->show();

    colorTextWidget = new ColorLatexWidget();
    colorTextWidget->show();

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

void MainWindow::widthIndexToValue(int inedex)
{
    qreal tmpValue = qvariant_cast<qreal>(widthBox->currentData());
    emit changedWidthValue(tmpValue);
}

void MainWindow::createWidthBox()
{
    widthBox = new QComboBox;
    // полученные размеры иконки получены эмперически:
    // 15 - высота панели
    // 126 - из обратной пропорции (изначально картинка была 420*50)
    widthBox->setIconSize(QSize(126,15));

    // последние значения - различные значение для толлщин пера
    // они подобраны эмпирически
    //    0,1	0,5
    //    0,2	1
    //    0,4	2
    //    0,6	3
    //    0,8	4
    //    1,2	6
    //    1,6	8


    widthBox->addItem(QIcon(":/icons/width/ultra_thin.png"),   "0.1pt",0.5);
    widthBox->addItem(QIcon(":/icons/width/very_thin.png"),    "0.2pt",1);
    widthBox->addItem(QIcon(":/icons/width/thin.png"),         "0.4pt",2);
    widthBox->addItem(QIcon(":/icons/width/semithick.png"),    "0.6pt",3);
    widthBox->addItem(QIcon(":/icons/width/thick.png"),        "0.8pt",4);
    widthBox->addItem(QIcon(":/icons/width/very_thick.png"),   "1.2pt",6);
    widthBox->addItem(QIcon(":/icons/width/ultra_thick.png"),  "1.6pt",8);

    connect(widthBox,SIGNAL(currentIndexChanged(int)),this,SLOT(widthIndexToValue(int)));
    connect(this,SIGNAL(changedWidthValue(qreal)),scene,SLOT(setPenWidth(qreal)));
    widthBox->setCurrentIndex(2);
}

void MainWindow::createColorToolBar()
{

    colorToolBar = new QToolBar;
    addToolBar(Qt::BottomToolBarArea,colorToolBar);
    colorToolBar->setMovable(false);

    createColorWidgets();
    createWidthBox();




    colorToolBar->addWidget(widthBox);

}
