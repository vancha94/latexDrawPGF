#ifndef COLORLATEXWIDGET_H
#define COLORLATEXWIDGET_H


#include <./include/color_palette_widget.hpp>
#include <./include/ColorPreview>
#include <QWidget>
//#include <map>

namespace Ui {
    class colorLatexWidget;
}

class ColorLatexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorLatexWidget(bool white = 0,QWidget *parent = 0);
    ~ColorLatexWidget();
public Q_SLOTS:
    void changePalette(int saturation);
    void changeColor(QColor color);


signals:
    void colorChanged(QColor color, QString nameColor);
    void saturationChanged(int saturation);

private: //methods
    void setLatexPalette();
    void addColor(QColor color, QString nameColor);


private:
    Ui::colorLatexWidget *ui;
    color_widgets::ColorPaletteWidget *colorWidget;
    color_widgets::ColorPalette palette;
    color_widgets::ColorPaletteModel *paletteModel;
    QHash<QColor,QString> latexColors;
    color_widgets::ColorPreview *preview;
//     std::map<QColor,QString> latexColors;

    void addLatexColors();
};

#endif // COLORLATEXWIDGET_H
