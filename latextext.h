#ifndef LATEXTEXTNEW_H
#define LATEXTEXTNEW_H

#include <QWidget>

namespace Ui {
    class LatexTextNew;
}

class LatexText : public QWidget
{
    Q_OBJECT

public:
    explicit LatexText(QWidget *parent = 0);
    ~LatexText();
    void addText(QString str);
private:
    const QString startStr = "%\\usepackage[dvipsnames]{xcolor}\n%\\usepackage{tikz}\n\\begin{tikzpicture}[scale=0.01]\n";
    const QString endStr = "\\end{tikzpicture}";
    QString middleStr;
private Q_SLOTS:
    void buttonCliked();

private:
    Ui::LatexTextNew *ui;
};

#endif // LATEXTEXTNEW_H
