#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <QVector>
#include <QKeyEvent>
#include <QEvent>

enum Dir
{
    Up,
    Down,
    Left,
    Right,
};

class food
{
private:
    int x;
    int y;
public:
    food();
    ~food();
    void reCreate();
    int getX()const { return x; }
    int getY()const { return y; }
};

class snake
{
public:
    struct SNode
    {
        int x;
        int y;
        SNode(int xx, int yy) :x(xx), y(yy) {}
    };
private:
    QVector<SNode*> body;
    int rand_dir;

public:
    snake(int len = 3);
    ~snake();
    Dir dir;
//    QEvent event;
    void move();
    bool isValid();
    bool isFoodAte(food* f);
    void merge(food* f);
    QVector<SNode*>& getBody() { return body; }
    void setDir(Dir d) { dir = d; }
};

#endif // SNAKE_H
