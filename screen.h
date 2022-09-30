#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
private:
    int posX, posY;

public:
    Screen();
    void hideCursor();
    void hideScrollbars();
    void disableMaximize();
    void drawScreenLimitBorders();
    void clearScreen();
    void moveTo(const int, const int);
    void setScreenSize(const int, const int);
    void setPosX(const int);
    void setPosY(const int);
    void message(std::string);
    void message(int, int, std::string);
    void message(int, int, char);
    void message(int, int, std::string color, char caracter);
    void message(int, int, std::string color, std::string mensaje);
    const int *getPosX() const;
    const int *getPosY() const;
};

#endif /*SCREEN_H*/