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

    Circle boll0(RED,50.0f,screenWidth/2,screenHeight/2,0.0f,0.0f);
    Circle boll1(GREEN,50.0f,screenWidth/2 - 200,screenHeight/2,0.0f,-100.0f);
    Circle boll2(BLUE,50.0f,screenWidth/2,screenHeight/2 + 200,-100.0f,0.0f);
    Circle boll3(PURPLE,50.0f,screenWidth/2,screenHeight/2 - 210,100.0f,100.0f);

    std::vector<Circle> cirklar;
    cirklar.push_back(Circle(RED,50,screenWidth/2+100,screenHeight/2,0,0));
    cirklar.push_back(Circle(ORANGE,50,screenWidth/2+100,screenHeight/2,0,0));
    cirklar.push_back(Circle(YELLOW,50,screenWidth/2,screenHeight/2,0,0));
    cirklar.push_back(Circle(GREEN,50,screenWidth/2,screenHeight/2,0,0));
    cirklar.push_back(Circle(BLUE,50,screenWidth/2,screenHeight/2,0,0));
    cirklar.push_back(Circle(PURPLE,50,screenWidth/2,screenHeight/2,0,0));
    cirklar.push_back(Circle(PINK,50,screenWidth/2,screenHeight/2,0,0));

    Obj* update0 = &boll0;

    std::vector<Obj*> world;
    world.push_back(&boll0);
    world.push_back(&boll1);
    world.push_back(&boll2);
    world.push_back(&boll3);

    while(!WindowShouldClose()){
        float DeltaTime = GetFrameTime();

        Gravity(boll0,boll1);
        Gravity(boll0,boll2);
        Gravity(boll0,boll3);
        Gravity(boll1,boll2);
        Gravity(boll1,boll3);
        Gravity(boll2,boll3);

        for(int i = 0; i<world.size(); i++){
            world[i]->update(DeltaTime);
        }

        BeginDrawing();
            ClearBackground(SKYBLUE);
            boll0.draw();
            boll1.draw();
            boll2.draw();
            boll3.draw();
        EndDrawing();
    }

    return 0;
}