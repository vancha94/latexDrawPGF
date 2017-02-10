#include "latextext.h"

LatexText::LatexText(QWidget *parent):QPlainTextEdit(parent)
{
    middleStr = "\n";
}

void LatexText::addText(QString str)
{
    clear();
    middleStr+= str  + "\n";
    QString tmpStr ;
    if(str!="")
        tmpStr  = startStr +  str + endStr;
    else tmpStr="";
    insertPlainText(tmpStr);
}
