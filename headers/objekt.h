#pragma once

#include "raylib.h"


class Obj{
    public:
        Vector2 pos;
        Vector2 vel;
        Vector2 acc;
        Vector2 force;
        float mass;
        float elasticity;

        void update(float dt);
};

class Circle: public Obj{
    public:
        Circle(Color colorn,float radiusn, float xn, float yn,float xVeln,float yVeln, float elasticityn);

        Color color;
        float radius;

        void draw();
        
};

class Triangle: public Obj{
    public:
        Triangle(Color colorn,Vector2 a,Vector2 b, Vector2 c,float x, float y, float xV, float yV, float r, float rV, float elasti);

        Color color;
        float rotation;
        float rVel;
        Vector2 vertezis[3];

        void update(float dt);

        void draw();
};

int Gravity(Obj &obj0,Obj &obj1,float G);

int Collision(Circle &C0, Circle &C1);

int CollisionNew(Circle &C0, Circle &C1);
