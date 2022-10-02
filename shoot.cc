#include <iostream>
#include <conio.h>
#include <windows.h>
#include "config.h"
#include "shoot.h"

#define SPEED_SHOOT 1

Shoot::Shoot()
{
    setSpeed(SPEED_SHOOT);
}

Shoot::~Shoot() {}

const int *Shoot::getPosX() const { return Pos.getPosX(); };
const int *Shoot::getPosY() const { return Pos.getPosY(); };

void Shoot::setSpeed(int speed) { this->speed = speed; }

void Shoot::setPos(const int posX, const int posY)
{
    Pos.setPosX(posX);
    Pos.setPosY(posY);
}

void Shoot::del()
{
    Pos.message(*getPosX(), *getPosY(), " ");
}

void Shoot::move()
{
    del();
    if (*getPosY() > TOPLIMIT + 1)
    {
        Pos.setPosY(*getPosY() - 1);
    }
    Pos.message(*getPosX(), *getPosY(), 248, "bright_white");
}

bool Shoot::outLimits()
{
    if (*getPosY() == TOPLIMIT + 1)
    {
        return true;
    }
    return false;
}