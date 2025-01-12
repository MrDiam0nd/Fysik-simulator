#include "matte.h"

#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

Vector2 translateVector(Vector2 V,Vector2 B0, Vector2 B1){
    Vector2 R;

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
