
#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

#include "matte.h"
#include "objekt.h"

const int screenWidth = 700;
const int screenHeight = 700;

int main(){
    InitWindow(screenWidth,screenHeight,"Fysik");

    Triangle tri(BLACK,{0,100},{100,0},{-100,0},350,350,0,0,0,1,0);

    while(!WindowShouldClose()){
        float DeltaTime = GetFrameTime();

        tri.update(DeltaTime);

        BeginDrawing();
            ClearBackground(SKYBLUE);
            tri.draw();
        EndDrawing();
    }
}