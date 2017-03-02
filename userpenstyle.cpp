#include "userpenstyle.h"
#include "ui_userpenstyle.h"
#include <QDebug>



UserPenStyle::UserPenStyle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPenStyle)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
    ui->graphicsView->setScene(scene);

    initTableValues();

    pen.setWidth(3);

    item = new QGraphicsLineItem;
    item->setLine(-2*ui->graphicsView->geometry().width(),
                  -8*ui->graphicsView->geometry().height(),
                  ui->graphicsView->geometry().width(),
                  ui->graphicsView->geometry().height());

    scene->addItem(item);

    createVectorPattern();
    // pen.setStyle(Qt::DotLine);
    item->setPen(pen);


    connect(ui->addButton,SIGNAL(clicked(bool)),this,SLOT(addElement()));
    connect(ui->tableWidget,&QTableWidget::cellChanged,this,&UserPenStyle::createVectorPattern);
    connect(ui->offset,SIGNAL(valueChanged(double)),this,SLOT(changeOffset(qreal)));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(deleteElement()));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(okClickedSlot()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SIGNAL(canselClicked()));
    //connect(this,SIGNAL())



}

UserPenStyle::~UserPenStyle()
{
    delete ui;
}

void UserPenStyle::closeEvent(QCloseEvent *e)
{
    emit canselClicked();
    QDialog::closeEvent(e);
}



void UserPenStyle::addElement()
{

    int countRow = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(countRow);;

    for(int i = 0; i<ui->tableWidget->columnCount();++i)
    {
        initCellValue(countRow,i);
    }

    createVectorPattern();

}

void UserPenStyle::changeOffset(qreal value)
{
    pen.setDashOffset(value);
    item->setPen(pen);
}

void UserPenStyle::deleteElement()
{
    auto tmp = ui->tableWidget->rowCount();
    ui->tableWidget->removeRow(tmp-1);
    createVectorPattern();
}

void UserPenStyle::okClickedSlot()
{
    style = "dash pattern=";
    QString onStr = " on ";
    QString offStr = " off ";
    for (int i =0;i<vector.size();++i)
    {
        if (i%2==0)
            style+=onStr;
        else
        {
            style+=offStr;
        }
        style+=QString::number(vector[i]);
    }
    style+=", dash phase=";
    style+=QString::number(pen.dashOffset());
    emit okClicked(style,vector,pen.dashOffset());
}



void UserPenStyle::initCellValue(int row, int column)
{


    auto tmpItem = ui->tableWidget->item(row,column);
    if(tmpItem==nullptr)
    {
        tmpItem = new QTableWidgetItem;
        ui->tableWidget->setItem(row,column,tmpItem);
    }
    tmpItem->setData(Qt::EditRole,row+column+1.1+row*column);


}

void UserPenStyle::initTableValues()
{
    int countRow = ui->tableWidget->rowCount();
    int countColumn = ui->tableWidget->columnCount();
    for(int i = 0; i<countRow;++i)
        for(int j =0;j<countColumn;++j)
        {

            initCellValue(i, j);

        }
}

void UserPenStyle::createVectorPattern()
{
    vector.clear();
    int countRow = ui->tableWidget->rowCount();
    int countColumn = ui->tableWidget->columnCount();
    for(int i = 0; i<countRow;++i)
        for(int j =0;j<countColumn;++j)
        {
            auto tmpItem = ui->tableWidget->item(i,j);
            if(tmpItem==nullptr)
            {
                tmpItem = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,tmpItem);
                tmpItem->setData(Qt::EditRole,i+j+1.1+i*j);

            }
            auto tmpValue = tmpItem->data(Qt::EditRole);
            vector << qvariant_cast<qreal>(tmpValue);

        }
    if(vector.size()%2!=0)
        vector.remove(vector.size()-1);
    pen.setDashPattern(vector);
    item->setPen(pen);
}


