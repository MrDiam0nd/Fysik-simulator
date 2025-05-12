#include "menu.h"
#include "raylib.h"

Button::Button(Vector2 posn, Vector2 sizen, Color colorn, Color color2n){
    pos = posn;
    size = sizen;
    color = colorn;
    color2 = color2n;
    return;
}

bool Button::check(){
    bool R = false;
    Vector2 mousepos = GetMousePosition();
    if(mousepos.x >= pos.x && mousepos.x <= pos.x + size.x && mousepos.y >= pos.y && mousepos.y <= pos.y + size.y){
        hovered = true;
        if(IsMouseButtonPressed(0)){
            R = true;
        }
    }else{
        hovered = false;
    }
    return R;
}

void Button::draw(){
    if(hovered){
        DrawRectangle(pos.x,pos.y,size.x,size.y,color2);
    }else{
        DrawRectangle(pos.x,pos.y,size.x,size.y,color);
    }
}

Menuscene::Menuscene() : 
        Spacebtn({100,50},{100,100},RED,BLUE) ,
        Boxbtn({100,250},{100,100},RED,BLUE) ,
        Expbtn({100,450},{100,100},RED,BLUE) ,
        Quitbtn({100,650},{100,100},RED,BLUE) 
{
    return;
}

int Menuscene::fn(gamestate &gs){
    if(Spacebtn.check()){
        gs = SPACE;
    }
    if(Boxbtn.check()){
        gs = BOX;
    }
    if(Quitbtn.check()){
        
    }
    if(Expbtn.check()){
        gs = EXP;
    }
    BeginDrawing();
        ClearBackground(SKYBLUE);
        Spacebtn.draw();
        Boxbtn.draw();
        Quitbtn.draw();
        Expbtn.draw();
    EndDrawing();
    return 0;
}
