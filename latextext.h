#ifndef LATEXTEXT_H
#define LATEXTEXT_H

#include <QPlainTextEdit>


class LatexText : public QPlainTextEdit
{
    Q_OBJECT
public:
    LatexText();
private:
    const QString startStr = "\begin{tikzpicture}";
    const QString endStr = "\end{tikzpicture}";
    QString middleStr;
public slots:
    void addText(QString str);


};

#endif // LATEXTEXT_H
