#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
//#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("snake");
    mysnake=new snake(SNAKE_INITIAL_LEN); //实例化
    myfood=new food;
    subw = new SubWidget;
    timer = new QTimer(this);
    resize(WIDTH,HEIGHT);
    setStyleSheet("QWidget{background:white}");
    setWindowOpacity(0.8);//设置窗口的透明度
//    this->grabKeyboard(); //获取键盘
//    setFocusPolicy(Qt::StrongFocus);
    connect(timer, &QTimer::timeout, this, &MyWidget::refresh);
    timer->start(200);
}

MyWidget::~MyWidget()
{
    delete ui;
    delete mysnake;
    delete myfood;
    delete subw;
}
void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    QFont font("方正舒体",12,QFont::ExtraLight,false);
    painter.setRenderHint(QPainter::Antialiasing);
    //绘制食物和蛇身
    pen.setColor(Qt::green);
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse((myfood->getX())* STEP + STEP / 2, (myfood->getY())* STEP + STEP / 2, STEP, STEP);

    for (int i = 1; i < mysnake->getBody().size()-1;i++)
    {
        painter.drawEllipse((mysnake->getBody()[i]->x)* STEP + STEP / 2, (mysnake->getBody()[i]->y)*STEP + STEP / 2, STEP,STEP);
    }
    //绘制蛇头
    pen.setColor(Qt::red);
    brush.setColor(Qt::red);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawEllipse((mysnake->getBody()[0]->x)* STEP + STEP / 2, (mysnake->getBody()[0]->y)*STEP + STEP / 2, STEP,STEP);  //蛇头
    //绘制蛇尾
    pen.setColor(Qt::blue);
    brush.setColor(Qt::blue);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawEllipse((mysnake->getBody()[mysnake->getBody().size() - 1]->x)* STEP + STEP / 2, (mysnake->getBody()[mysnake->getBody().size() - 1]->y)*STEP + STEP / 2, STEP,STEP);//蛇尾
    //绘制得分
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(20,20,QString("当前得分：")+QString("%1").arg(mysnake->getBody().length()-SNAKE_INITIAL_LEN));
}

void MyWidget::refresh()
{
    if (mysnake->isValid())
    {
        if (mysnake->isFoodAte(myfood))
        {
            mysnake->merge(myfood);
            myfood->reCreate();
        }
        mysnake->move();
        update();
    }
    else
    {
        this->hide();

        this->timer->stop();
        subw->show();
        connect(subw,&SubWidget::mysignal_1,this,&MyWidget::restart);
        connect(subw,&SubWidget::mysignal_2,this,&MyWidget::exit);
//        connect(subw,&SubWidget::mysignal,
//                [=](){
//                        subw->close();
//                     });

//        this->hide(); //此处主窗口关闭，发射信号至子窗口
    }
}

void MyWidget::exit()
{
    delete mysnake;
    delete myfood;
    timer->stop();
    subw->close();
    this->close();
    delete ui;
}

void MyWidget::restart()
{
    this->show();
    subw->close();
    if (mysnake!=nullptr)
    {
        delete mysnake;
    }
    mysnake=new snake(SNAKE_INITIAL_LEN);
    timer->start();
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    int keyvalue =event->key();
    switch (keyvalue)
    {
    case Qt::Key_Up:
        if (mysnake->dir!=Down)
        {
            mysnake->dir=Up;
        }
//        qDebug()<<"Down"<<endl;
        break;
    case Qt::Key_Down:
        if (mysnake->dir!=Up)
        {
            mysnake->dir=Down;
        }
//        qDebug()<<"UP"<<endl;
        break;
    case Qt::Key_Left:
        if (mysnake->dir!=Right)
        {
            mysnake->dir=Left;
        }
//        qDebug()<<"Left"<<endl;
        break;
    case Qt::Key_Right:
        if (mysnake->dir!=Left)
        {
            mysnake->dir=Right;
        }
//        qDebug()<<"Right"<<endl;
        break;
    case Qt::Key_Escape:
        this->close();
        subw->show();
        break;
    case Qt::Key_Space:
        if (this->timer->isActive())
            this->timer->stop();
        else {
            this->timer->start();
        }

    default:
//        dir = Left;
        break;
    }
}






