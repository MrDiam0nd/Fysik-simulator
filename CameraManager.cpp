#include "CameraManager.h"
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
CameraManager::CameraManager()
{
    camera.zoom = 1.0f;
}

Camera2D CameraManager::GetCamera()
{
    // move with right click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        // get mouse pos
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        // centers the camera
        camera.offset = GetMousePosition();

        //Curser moves with camera
        camera.target = mouseWorldPos;

        // Zoom increment
        float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
        if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
        camera.zoom = Clamp(camera.zoom*scaleFactor, maxZoomOut, maxZoomIn);
    }
    return camera;
}