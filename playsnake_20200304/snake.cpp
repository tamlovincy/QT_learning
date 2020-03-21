#include "snake.h"
#include <iostream>
#include "mywidget.h"

#define ABS(x)	((x) > 0? (x) : (-(x)))

food::food()
{
    x = rand() % X_RANGE;
    y = rand() % Y_RANGE;
}

food::~food()
{
}

void food::reCreate()
{
    x = rand() % X_RANGE;
    y = rand() % Y_RANGE;
}

snake::snake(int len)
{
    for (int i = 0; i < len; ++i)
    {
        body.push_back(new SNode(X_RANGE/2 + i, Y_RANGE / 2));//初始化蛇的方向，向右生长
    }
    rand_dir=rand() % 4;
    dir = Dir(rand_dir); //随机产生方向
}

snake::~snake()
{
    for (int i = 0; i < body.size(); ++i)
    {
        delete body[i];
    }
}

void snake::move()
{
    for (int i = body.size() - 1; i > 0; --i)
    {
        body[i]->x = body[i - 1]->x;
        body[i]->y = body[i - 1]->y;
    }
    switch (dir)
    {
    case 0: //case UP
    {
        body[0]->y -= 1;
        if (body[0]->y < 0)
            body[0]->y = Y_RANGE - 1;
    }
    break;
    case 1: //case DOWN
    {
        body[0]->y += 1;
        if (body[0]->y >= Y_RANGE)
            body[0]->y = 0;
    }
    break;
    case 2: //case LEFT
    {
        body[0]->x -= 1;
        if (body[0]->x < 0)
            body[0]->x = X_RANGE - 1;
    }
    break;
    case 3: //case DOWN
    {
        body[0]->x += 1;
        if (body[0]->x >= X_RANGE)
            body[0]->x = 0;
    }
    break;
    default:
        break;
    }
}

bool snake::isValid()
{
    for (int i = 0; i < body.size(); ++i)
    {
        if (body[i]->x < 0 || body[i]->x >= X_RANGE || body[i]->y < 0 || body[i]->y >= Y_RANGE)
            return false;
    }
    for (int j = 0; j < body.size(); ++j)
    {
        for (int k = j + 1; k < body.size(); ++k)
        {
            if (body[j]->x == body[k]->x && body[j]->y == body[k]->y)
            {
                return false;
            }
        }
    }
    return true;
}

bool snake::isFoodAte(food * f)
{
    int diff_x = body[0]->x - f->getX();
    int diff_y = body[0]->y - f->getY();
    if (ABS(diff_x) + ABS(diff_y) == 1 ) //
    {
        if ((dir == Up&&diff_x == 0) || (dir == Down&&diff_x == 0)
            || (dir == Left&&diff_y == 0) || (dir == Right&&diff_y == 0))
            return true;
    }

    return false;
}

void snake::merge(food * f)
{
    if (isFoodAte(f))
    {
        SNode *node = new SNode(f->getX(), f->getY());
        body.insert(body.begin(), node);
    }
}


