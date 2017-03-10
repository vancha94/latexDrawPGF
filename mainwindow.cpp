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

    latexText = new LatexText(dock);
    dock->setWidget(latexText);

    userPenStyle = new UserPenStyle();





    setCentralWidget(view);
    addDockWidget(Qt::RightDockWidgetArea,dock);


    createActions();
    createConnections();
    createDrawToolBar();
    createColorToolBar();


    //view->setmo
    // test code
    //usepPenStyle->show();


}

MainWindow::~MainWindow()
{
    delete scene;
    delete dock;
    delete userPenStyle;
    //delete
}

void MainWindow::createActions()
{


    createDrawAction(lineAction,        "Draw line",       QIcon(":/icons/line.png"),    Scene::DrawLine);
    createDrawAction(selectAction,      "Select object",   QIcon(":/icons/select.png"),  Scene::SelectObject);
    createDrawAction(polylineAction,    "Draw PolyLine",   QIcon(":/icons/polyline.png"),Scene::DrawPolyLine,true);




    drawActionGroup = new QActionGroup(this);
    drawActionGroup->setExclusive(true);
    drawActionGroup->addAction(lineAction);
    drawActionGroup->addAction(selectAction);
    drawActionGroup->addAction(polylineAction);

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
    connect(userPenStyle,SIGNAL(canselClicked()),this,SLOT(userStyleCanceled()));
    connect(userPenStyle,SIGNAL(okClicked(QString,QVector<qreal>,qreal)),
            scene,SLOT(setPenStyle(QString,QVector<qreal>,qreal)));




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
        return nullptr;

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

void MainWindow::userStyleCanceled()
{
    styleBox->setCurrentIndex(0);
}

void MainWindow::addDrawActions()
{
    drawingToolBar->addAction(selectAction);
    drawingToolBar->addAction(lineAction);
    drawingToolBar->addAction(polylineAction);
}

void MainWindow::polyItem()
{
    view->setMouseTracking(true);
}

void MainWindow::notPolyItem()
{
    view->setMouseTracking(false);
}

void MainWindow::jointToValue(int index)
{
    QString value = jointBox->itemText(index);
    Qt::PenJoinStyle style = qvariant_cast<Qt::PenJoinStyle>(jointBox->itemData(index));
    emit changeJointValue(value,style);
}



void MainWindow::createDrawToolBar()
{
    drawingToolBar = new QToolBar;
    addToolBar(Qt::TopToolBarArea, drawingToolBar);
    drawingToolBar->setMovable(false);

    drawingToolBar->addAction(undoAction);
    drawingToolBar->addAction(redoAction);
    drawingToolBar->addSeparator();

    addDrawActions();

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

void MainWindow::isSelectedUserItem(QString str)
{
    if(str!="user style")
        emit changeStyleValue(str);
    else if (str=="user style")
    {
        //TODO написать виджет для этого стиля, сигналы к нему и тд.
        userPenStyle->exec();

    }
    else
    {
        // на всяий случай, если выбралась та поизиция, кторой нет
        Q_ASSERT(false);
    }
}

void MainWindow::createStyleBox()
{
    styleBox = new QComboBox();
    styleBox->setIconSize(QSize(126,15));

    styleBox->addItem(QIcon(":/icons/style/solid.png"),                 "solid");
    styleBox->addItem(QIcon(":/icons/style/dotted.png"),                "dotted");
    styleBox->addItem(QIcon(":/icons/style/densely_dotted.png"),        "densely dotted");
    styleBox->addItem(QIcon(":/icons/style/loosely_dotted.png"),        "loosely dotted");
    styleBox->addItem(QIcon(":/icons/style/dashed.png"),                "dashed");
    styleBox->addItem(QIcon(":/icons/style/densely_dashed.png"),        "densely dashed");
    styleBox->addItem(QIcon(":/icons/style/loosely_dashed.png"),        "loosely dashed");
    styleBox->addItem(QIcon(":/icons/style/dashdotted.png"),            "dashdotted");
    styleBox->addItem(QIcon(":/icons/style/densely_dashdotted.png"),    "densely dashdotted");
    styleBox->addItem(QIcon(":/icons/style/loosely_dashdotted.png"),    "loosely dashdotted");
    styleBox->addItem(QIcon(":/icons/style/dashdotdotted.png"),         "dashdotdotted");
    styleBox->addItem(QIcon(":/icons/style/densely_dashdotdotted.png"), "densely dashdotdotted");
    styleBox->addItem(QIcon(":/icons/style/loosely_dashdotdotted.png"), "loosely dashdotdotted");


    //userItem - отдельное поведение
    styleBox->addItem("user style",true);

    connect(styleBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(isSelectedUserItem(QString)));
    connect(this,SIGNAL(changeStyleValue(QString)),scene,SLOT(setPenStyle(QString)));
}

void MainWindow::createJointBox()
{
    jointBox = new QComboBox();
    jointBox->setIconSize(QSize(15,15));


    jointBox->addItem(QIcon(":/icons/joint/bevel.png"),"bevel",Qt::BevelJoin);
    jointBox->addItem(QIcon(":/icons/joint/miter.png"),"miter",Qt::MiterJoin);
    jointBox->addItem(QIcon(":/icons/joint/round.png"),"round",Qt::RoundJoin);

    connect(jointBox,SIGNAL(currentIndexChanged(int)),this,SLOT(jointToValue(int)));
    connect(this,SIGNAL(changeJointValue(QString,Qt::PenJoinStyle)),scene,SLOT(setJointStyle(QString,Qt::PenJoinStyle)));

    jointBox->setCurrentIndex(1);
}

void MainWindow::createColorToolBar()
{

    colorToolBar = new QToolBar;
    addToolBar(Qt::BottomToolBarArea,colorToolBar);
    colorToolBar->setMovable(false);

    createColorWidgets();
    createWidthBox();
    createStyleBox();
    createJointBox();


    colorToolBar->addWidget(widthBox);
    colorToolBar->addWidget(styleBox);
    colorToolBar->addWidget(jointBox);

}

void MainWindow::createDrawAction(QAction* &action, QString name, QIcon icon, Scene::Mode _mode, bool isPoly)
{
    action = new QAction(name, this);
    action->setData(int(_mode));
    action->setIcon(icon);
    action->setCheckable(true);
    if(isPoly)
        connect(action,SIGNAL(triggered(bool)),this,SLOT(polyItem()));
    else
        connect(action,SIGNAL(triggered(bool)),this,SLOT(notPolyItem()));
}
