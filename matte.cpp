#include "matte.h"

#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

void print_vector(Vector2 V,char* name = "vector"){
    std::cout << name << ":  " << V.x << "  " << V.y << std::endl;
}

void check_vector(Vector2 V,char* name = "vector"){
    if(isnan(V.x) || isnan(V.y)){
        std::cout << "error ";
        print_vector(V);
    }
}

Vector2 translateVector(Vector2 V,Vector2 BX, Vector2 BY){
    Vector2 R;

    R.x = (V.y * BY.x - BY.y * V.x) / (BY.x * BX.y - BY.y * BX.x);
    R.y = (V.y * BX.x - BX.y * V.x) / (BY.y * BX.x - BY.x * BX.y);

    check_vector(R);

    return R;
}

Vector2 translateVectorBack(Vector2 V,Vector2 BX, Vector2 BY){
    Vector2 R;

    R.x = BX.x * V.x + BY.x * V.y;
    R.y = BX.y * V.x + BY.y * V.y;

    return R;
}
