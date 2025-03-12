#pragma once

#include "raylib.h"

class Particle
{
private:
    Vector3 Position = { 0, 10.0f, 0 };
    
    Vector3 Velocity = {0, 0, 0};
    Vector3 Acceleration = { 0, 0, 0 };
    Vector3 ImpactForces = { 0, 0, 0 };

    float Mass = 1.0f;
    float radius = 0.5f;

    void Integrate();
    void CheckCollision();

public:
    Particle();
    ~Particle();

    void Update();
    void Draw3D();
    void Draw();
    void DrawDebug();

};