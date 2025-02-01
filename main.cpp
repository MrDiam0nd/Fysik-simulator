#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

#include "objekt.h"
#include "matte.h"
#include "CameraManager.h"

const int screenWidth = 700;
const int screenHeight = 700;
const float G = 100;

enum gamestate {
    MENU,
    SPACE,
    BOX
};

class Button {
    public:
    Vector2 pos;
    Vector2 size;
    Color color;
    Color color2;
    bool hovered;
    int (*function)();

    Button(Vector2 posn, Vector2 sizen, Color colorn, Color color2n){
        pos = posn;
        size = sizen;
        color = colorn;
        color2 = color2n;
        return;
    }

    bool check(){
        bool R = false;
        Vector2 mousepos = GetMousePosition();
        if(mousepos.x >= pos.x && mousepos.x <= pos.x + size.x && mousepos.y >= pos.y && mousepos.y <= pos.y + size.y){
            hovered = true;
            if(IsMouseButtonPressed(0)){
                R = true;
                function();
            }
        }
        return R;
    }

    void draw(){
        if(hovered){
            DrawRectangle(pos.x,pos.y,size.x,size.y,color2);
        }else{
            DrawRectangle(pos.x,pos.y,size.x,size.y,color);
        }
    }
};

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

int Spacefn(const float dt,std::vector<Circle> &cirklar,float &time){
    if(time > 0.1){
        cirklar.push_back(Circle(RED,10,rand()%screenWidth,rand()%screenHeight,0,0,0.95));
        time -= 0.1;
    }

    for(int i = cirklar.size()-1; i>0;i--){
        for(int j = 0; j<i;j++){
            Gravity(cirklar[i],cirklar[j],G);

        }
    }

    for(int i = cirklar.size()-1; i>0;i--){
        for(int j = 0; j<i;j++){
            Collision(cirklar[i],cirklar[j]);
        }
    }
    for(int i = cirklar.size()-1; i>0;i--){
        for(int j = 0; j<i;j++){
            Collision(cirklar[i],cirklar[j]);
        }
    }
    for(int i = cirklar.size()-1; i>0;i--){
        for(int j = 0; j<i;j++){
            Collision(cirklar[i],cirklar[j]);
        }
    }
    
    check_nans(cirklar);

    for(int i = 0; i<cirklar.size(); i++){
        cirklar[i].update(dt);
    }

    return 0;
}

int Boxfn(const float dt,std::vector<Circle> &cirklar,float &time){
    if(time > 0.1){
        cirklar.push_back(Circle(RED,10,rand()%screenWidth,rand()%screenHeight,0,0,0.95));
        time -= 0.1;
    }

    for(int i = 0; i<cirklar.size(); i++){
        cirklar[i].vel.y += 1;
    }

    for(int i = cirklar.size()-1; i>0;i--){
        for(int j = 0; j<i;j++){
            Collision(cirklar[i],cirklar[j]);
        }
    }
    for(int i = cirklar.size()-1; i>0;i--){
        for(int j = 0; j<i;j++){
            Collision(cirklar[i],cirklar[j]);
        }
    }
    for(int i = cirklar.size()-1; i>0;i--){
        for(int j = 0; j<i;j++){
            Collision(cirklar[i],cirklar[j]);
        }
    }

    for(int i = 0; i<cirklar.size(); i++){
        if(cirklar[i].pos.x-cirklar[i].radius < 0){
            cirklar[i].pos.x = 0+cirklar[i].radius;
            if(cirklar[i].vel.x < 0){
                cirklar[i].vel.x *= -0.9;
            }
        }
        if(cirklar[i].pos.x+cirklar[i].radius > screenWidth){
            cirklar[i].pos.x = screenWidth-cirklar[i].radius;
            if(cirklar[i].vel.x > 0){
                cirklar[i].vel.x *= -0.9;
            }
        }
        if(cirklar[i].pos.y-cirklar[i].radius < 0){
            cirklar[i].pos.y = 0+cirklar[i].radius;
            if(cirklar[i].vel.y < 0){
                cirklar[i].vel.y *= -0.9;
            }
        }
        if(cirklar[i].pos.y+cirklar[i].radius > screenHeight){
            cirklar[i].pos.y = screenHeight-cirklar[i].radius;
            if(cirklar[i].vel.y > 0){
                cirklar[i].vel.y *= -0.9;
            }
        }
    }

    for(int i = 0; i<cirklar.size(); i++){
        cirklar[i].update(dt);
    }

    return 0;
}

int Menufn(enum gamestate &gs,class Button &button){



    return 0;
}

int main(){
    InitWindow(screenWidth,screenHeight,"Fysik");
    enum gamestate gs = SPACE;
    //SetTargetFPS(60);
    CameraManager mainCamera;

    std::vector<Circle> cirklar;
    class Button button({100,100},{100,100},RED,BLUE);

    float time = 0;

    while(!WindowShouldClose()){
        float DeltaTime = GetFrameTime();
        //float DeltaTime  = 0.005;
        time += DeltaTime;

        if(IsKeyDown(KEY_S)){
            gs = SPACE;
        }
        if(IsKeyDown(KEY_B)){
            gs = BOX;
        }
        if(IsKeyDown(KEY_M)){
            gs = MENU;
        }

        if(gs == MENU){
            Menufn(gs,button);

            BeginDrawing();
                ClearBackground(SKYBLUE);
                button.draw();
            EndDrawing();
        }
        if(gs == SPACE){
            Spacefn(DeltaTime,cirklar,time);

            BeginDrawing();
                ClearBackground(BLACK);
                BeginMode2D(mainCamera.GetCamera());
                for(int i = 0; i<cirklar.size(); i++){
                    cirklar[i].draw();
                }
                EndMode2D();
            EndDrawing();
        }
        if(gs == BOX){
            Boxfn(DeltaTime,cirklar,time);

            BeginDrawing();
                ClearBackground(SKYBLUE);
                BeginMode2D(mainCamera.GetCamera());
                for(int i = 0; i<cirklar.size(); i++){
                    cirklar[i].draw();
                }
                EndMode2D();
            EndDrawing();
        }


        
    }
    CloseWindow();
    return 0;
}