#ifndef USERPENSTYLE_H
#define USERPENSTYLE_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QTableWidget>


namespace Ui {
    class UserPenStyle;
}

class UserPenStyle : public QDialog
{
    Q_OBJECT

public:
    explicit UserPenStyle(QWidget *parent = 0);
    ~UserPenStyle();

    void closeEvent(QCloseEvent *e);

private:
    Ui::UserPenStyle *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *item;
    QPen pen;
    QVector<qreal> vector;
    QString style;

signals:
    void okClicked(QString _style, QVector<qreal> _vector);
    void canselClicked();
private Q_SLOTS:
    void addElement();
    void changeOffset(qreal value);
    void deleteElement();
    void okClickedSlot();

private: // methods
    void initTableValues();
    void createVectorPattern();
    void initCellValue(int row, int column);
};

#endif // USERPENSTYLE_H
