#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

const int screenWidth = 700;
const int screenHeight = 700;
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
        void draw();
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

    std::vector<Circle> cirklar;
    cirklar.push_back(Circle(RED,50,screenWidth/2 +200,screenHeight/2,0,-100));
    cirklar.push_back(Circle(ORANGE,50,screenWidth/2 -200,screenHeight/2,0,100));
    cirklar.push_back(Circle(YELLOW,50,screenWidth/2,screenHeight/2 +200,100,0));
    cirklar.push_back(Circle(GREEN,50,screenWidth/2,screenHeight/2 -200,-100,0));
    cirklar.push_back(Circle(BLUE,50,screenWidth/2+200,screenHeight/2+200,100,-100));
    cirklar.push_back(Circle(PURPLE,50,screenWidth/2+200,screenHeight/2-200,-100,-100));
    cirklar.push_back(Circle(PINK,50,screenWidth/2-200,screenHeight/2+200,100,100));
    cirklar.push_back(Circle(DARKPURPLE,50,screenWidth/2-200,screenHeight/2-200,-100,100));

    while(!WindowShouldClose()){
        float DeltaTime = GetFrameTime();

        for(int i = cirklar.size(); i>0;i--){
            for(int j = 0; j<i;j++){
                Gravity(cirklar[i],cirklar[j]);
            }
        }

        for(int i = 0; i<cirklar.size(); i++){
            cirklar[i].update(DeltaTime);
        }

        BeginDrawing();
            ClearBackground(SKYBLUE);
            for(int i = 0; i<cirklar.size(); i++){
                cirklar[i].draw();
            }
        EndDrawing();
    }

    return 0;
}