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
#include <colorlatexwidget.h>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>
#include <userpenstyle.h>


enum colorButtons
{
    BORDER,
    BACKGROUND,
    TEXT
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow();
    ~MainWindow();
public slots:
    void actionGroupClicked(QAction*);
    void buttonColorClicked();
    void colorButtonChange(QColor color, QString string);

    void bakgroundButtonClicked();
    void borderButtonClicked();
    void textButtonClicked();
signals:
    void changedWidthValue(qreal value);
    void changeStyleValue(QString value);
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
    QPushButton *buttonBorder;
    QPushButton *buttonBackground;
    QPushButton *buttonText;
    bool isBackgroundButtonClicked;
    colorButtons clickedColorButton;

    QUndoStack* stack;

    ColorLatexWidget *colorBorderWidget;
    ColorLatexWidget *colorBackgroundWidget;
    ColorLatexWidget *colorTextWidget;


    QComboBox *widthBox;
    QComboBox *styleBox;

    UserPenStyle *usepPenStyle;




private: //methods
    void createActions();
    void createConnections();
    void createDrawToolBar();
    void createColorToolBar();



    QPushButton * setButtonPointner();
    ColorLatexWidget *setWidgetPointner();
    void createColorWidgets();

   Q_SLOT void widthIndexToValue(int inedex);
    void createWidthBox();

    Q_SLOT void isSelectedUserItem(QString str);
};

#endif // MAINWINDOW_H
