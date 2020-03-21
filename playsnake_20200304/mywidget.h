#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QVector>
#include "snake.h"
#include "subwidget.h"

#define WIDTH	640
#define HEIGHT	480
#define STEP	20
#define X_RANGE	(WIDTH / STEP)
#define Y_RANGE (HEIGHT / STEP)
#define SNAKE_INITIAL_LEN	10

QT_BEGIN_NAMESPACE
namespace Ui { class MyWidget; }
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    void paintEvent(QPaintEvent *);
    void refresh();
    void restart();
    void exit();
private:
    Ui::MyWidget *ui;
    snake *mysnake;
    food *myfood;
    QTimer *timer;
    SubWidget *subw;

protected:
    virtual void keyPressEvent(QKeyEvent *event);
protected slots:

};
#endif // MYWIDGET_H
