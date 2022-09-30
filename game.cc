#include "game.h"

Game::Game()
{
    gameStatus = false;
}

Game::~Game() {}

void Game::setPoints(int points)
{
    this->points = points;
}

void Game::addPoints(int points)
{
    this->points += points;
}

void Game::changeStatus(bool newStatus)
{
    gameStatus = newStatus;
};

void Game::start()
{
    setPoints(0);
    changeStatus(true);
}

void Game::stop()
{
    changeStatus(false);
}

bool Game::isActive()
{
    return gameStatus;
}
const int Game::getPoints() { return points; }

void play()
{
}