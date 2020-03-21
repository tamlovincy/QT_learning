#include "subwidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
//#include "mywidget.h"
#include <QString>
#include <QTextEdit>

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("snake");
    b1=new QPushButton;
    b2=new QPushButton;
    resize(640,480);
    setStyleSheet("QWidget{background:white}");
    setWindowOpacity(0.8);//设置窗口的透明度

    b1->setParent(this);
    b1->setText("重新开始游戏？");
    b1->move(260,300);
//    this->setStyleSheet("color:blue");
    connect(b1,&QPushButton::clicked,this,&SubWidget::sendslot_1);
    b2->setParent(this);
    b2->setText("退出？");
    b2->move(270,350);
//    this->setStyleSheet("color:blue");
    connect(b2,&QPushButton::clicked,this,&SubWidget::sendslot_2);
}

void SubWidget::sendslot_1()
{
    emit mysignal_1();  //发送信号
}
void SubWidget::sendslot_2()
{
    emit mysignal_2();  //发送信号
}
void SubWidget::paintEvent(QPaintEvent *)
{

//    QTextEdit m_textedit(this);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    QFont font("方正舒体",30,QFont::ExtraLight,false);
    painter.setFont(font);
//    qDebug()<<"test!"<<endl;
    painter.drawText((this->width()-260)/2,(this->height()-30)/2,QString("GAME OVER!"));
//    m_textedit.setAlignment(Qt::AlignCenter);
//    this->setStyleSheet("color:red");
//    b1->setParent(this);
//    b1->setText("重新开始游戏？");
//    b1->move(200,200);

//    b1->show();
}
