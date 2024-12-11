#include "raylib.h"
#include <iostream>
#include <math.h>

const int screenWidth = 400;
const int screenHeight = 400;
const float G = 10;

class Obj{
    public:
        float x;
        float y;
        float xVel;
        float yVel;
        float xAcc;
        float yAcc;
        float xF;
        float yF;
        float mass;
};

class Circle: public Obj{
    public:
        Circle(Color colorn = RED,float radiusn = 50, float xn = 0, float yn = 0,float xVeln = 0,float yVeln = 0){
            color = colorn;
            radius = radiusn;
            x = xn;
            y = yn;
            xVel = xVeln;
            yVel = yVeln;
            mass = radius*radius*PI;
        }

        Color color;
        float radius;

        void draw(){
            DrawCircle(x,y,radius,color);
        }
        void update(float dt){
            xAcc += xF / mass;
            yAcc += yF / mass;

            xVel += xAcc * dt * 0.5;
            yVel += yAcc * dt * 0.5;

            x += xVel*dt;
            y += yVel*dt;

            xVel += xAcc * dt * 0.5;
            yVel += yAcc * dt * 0.5;

            xF = 0;
            yF = 0;
            xAcc = 0;
            yAcc = 0;

        }
};

int Gravity(Obj &obj0,Obj &obj1){
    float dx = obj0.x-obj1.x;
    float dy = obj0.y-obj1.y;
    float distance = sqrt(pow((dx),2)+pow((dy),2));
    float F = G * obj0.mass * obj1.mass / distance;
    //F=ma
    //vilket håll

    dx = dx*F/distance;
    dy = dy*F/distance;

    obj1.xF += dx;
    obj0.xF -= dx;
    obj1.yF += dy;
    obj0.yF -= dy;

    return F;
}


int main(){
    InitWindow(screenWidth,screenHeight,"Fysik");

    Circle boll0(RED,50.0f,screenWidth,screenHeight/2,0.0f,100.0f);
    Circle boll1(GREEN,50.0f,0.0f,screenHeight/2,0.0f,-100.0f);

    while(!WindowShouldClose()){
        float DeltaTime = GetFrameTime();

        Gravity(boll0,boll1);

        boll0.update(DeltaTime);
        boll1.update(DeltaTime);

        BeginDrawing();
            ClearBackground(SKYBLUE);
            boll0.draw();
            boll1.draw();
        EndDrawing();
    }

    return 0;
}