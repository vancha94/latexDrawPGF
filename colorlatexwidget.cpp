#include "colorlatexwidget.h"
#include "ui_colorlatexwidget.h"
#include <QDebug>

uint qHash(const QColor &color, uint seed)
{
    uint key = color.rgb();
    return qHash(key,seed);
}

ColorLatexWidget::ColorLatexWidget(bool white, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::colorLatexWidget)
{
    ui->setupUi(this);

    setLatexPalette();

    connect(ui->verticalSlider,SIGNAL(valueChanged(int)),this,SLOT(changePalette(int)));

    resize(this->minimumSize());
    setWindowFlags(Qt::Popup);

    if(white)
        colorWidget->setCurrentColor(70);
}

ColorLatexWidget::~ColorLatexWidget()
{
    delete ui;
    delete colorWidget;
    delete paletteModel;
}

void ColorLatexWidget::changePalette(int saturation)
{
    auto tmpColor = colorWidget->currentColor();
    tmpColor.setAlpha(saturation);

    preview->setColor(tmpColor);
    emit saturationChanged(saturation);;
}

void ColorLatexWidget::changeColor(QColor color)
{
    auto tmpStr = latexColors[color];
    color.setAlpha(ui->verticalSlider->value());

    preview->setColor(color);

    emit colorChanged(color,tmpStr);
}

void ColorLatexWidget::addLatexColors()
{
    addColor(QColor("#dfe573"),"GreenYellow");
    addColor(QColor("#fff101"),"Yellow");
    addColor(QColor("#ffde41"),"Goldenrod");
    addColor(QColor("#fdbb43"),"Dandelion");
    addColor(QColor("#fab780"),"Apricot");
    addColor(QColor("#f79559"),"Peach");
    addColor(QColor("#f79e7c"),"Melon");
    addColor(QColor("#f9a21c"),"YellowOrange");
    addColor(QColor("#f48038"),"Orange");
    addColor(QColor("#f6911e"),"BurntOrange");
    addColor(QColor("#c04f16"),"Bittersweet");
    addColor(QColor("#f16034"),"RedOrange");
    addColor(QColor("#a9331f"),"Mahogany");
    addColor(QColor("#ad3136"),"Maroon");
    addColor(QColor("#b6301c"),"BrickRed");
    addColor(QColor("#ee1d23"),"Red");
    addColor(QColor("#ff0000"),"red");
    addColor(QColor("#ee1059"),"OrangeRed");
    addColor(QColor("#ed027d"),"RubineRed");
    addColor(QColor("#ed2268"),"WildStrawberry");
    addColor(QColor("#f49188"),"Salmon");
    addColor(QColor("#f181b2"),"CarnationPink");
    addColor(QColor("#ed028c"),"Magenta");
    addColor(QColor("#ef56a0"),"VioletRed");
    addColor(QColor("#ee549f"),"Rhodamine");
    addColor(QColor("#a93b94"),"Mulberry");
    addColor(QColor("#9f236c"),"RedViolet");
    addColor(QColor("#8b368c"),"Fuchsia");
    addColor(QColor("#f49dc4"),"Lavender");
    addColor(QColor("#d782b7"),"Thistle");
    addColor(QColor("#af72af"),"Orchid");
    addColor(QColor("#a3538a"),"DarkOrchid");
    addColor(QColor("#98479b"),"Purple");
    addColor(QColor("#90268f"),"Plum");
    addColor(QColor("#59439b"),"Violet");
    addColor(QColor("#623e99"),"RoyalPurple");
    addColor(QColor("#483a94"),"BlueViolet");
    addColor(QColor("#7a77b8"),"Periwinkle");
    addColor(QColor("#747399"),"CadetBlue");
    addColor(QColor("#3eafe4"),"CornflowerBlue");
    addColor(QColor("#006794"),"MidnightBlue");
    addColor(QColor("#006eb8"),"NavyBlue");
    addColor(QColor("#0072bc"),"RoyalBlue");
    addColor(QColor("#2e3092"),"Blue");
    addColor(QColor("#0000ff"),"blue");
    addColor(QColor("#00a3e3"),"Cerulean");
    addColor(QColor("#00aeef"),"Cyan");
    addColor(QColor("#00b0ef"),"ProcessBlue");
    addColor(QColor("#47c4dc"),"SkyBlue");
    addColor(QColor("#00b4cd"),"Turquoise");
    addColor(QColor("#00afb3"),"TealBlue");
    addColor(QColor("#00b5bd"),"Aquamarine");
    addColor(QColor("#00b3b8"),"BlueGreen");
    addColor(QColor("#00a99d"),"Emerald");
    addColor(QColor("#00a99a"),"JungleGreen");
    addColor(QColor("#2dbc9d"),"SeaGreen");
    addColor(QColor("#00a54f"),"Green");
    addColor(QColor("#00ff00"),"green");
    addColor(QColor("#009a55"),"ForestGreen");
    addColor(QColor("#008a73"),"PineGreen");
    addColor(QColor("#8bc63e"),"LimeGreen");
    addColor(QColor("#97cd6f"),"YellowGreen");
    addColor(QColor("#c6db66"),"SpringGreen");
    addColor(QColor("#3a7f32"),"OliveGreen");
    addColor(QColor("#973f05"),"RawSienna");
    addColor(QColor("#671600"),"Sepia");
    addColor(QColor("#7a2500"),"Brown");
    addColor(QColor("#d99c75"),"Tan");
    addColor(QColor("#939598"),"Gray");
    addColor(QColor("#000000"),"Black");
    addColor(QColor("#ffffff"),"White");
}

void ColorLatexWidget::setLatexPalette()
{
    int paletteColumns = 17;
    palette.setColumns(paletteColumns);
    palette.setName("Палитра цветов");
    addLatexColors();

    paletteModel=new color_widgets::ColorPaletteModel();
    paletteModel->addPalette(palette);
    paletteModel->updatePalette(0,palette);

    preview=new color_widgets::ColorPreview(ui->preview);
    colorWidget = new color_widgets::ColorPaletteWidget(ui->widget);
    colorWidget->setModel(paletteModel);

    connect(colorWidget,SIGNAL(currentColorChanged(QColor)),this,SLOT(changeColor(QColor)));
    colorWidget->setReadOnly(true);
    colorWidget->setCurrentColor(69);

    preview->setDisplayMode(color_widgets::ColorPreview::SplitAlpha);
    preview->resize(300,32);

    colorWidget->resize(300,200);
}

void ColorLatexWidget::addColor(QColor color, QString nameColor)
{
    palette.appendColor(color,nameColor);
    latexColors[color] = nameColor;
}
