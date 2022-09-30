#ifndef ASTEROIDS_SHOOT_H_
#define ASTEROIDS_SHOOT_H_

#include "screen.h"

class Shoot
{
private:
    Screen Pos;
    int speed;

public:
    Shoot();
    ~Shoot();
    void setSpeed(int);
    void move();
    bool outLimits();
    void setPos(const int, const int);
    void del();
    const int *getPosX() const;
    const int *getPosY() const;
};

#endif /*ASTEROIDS_SHOOT_H_*/