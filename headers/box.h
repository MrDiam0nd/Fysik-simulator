#pragma once

#include "CameraManager.h"
#include "objekt.h"
#include <vector>

class Boxscene{
    int screenWidth = 700;
    int screenHeight = 700;
    CameraManager mainCamera;
    std::vector<Circle> cirklar;
    float time = 0;

public:
    Boxscene();
    int fn();
};