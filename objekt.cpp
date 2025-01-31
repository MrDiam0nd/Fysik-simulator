#include "objekt.h"

#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

#include "matte.h"

void Obj::update(float dt)
{
    acc.x += force.x / mass;
    acc.y += force.y / mass;

    vel.x += acc.x * dt * 0.5;
    vel.y += acc.y * dt * 0.5;

    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    vel.x += acc.x * dt * 0.5;
    vel.y += acc.y * dt * 0.5;

    force.x = 0;
    force.y = 0;
    acc.x = 0;
    acc.y = 0;
}

Circle::Circle(Color colorn = RED, float radiusn = 50, float xn = 0, float yn = 0, float xVeln = 0, float yVeln = 0, float elasticityn = 1)
{
    color = colorn;
    radius = radiusn;
    pos.x = xn;
    pos.y = yn;
    vel.x = xVeln;
    vel.y = yVeln;
    mass = radius * radius * PI;
    elasticity = elasticityn;
    force.x = 0;
    force.y = 0;
    acc.x = 0;
    acc.y = 0;
}

void Circle::draw()
{
    DrawCircle(pos.x, pos.y, radius, color);
}

Triangle::Triangle(Color colorn, Vector2 a, Vector2 b, Vector2 c, float x, float y, float xV, float yV, float r, float rV, float elasti)
{
    color = colorn;
    rotation = r;
    rVel = rV;
    vertezis[0] = a;
    vertezis[1] = b;
    vertezis[2] = c;

    pos.x = x;
    pos.y = y;
    vel.x = xV;
    vel.y = yV;
    elasticity = elasti;
    force.x = 0;
    force.y = 0;
    acc.x = 0;
    acc.y = 0;

    mass = 1;
}

void Triangle::update(float dt)
{
    acc.x += force.x / mass;
    acc.y += force.y / mass;

    vel.x += acc.x * dt * 0.5;
    vel.y += acc.y * dt * 0.5;

    pos.x += vel.x * dt;
    pos.y += vel.y * dt;

    vel.x += acc.x * dt * 0.5;
    vel.y += acc.y * dt * 0.5;

    force.x = 0;
    force.y = 0;
    acc.x = 0;
    acc.y = 0;

    rotation += rVel * dt;
}

void Triangle::draw()
{
    Vector2 vert[3];

    Vector2 B0 = {cos(rotation), sin(rotation)};
    Vector2 B1 = {-sin(rotation), cos(rotation)};

    for (int i = 0; i < 3; i++)
    {
        vert[i] = translateVectorBack(vertezis[i], B0, B1);
        vert[i].x += pos.x;
        vert[i].y += pos.y;
    }

    DrawTriangle(vert[0], vert[1], vert[2], color);
}

int Gravity(Obj &obj0,Obj &obj1,float G){
    float dx = obj0.pos.x-obj1.pos.x;
    float dy = obj0.pos.y-obj1.pos.y;
    float distance = pow((dx),2)+pow((dy),2);
    float F = G * obj0.mass * obj1.mass / distance;
    //F=ma
    //vilket håll

    distance = sqrt(distance);

    if(distance == 0){
        std::cout << "oh ohh (Gravitationen delade på 0)" << std::endl;
        return 1;
    }

    dx = dx*F/distance;
    dy = dy*F/distance;

    obj1.force.x += dx;
    obj0.force.x -= dx;
    obj1.force.y += dy;
    obj0.force.y -= dy;

    return F;
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

        if(isnan(C0.vel.x) || isnan(C0.vel.y)){
            std::cout << "C0 vel: " << C0.vel.x << " " << C0.vel.y<< std::endl;
        }

        Vector2 C0NewVel = translateVector(C0.vel,base0,base1);
        Vector2 C1NewVel = translateVector(C1.vel,base0,base1);

        ////////////////////////
        // C0.mass * C0NewVel.x^^2
        /*
        C0NewVel.x *= C0.mass;
        C1NewVel.x *= C1.mass;
        C0NewVel.y *= C0.mass;
        C1NewVel.y *= C1.mass;

        float temp = C0NewVel.x;
        C0NewVel.x = C1NewVel.x;
        C1NewVel.x = temp;

        */
        
        //C0.mass
        
        //C1.mass

        //C0NewVel.x

        //C1NewVel.x

        Vector2 C0Result;
        Vector2 C1Result;

        float CRes = (C0.elasticity + C1.elasticity)/2;

        //Perfekt elastisk
        //C0Result.x = ((C0.mass-C1.mass)*C0NewVel.x + 2*C1.mass*C1NewVel.x)/(C0.mass + C1.mass);
        //C1Result.x = (2*C0.mass*C0NewVel.x + (C1.mass-C0.mass)*C1NewVel.x)/(C0.mass + C1.mass);
        
        //inelastisk collision
        C0Result.x = (CRes*C1.mass*(C1NewVel.x-C0NewVel.x) + C0.mass*C0NewVel.x + C1.mass*C1NewVel.x)/(C0.mass+C1.mass);
        C1Result.x = (CRes*C0.mass*(C0NewVel.x-C1NewVel.x) + C0.mass*C0NewVel.x + C1.mass*C1NewVel.x)/(C0.mass+C1.mass);

        C0Result.y = C0NewVel.y;
        C1Result.y = C1NewVel.y;

        if(isnan(C0NewVel.y)){
            std::cout << "C0NewVel: "<< C0NewVel.y<< std::endl;
        }

        // if(isnan(C0Result.x) || isnan(C0Result.y)){
        //     std::cout << "C0result: " << C0Result.x << " " << C0Result.y<< std::endl;
        // }
        // if(isnan(C1Result.x) || isnan(C1Result.y)){
        //     std::cout << "C1result: " << C0Result.x << " " << C0Result.y<< std::endl;
        // }

        Vector2 C0back = translateVectorBack(C0Result,base0,base1);
        Vector2 C1back = translateVectorBack(C1Result,base0,base1);

        float combinedElasticity = ((C0.elasticity/2 + 0.5) + (C1.elasticity/2 + 0.5))/2;
        combinedElasticity = 1;

        // if(isnan(C0back.x) || isnan(C0back.y)){
        //     std::cout << "C0back is nan" << std::endl;
        //     std::cout << "C0result: " << C0Result.x << " " << C0Result.y<< std::endl;

        // }
        
        C0.vel.x = C0back.x * combinedElasticity + C1back.x * (1-combinedElasticity);
        C0.vel.y = C0back.y * combinedElasticity + C1back.y * (1-combinedElasticity);
        C1.vel.x = C1back.x * combinedElasticity + C0back.x * (1-combinedElasticity);
        C1.vel.y = C1back.y * combinedElasticity + C0back.y * (1-combinedElasticity);

        return 1;
    }
    return 0;
}

