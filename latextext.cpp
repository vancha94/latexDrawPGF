#include "latextext.h"
#include "ui_latextextnew.h"

#include <QClipboard>

LatexText::LatexText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LatexTextNew)
{
    ui->setupUi(this);
    middleStr = "\n";
    ui->plainText->setReadOnly(true);
    ui->pushButton->setIcon(QIcon(":/icons/copy.png"));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(buttonCliked()));
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
    QTextCursor cursor = ui->plainText->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->plainText->setTextCursor(cursor);
}

void LatexText::buttonCliked()
{
    QClipboard *cp = QApplication::clipboard();
    auto tmp = ui->plainText->toPlainText();
    if (tmp!="")
        cp->setText(tmp);
}
