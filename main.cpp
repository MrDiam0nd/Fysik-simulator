#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

#include "objekt.h"
#include "matte.h"
#include "CameraManager.h"
#include "experiment.h"
#include "space.h"
#include "box.h"
#include "menu.h"

const int screenWidth = 700;
const int screenHeight = 700;

int check_nans(std::vector<Circle> cirklar){
    for(int i = 0; i< cirklar.size();i++){
            bool errorpos = isnan(cirklar[i].pos.x);
            bool errorvel = isnan(cirklar[i].vel.x);
            bool erroracc = isnan(cirklar[i].acc.x);
            bool errorforce = isnan(cirklar[i].force.x);
            if(!errorpos && !errorvel && !erroracc && !errorforce){
                continue;
            }
            std::cout << "cirkel " << i << std::endl;
            if(isnan(cirklar[i].pos.x) || isnan(cirklar[i].pos.y)){
                std::cout << "     error pos: " << cirklar[i].pos.x << "  " << cirklar[i].pos.y << std::endl;
            }
            if(isnan(cirklar[i].vel.x) || isnan(cirklar[i].vel.y)){
                std::cout << "     error vel: " << cirklar[i].vel.x << "  "<< cirklar[i].vel.y << std::endl;
            }
            if(isnan(cirklar[i].acc.x) || isnan(cirklar[i].acc.y)){
                std::cout << "     error acc: " << cirklar[i].acc.x << "  " << cirklar[i].acc.y << std::endl;
            }
            if(isnan(cirklar[i].force.x) || isnan(cirklar[i].force.y)){
                std::cout << "     error force: " << cirklar[i].force.x << "  " << cirklar[i].force.y << std::endl;
            }
        }
    return 0;
}

int main(){
    InitWindow(screenWidth,screenHeight,"Fysik");
    enum gamestate gs = MENU;
    //SetTargetFPS(60);

    Trianglescene trianglescene;
    Spacescene spacescene;
    Boxscene boxscene;
    Menuscene menuscene;

    while(!WindowShouldClose())
    {
        if(IsKeyDown(KEY_S)){
            gs = SPACE;
        }
        if(IsKeyDown(KEY_B)){
            gs = BOX;
        }
        if(IsKeyDown(KEY_M)){
            gs = MENU;
        }
        if(IsKeyDown(KEY_T)){
            gs = TRI;
        }

        if(gs == MENU){
            menuscene.fn(gs);
        }
        if(gs == SPACE){
            spacescene.fn();
        }
        if(gs == BOX){
            boxscene.fn();
        }
        if(gs == TRI){
            trianglescene.fn();
        }
    }
    CloseWindow();
    return 0;
}