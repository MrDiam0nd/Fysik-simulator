#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

const int screenWidth = 700;
const int screenHeight = 700;
const float G = 10;

class Obj{
    public:
        Vector2 pos;
        Vector2 vel;
        Vector2 acc;
        Vector2 force;
        float mass;
        float elasticity;

        void update(float dt){
            acc.x += force.x / mass;
            acc.y += force.y / mass;

            vel.x += acc.x * dt * 0.5;
            vel.y += acc.y * dt * 0.5;

            pos.x += vel.x*dt;
            pos.y += vel.y*dt;

            vel.x += acc.x * dt * 0.5;
            vel.y += acc.y * dt * 0.5;

            force.x = 0;
            force.y = 0;
            acc.x = 0;
            acc.y = 0;

        }
        void draw();
};

class Circle: public Obj{
    public:
        Circle(Color colorn = RED,float radiusn = 50, float xn = 0, float yn = 0,float xVeln = 0,float yVeln = 0, float elasticityn =1){
            color = colorn;
            radius = radiusn;
            pos.x = xn;
            pos.y = yn;
            vel.x = xVeln;
            vel.y = yVeln;
            mass = radius*radius*PI;
            elasticity = elasticityn;
        }

        Color color;
        float radius;

        void draw(){
            DrawCircle(pos.x,pos.y,radius,color);
        }
        
};

int Gravity(Obj &obj0,Obj &obj1){
    float dx = obj0.pos.x-obj1.pos.x;
    float dy = obj0.pos.y-obj1.pos.y;
    float distance = sqrt(pow((dx),2)+pow((dy),2));
    float F = G * obj0.mass * obj1.mass / distance;
    //F=ma
    //vilket håll

    dx = dx*F/distance;
    dy = dy*F/distance;

    obj1.force.x += dx;
    obj0.force.x -= dx;
    obj1.force.y += dy;
    obj0.force.y -= dy;

    return F;
}

Vector2 translateVector(Vector2 V,Vector2 B0, Vector2 B1){
    Vector2 R;

    //B0.x * R.x + B1.x * R.y = V.x
    //B0.y * R.x + B1.y * R.y = V.y

    //R.y = (V.y - B0.y * ((V.x - B1.x * R.y) / B0.x)) / B1.y;
    //R.y = (V.y - B0.y * R.x) / B1.y

    //R.x = (V.x - B1.x * ((V.y - B0.y * R.x) / B1.y)) / B0.x;
    //R.x = (V.x - B1.x * R.y) / B0.x

    //B0.x * R.x + ( B1.x * V.y - B1.x * B0.y * R.x) / B1.y = V.x

    R.x = (V.x*B1.y-V.y*B1.x)/(B0.x*B1.y-B1.x*B0.y);
    R.y = (V.y - B0.y * R.x) / B1.y;

    return R;
}

Vector2 translateVectorBack(Vector2 V,Vector2 B0, Vector2 B1){
    Vector2 R;

    R.x = B0.x * V.x + B1.x * V.y;
    R.y = B0.y * V.x + B1.y * V.y;

    return R;
}

int Collision(Circle &C0, Circle &C1){
    float dx = C0.pos.x - C1.pos.x;
    float dy = C0.pos.y - C1.pos.y;
    float distance = sqrt(dx*dx+dy*dy);
    if(distance < C0.radius + C1.radius){
        
        float distbetween = distance - C0.radius - C1.radius;
        
        Vector2 base0 = {dx/distance,dy/distance};
        Vector2 base1 = {base0.y,-base0.x};

        C1.pos.x += base0.x * distbetween/2;
        C1.pos.y += base0.y * distbetween/2;
        C0.pos.x -= base0.x * distbetween/2;
        C0.pos.y -= base0.y * distbetween/2;

        Vector2 C0NewVel = translateVector(C0.vel,base0,base1);
        Vector2 C1NewVel = translateVector(C1.vel,base0,base1);

        C0NewVel.x *= C0.mass;
        C0NewVel.y *= C0.mass;
        C1NewVel.x *= C1.mass;
        C1NewVel.y *= C1.mass;

        float temp = C0NewVel.x;
        C0NewVel.x = C1NewVel.x;
        C1NewVel.x = temp;

       
        
        Vector2 C0back = translateVectorBack(C0NewVel,base0,base1);
        Vector2 C1back = translateVectorBack(C1NewVel,base0,base1);

        float combinedElasticity = ((C0.elasticity/2 + 0.5) + (C0.elasticity/2 + 0.5))/2;

        C0.vel.x = C0back.x * combinedElasticity + C1back.x * (1-combinedElasticity);
        C0.vel.y = C0back.y * combinedElasticity + C1back.y * (1-combinedElasticity);
        C1.vel.x = C1back.x * combinedElasticity + C0back.x * (1-combinedElasticity);
        C1.vel.y = C1back.y * combinedElasticity + C0back.y * (1-combinedElasticity);

        C0.vel.x /= C0.mass;
        C0.vel.y /= C0.mass;
        C1.vel.x /= C1.mass;
        C1.vel.y /= C1.mass;

        return 1;
    }
    return 0;
}

int main(){
    InitWindow(screenWidth,screenHeight,"Fysik");

    Vector2 res = translateVector(Vector2{4,2},Vector2{1,1},Vector2{1,-1});
    std::cout << res.x << " " << res.y << std::endl;

    std::vector<Circle> cirklar;
    cirklar.push_back(Circle(RED,100,screenWidth/2 +200,screenHeight/2,0,0,0.9));
    cirklar.push_back(Circle(ORANGE,50,screenWidth/2 -200,screenHeight/2,0,0,0.9));
    /*cirklar.push_back(Circle(YELLOW,50,screenWidth/2,screenHeight/2 +200,100,0,0.9));
    cirklar.push_back(Circle(GREEN,50,screenWidth/2,screenHeight/2 -200,-100,0,0.9));
    /*cirklar.push_back(Circle(BLUE,50,screenWidth/2+200,screenHeight/2+200,100,-100));
    cirklar.push_back(Circle(PURPLE,50,screenWidth/2+200,screenHeight/2-200,-100,-100));
    cirklar.push_back(Circle(PINK,50,screenWidth/2-200,screenHeight/2+200,100,100));
    cirklar.push_back(Circle(DARKPURPLE,50,screenWidth/2-200,screenHeight/2-200,-100,100));
    */
    while(!WindowShouldClose()){
        float DeltaTime = GetFrameTime();

        for(int i = cirklar.size(); i>0;i--){
            for(int j = 0; j<i;j++){
                if(Collision(cirklar[i],cirklar[j])){
                    std::cout << "Collision" << std::endl;
                }
            }
        }

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