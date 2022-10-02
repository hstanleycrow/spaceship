/**
 * Desarrollado por Harold Crow
 * Septiembre 2022
 * */
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <list>
#include "config.h"
#include "game.h"
#include "screen.h"
#include "ship.h"
#include "shoot.h"
#include "asteroid.h"

// using namespace std;
using namespace Config;

int main()
{
    Game game;
    int points = 0;
    char gameKeyPressed;
    char mainKeyPressed;

    Screen screen;
    Ship gameShip;
    std::list<Shoot *> shoots;
    std::list<Shoot *>::iterator itShoots;

    std::list<Asteroid *> asteroids;
    std::list<Asteroid *>::iterator itAsteroids;

    bool waitMessage = true;
    bool exitGame = false;
    screen.clearScreen();
    while (waitMessage)
    {
        if (waitMessage && game.isActive() == false)
        {
            screen.message((RIGHTLIMIT / 2) - 23, (BOTTOMLIMIT / 2), "PRESS <ENTER> TO START A NEW GAME OR ESC TO EXIT");
        }
        if (kbhit())
        {
            fflush(stdin);
            mainKeyPressed = getch();
            if (game.isActive() == false)
            {
                if (mainKeyPressed == ENTER)
                {
                    screen.message((RIGHTLIMIT / 2) - 23, (BOTTOMLIMIT / 2), "                                                                         ");
                    screen.message(4, 2, "Points");
                    // screen.moveTo((RIGHTLIMIT / 2) - 23, (BOTTOMLIMIT / 2));
                    // printf("                                                                         ");
                    game.start();
                    //  se coloca la nave
                    gameShip.setLives();
                    gameShip.setPos((RIGHTLIMIT / 2), (BOTTOMLIMIT - gameShip.getShipHeight()));
                    gameShip.render();
                    gameShip.renderLives();
                    gameShip.renderHearts();
                    // se colocan los asteroides
                    for (int i = 0; i < 5; i++)
                    {
                        asteroids.push_back(new Asteroid());
                    }
                    for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
                    {
                        (*itAsteroids)->set();
                    }
                }
                if (mainKeyPressed == ESC)
                {
                    waitMessage = false;
                }
            }
            while (game.isActive())
            {
                if (kbhit())
                {
                    fflush(stdin);
                    gameKeyPressed = getch();
                    //   si se dispara, se pone dibuja el disparo
                    if (gameKeyPressed == SPACE)
                    {
                        shoots.push_back(new Shoot());
                        itShoots = shoots.end();
                        itShoots--;
                        (*itShoots)->setPos(*gameShip.getPosX() + 2, *gameShip.getPosY() - 1);
                    }
                    if (gameKeyPressed == ESC)
                    {
                        exitGame = true;
                        for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
                        {
                            delete (*itAsteroids);
                            itAsteroids = asteroids.erase(itAsteroids);
                        }
                    }
                    if (gameKeyPressed == KEYLEFT || gameKeyPressed == KEYRIGHT || gameKeyPressed == KEYUP || gameKeyPressed == KEYDOWN || gameKeyPressed == 'e')
                        gameShip.move(gameKeyPressed);
                } // end kbhit game
                if (game.isActive())
                {
                    gameShip.renderLives();
                    screen.message(11, 2, std::to_string(game.getPoints()), "yellow");
                    for (itShoots = shoots.begin(); itShoots != shoots.end(); itShoots++)
                    {
                        (*itShoots)->move();
                        if ((*itShoots)->outLimits())
                        {
                            // Se borra el disparo
                            (*itShoots)->del();
                            // se borra el puntero al disparo
                            delete (*itShoots);
                            // se borra de la lista tambien para que no quede el espaci
                            itShoots = shoots.erase(itShoots);
                        }
                    }
                    // se mueven los asteroides y si chocan con la nave se restan corazones y/o vidas
                    for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
                    {
                        (*itAsteroids)->move();
                        if (*(*itAsteroids)->getPosX() >= *gameShip.getPosX() && *(*itAsteroids)->getPosX() < (*gameShip.getPosX() + 6) && *(*itAsteroids)->getPosY() >= *gameShip.getPosY() && *(*itAsteroids)->getPosY() < (*gameShip.getPosY() + 2))
                        {
                            (*itAsteroids)->del();
                            delete (*itAsteroids);
                            itAsteroids = asteroids.erase(itAsteroids);
                            // screen.message("Me dieron");
                            gameShip.shipCrash();
                            asteroids.push_back(new Asteroid());
                            itAsteroids = asteroids.end();
                            itAsteroids--;
                            (*itAsteroids)->set();
                        }
                    }
                    // se verifica si los asteroides chocan con algun disparo, si es asi, se borran y se crea un nuevo asteroide
                    for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
                    {
                        for (itShoots = shoots.begin(); itShoots != shoots.end(); itShoots++)
                        {
                            // se verifica si hay colision entre disparo y asteroide
                            if ((*(*itAsteroids)->getPosX() == *(*itShoots)->getPosX()) && (*(*itAsteroids)->getPosY() + 1 == *(*itShoots)->getPosY() || *(*itAsteroids)->getPosY() == *(*itShoots)->getPosY()))
                            {
                                game.addPoints(5);
                                // CODIGO REPETIDO
                                // Se borra el disparo
                                (*itShoots)->del();
                                // se borra el puntero al disparo
                                delete (*itShoots);
                                // se borra de la lista tambien para que no quede el espaci
                                itShoots = shoots.erase(itShoots);

                                // borrar el asteroide
                                (*itAsteroids)->del();
                                // se borra el puntero al disparo
                                delete (*itAsteroids);
                                // se borra de la lista tambien para que no quede el espaci
                                itAsteroids = asteroids.erase(itAsteroids);
                                // se crea un asteroide nuevo CODIGO REPETIDO
                                asteroids.push_back(new Asteroid());
                                itAsteroids = asteroids.end();
                                itAsteroids--;
                                (*itAsteroids)->set();
                            }
                        }
                    }
                    // gameShip.shipDies();
                    if (gameShip.getLives() == 0)
                    {
                        exitGame = true;
                    }
                    if (exitGame)
                    {
                        exitGame = false;
                        for (itAsteroids = asteroids.begin(); itAsteroids != asteroids.end(); itAsteroids++)
                        {
                            delete (*itAsteroids);
                            itAsteroids = asteroids.erase(itAsteroids);
                        }
                        screen.clearScreen();
                        game.stop();
                        waitMessage = true;
                        screen.message((RIGHTLIMIT / 2) - 10, (BOTTOMLIMIT / 2), "                                             ");
                        screen.message((RIGHTLIMIT / 2) - 8, (BOTTOMLIMIT / 2), "G A M E   O V E R", "red");
                        // printf("G A M E   O V E R");
                        Sleep(2000);
                        screen.clearScreen();
                        gameShip.~Ship();
                        // delete gameShipPtr;
                    }
                    Sleep(50);
                }
            } // end while game is active
        }     // endif kbhit()
    }

    return 0;
}