#pragma once

#include "CameraManager.h"
#include "objekt.h"
#include <vector>

class Simplescene{

    CameraManager mainCamera;
    std::vector<Circle> cirklar;
    float time = 0;
    const float G = 200;

public:
    Simplescene();
    int fn();
};