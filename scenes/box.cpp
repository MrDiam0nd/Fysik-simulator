#include "box.h"
#include "CameraManager.h"
#include "objekt.h"
#include <vector>
#include "math.h"

Boxscene::Boxscene(){
    return;
}

Boxscene::fn(){
    float DeltaTime = GetFrameTime();
    time += DeltaTime;

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
        cirklar[i].update(DeltaTime);
    }

    BeginDrawing();
        ClearBackground(SKYBLUE);
        //BeginMode2D(mainCamera.GetCamera());
        for(int i = 0; i<cirklar.size(); i++){
            cirklar[i].draw();
        }
        //EndMode2D();
    EndDrawing();

    return 0;
}