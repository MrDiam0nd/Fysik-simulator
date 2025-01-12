#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

#include "objekt.h"
#include "matte.h"

const int screenWidth = 700;
const int screenHeight = 700;
const float G = 10000;

int main(){
    InitWindow(screenWidth,screenHeight,"Fysik");

    //SetTargetFPS(60);

    std::vector<Circle> cirklar;

    float time = 0;

    cirklar.push_back(Circle(PURPLE,30,screenWidth/2,screenHeight/2,0,0,0.9));

    while(!WindowShouldClose()){
        //float DeltaTime = GetFrameTime();
        float DeltaTime  = 0.005;
        time += DeltaTime;
        //std::cout << DeltaTime << std::endl;

        if(time/0.5 > 1){
            cirklar.push_back(Circle(RED,30,rand()%screenWidth,rand()%screenHeight,0,0,0.9));
            time -= 0.5;
        }
        
        /*
        
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
            if(cirklar[i].pos.y+cirklar[i].radius > screenHeight){
                cirklar[i].pos.y = screenHeight-cirklar[i].radius;
                if(cirklar[i].vel.y > 0){
                    cirklar[i].vel.y *= -0.9;
                }
            }
        }
        /* */

        for(int i = cirklar.size()-1; i>0;i--){
            for(int j = 0; j<i;j++){
                Collision(cirklar[i],cirklar[j]);
            }
        }

        /* */
        for(int i = cirklar.size()-1; i>0;i--){
            for(int j = 0; j<i;j++){
                Gravity(cirklar[i],cirklar[j],G);

            }
        }
        /*
        for(int i = 0; i<cirklar.size(); i++){
            cirklar[i].vel.y += 1;
        }
        /**/
        std::cout << "xvel:" << cirklar[0].vel.x << " yvel:" << cirklar[0].vel.y << " force: "<< cirklar[0].force.x << " " << cirklar[0].force.y << "       ";

        for(int i = 0; i<cirklar.size(); i++){
            cirklar[i].update(DeltaTime);
        }

        std::cout << "xvel:" << cirklar[0].vel.x << " yvel:" << cirklar[0].vel.y << std::endl;

        BeginDrawing();
            ClearBackground(SKYBLUE);
            for(int i = 0; i<cirklar.size(); i++){
                cirklar[i].draw();
            }
        EndDrawing();

        if(isnan(cirklar[0].pos.x)){
            CloseWindow();
        }
    }

    return 0;
}