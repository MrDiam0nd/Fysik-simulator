#pragma once

#include "CameraManager.h"
#include "objekt.h"
#include <vector>

class Spacescene{

    CameraManager mainCamera;
    std::vector<Circle> cirklar;
    float time = 0;
    const float G = 100;

public:
    Spacescene();
    int fn();
};