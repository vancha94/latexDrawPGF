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


private: //methods
    void createActions();
    void createConnections();
    void createDrawToolBar();
    void createColorToolBar();



    QPushButton * setButtonPointner();
    ColorLatexWidget *setWidgetPointner();
};

#endif // MAINWINDOW_H
