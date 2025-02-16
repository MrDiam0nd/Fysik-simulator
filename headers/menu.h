#pragma once

#include "raylib.h"

enum gamestate {
    MENU,
    SPACE,
    BOX,
    EXP,
    TRI
};

class Button {
    public:
    Vector2 pos;
    Vector2 size;
    Color color;
    Color color2;
    bool hovered;

    Button(Vector2 posn, Vector2 sizen, Color colorn, Color color2n);

    bool check();

    void draw();
};

class Menuscene{
    Button Spacebtn;
    Button Boxbtn;
    Button Expbtn;
    Button Quitbtn;

    public:

    Menuscene();

    int fn(gamestate &gs);
};