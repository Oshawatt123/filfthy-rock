#pragma once
#include "raylib.h"
#include "raymath.h"
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
    bool drawDebug = false;
    bool isSolid = true;

    bool shouldRelocatePostPhysics = false;
    Vector3 postPhysicsLocation;

    Color color = GREEN;

public:
    PhysicsObject() {};
    ~PhysicsObject() {};

    virtual void Update() = 0;
    virtual void Draw3D() = 0;
    virtual void Draw() = 0;
    virtual void DrawDebug() = 0;
    virtual void CheckCollision(std::shared_ptr<PhysicsObject> other = nullptr) = 0;
    
    virtual void OnCollision(PhysicsObject* other) = 0;

    Vector3 GetPosition() { return Position; }
    Vector3 GetVelocity() { return Velocity; }
    void Translate(Vector3 dP) { Position += dP; Velocity = dP; }

    virtual void PrePhysics();
    virtual void PostPhysics() {};

    void SetDebugDraw(bool draw) { drawDebug = draw; }

    void ApplyAcceleration(Vector3 accel) { ImpactForces = Vector3Add(ImpactForces, accel); }

    bool IsSolid() { return isSolid; }
};