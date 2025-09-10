#pragma once
#include "raylib.h"
#include <memory>

class PhysicsObject
{
protected:
    Vector3 Position = { 0, 20.0f, 0 };

    Vector3 Velocity = { 0, 0, 0 };
    Vector3 Acceleration = { 0, 0, 0 };
    Vector3 ImpactForces = { 0, 0, 0 };

    float Mass = 1.0f;

    void Integrate();

public:
    PhysicsObject() {};
    ~PhysicsObject() {};

    virtual void Update() = 0;
    virtual void Draw3D() = 0;
    virtual void Draw() = 0;
    virtual void DrawDebug() = 0;
    virtual void CheckCollision(std::shared_ptr<PhysicsObject> other = nullptr) = 0;

    Vector3 GetPosition() { return Position; }
    Vector3 GetVelocity() { return Velocity; }

    void PrePhysics();
};