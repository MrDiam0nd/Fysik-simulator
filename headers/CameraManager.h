#pragma once

#include "raylib.h"

class CameraManager
{
    public:
    CameraManager();
    Camera2D GetCamera();

    private:
    Camera2D camera = { 0 };

    //>1 is zoom in  <1 is zoom out
    float maxZoomOut = 0.125f;
    float maxZoomIn = 64.0f;
};