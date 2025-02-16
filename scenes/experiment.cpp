#include "experiment.h"
#include "objekt.h"

#include "raylib.h"
#include <math.h>
#include <vector>

Trianglescene::Trianglescene() : tri( BLACK,{0,100},{100,0},{-100,0},350,350,0,0,0,1,0)
{
    return;
}

Trianglescene::fn()
{
    float DeltaTime = GetFrameTime();

    tri.update(DeltaTime);

    BeginDrawing();
        ClearBackground(SKYBLUE);
        tri.draw();
    EndDrawing();
    return 0;
}
/*
int main(){
    InitWindow(screenWidth,screenHeight,"Fysik");
    Trianglescene trianglescene;
    while(!WindowShouldClose()){
        trianglescene.Trifn();
    }
}
*/