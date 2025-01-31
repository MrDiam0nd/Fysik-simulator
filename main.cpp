#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

#include "objekt.h"
#include "matte.h"

const int screenWidth = 700;
const int screenHeight = 700;
const float G = 100;

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

    //SetTargetFPS(60);

    std::vector<Circle> cirklar;

    float time = 0;

    // cirklar.push_back(Circle(PURPLE,20,screenWidth/2 - 250,screenHeight/2,0,100,0.9));
    // cirklar.push_back(Circle(RED,100,screenWidth/2 + 50,screenHeight/2,0,0,0.9));

    while(!WindowShouldClose()){
        float DeltaTime = GetFrameTime();
        //float DeltaTime  = 0.005;
        time += DeltaTime;

        if(time > 0.1){
            // cirklar.push_back(Circle(RED,10,350+(rand()%screenWidth)/100,0,0,0,0.9));
            cirklar.push_back(Circle(RED,10,rand()%screenWidth,rand()%screenHeight,0,0,0.95));
            time -= 0.1;
        }
        
        // for(int i = 0; i<cirklar.size(); i++){
        //     if(cirklar[i].pos.x-cirklar[i].radius < 0){
        //         cirklar[i].pos.x = 0+cirklar[i].radius;
        //         if(cirklar[i].vel.x < 0){
        //             cirklar[i].vel.x *= -0.9;
        //         }
        //     }
        //     if(cirklar[i].pos.x+cirklar[i].radius > screenWidth){
        //         cirklar[i].pos.x = screenWidth-cirklar[i].radius;
        //         if(cirklar[i].vel.x > 0){
        //             cirklar[i].vel.x *= -0.9;
        //         }
        //     }
        //     if(cirklar[i].pos.y-cirklar[i].radius < 0){
        //         cirklar[i].pos.y = 0+cirklar[i].radius;
        //         if(cirklar[i].vel.y < 0){
        //             cirklar[i].vel.y *= -0.9;
        //         }
        //     }
        //     if(cirklar[i].pos.y+cirklar[i].radius > screenHeight){
        //         cirklar[i].pos.y = screenHeight-cirklar[i].radius;
        //         if(cirklar[i].vel.y > 0){
        //             cirklar[i].vel.y *= -0.9;
        //         }
        //     }
        // }

        check_nans(cirklar);
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
        
        for(int i = cirklar.size()-1; i>0;i--){
            for(int j = 0; j<i;j++){
                Gravity(cirklar[i],cirklar[j],G);

            }
        }
        
        // for(int i = 0; i<cirklar.size(); i++){
        //     cirklar[i].vel.y += 1;
        // }
        /**/
        //std::cout << cirklar[0].pos.x<< cirklar[0].vel.x << std::endl;

        for(int i = 0; i<cirklar.size(); i++){
            cirklar[i].update(DeltaTime);
        }

        //std::cout <<"                  "<< cirklar[0].vel.x << std::endl;

        BeginDrawing();
            ClearBackground(SKYBLUE);
            for(int i = 0; i<cirklar.size(); i++){
                cirklar[i].draw();
            }
        EndDrawing();
    }

    return 0;
}