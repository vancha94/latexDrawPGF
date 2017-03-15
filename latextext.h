#ifndef LATEXTEXT_H
#define LATEXTEXT_H

#include <QPlainTextEdit>


class LatexText : public QPlainTextEdit
{
    Q_OBJECT
public:
    LatexText(QWidget *parent);
private:
    const QString startStr = "%\\usepackage[dvipsnames]{xcolor}\n%\\usepackage{tikz}\n\\begin{tikzpicture}[scale=0.01]\n";
    const QString endStr = "\\end{tikzpicture}";
    QString middleStr;
public:
    void addText(QString str);
};

#endif // LATEXTEXT_H
