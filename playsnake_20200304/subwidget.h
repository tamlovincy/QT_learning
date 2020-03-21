#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);


signals:
    void mysignal_1();
    void mysignal_2();

public slots:
    void sendslot_1(); //发送槽函数
    void sendslot_2(); //发送槽函数

private:
    QPushButton *b1;
    QPushButton *b2;

};

#endif // SUBWIDGET_H
