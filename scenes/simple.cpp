#include "simple.h"

#include "CameraManager.h"
#include "objekt.h"
#include <vector>
#include "math.h"

Simplescene::Simplescene(){

    cirklar.push_back(Circle(RED,50,0,100,0,-60,1));
    cirklar.push_back(Circle(RED,50,200,100,0,60,1));
    cirklar.push_back(Circle(RED,50,1700,1700,rand()%100 - 50,rand()%100 - 50,1));
    return;
}

int Simplescene::fn(){
    float DeltaTime = GetFrameTime();
    time += DeltaTime;

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

    for(int i = 0; i<cirklar.size(); i++){
        cirklar[i].update(DeltaTime);
    }

    BeginDrawing();
        ClearBackground(GREEN);
        BeginMode2D(mainCamera.GetCamera());
        for(int i = 0; i<cirklar.size(); i++){
            cirklar[i].draw();
        }
        EndMode2D();
    EndDrawing();

    return 0;
}