#pragma once

#include "raylib.h"

#include "PhysicsObject.h"

class Particle : public PhysicsObject
{
protected:
    virtual void Integrate();

    float radius = 0.5f;

public:
    Particle();
    ~Particle();

    Particle(Vector3 pos);
    Particle(Vector3 pos, Vector3 vel);

    virtual void Update() override;
    virtual void Draw3D() override;
    virtual void Draw() override;
    virtual void DrawDebug() override;

    void CheckCollision(std::shared_ptr<PhysicsObject> other = nullptr) override;
    

};