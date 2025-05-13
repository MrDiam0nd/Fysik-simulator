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

        // Flytta isär dem
        C1.pos.x += base0.x * distbetween/2;
        C1.pos.y += base0.y * distbetween/2;
        C0.pos.x -= base0.x * distbetween/2;
        C0.pos.y -= base0.y * distbetween/2;

        // Nytt kordinatsystem
        Vector2 V0 = translateVector(C0.vel,base0,base1);
        Vector2 U0 = translateVector(C1.vel,base0,base1);

        Vector2 V = V0;
        Vector2 U = U0;

        float m = C0.mass;
        float M = C1.mass;

        float e = (C0.elasticity + C1.elasticity)/2;

        // Fysik
        V.x=(e*M*(U0.x-V0.x)+M*U0.x+m*V0.x)/(M+m);
        U.x=(e*m*(V0.x-U0.x)+M*U0.x+m*V0.x)/(M+m);

        // Tillbaka till gamla kordinatsystemet
        Vector2 C0back = translateVectorBack(V,base0,base1);
        Vector2 C1back = translateVectorBack(U,base0,base1);

        C0.vel = C0back;
        C1.vel = C1back;

        return 1;
    }
    return 0;
}