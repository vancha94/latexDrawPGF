#include "latextext.h"
#include "ui_latextextnew.h"

LatexText::LatexText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LatexTextNew)
{
    ui->setupUi(this);
     middleStr = "\n";
     ui->plainText->setReadOnly(true);
     ui->pushButton->setIcon(QIcon(":/icons/copy.png"));
}

LatexText::~LatexText()
{
    delete ui;
}

void LatexText::addText(QString str)
{
    ui->plainText->clear();
    middleStr+= str  + "\n";
    QString tmpStr ;
    if(str!="")
        tmpStr  = startStr +  str + endStr;
    else tmpStr="";
    ui->plainText->insertPlainText(tmpStr);
}
