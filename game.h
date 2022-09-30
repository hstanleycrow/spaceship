#ifndef ASTEROIDS_GAME_H_
#define ASTEROIDS_GAME_H_

class Game
{
private:
    int points;
    bool gameStatus;
    void changeStatus(bool);

public:
    Game();
    ~Game();
    void start();
    void stop();
    bool isActive();
    void setPoints(int);
    void addPoints(int);
    void play();
    const int getPoints();
};

#endif /*ASTEROIDS_GAME_H_*/