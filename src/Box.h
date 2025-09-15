#pragma once

#include "PhysicsObject.h"
class Box :
    public PhysicsObject
{
protected:
    virtual void Integrate();

    float Width = 1.0f;
    float Height = 1.0f;
    float Depth = 1.0f;

    Vector3 initialPosition;

    virtual void OnCollision(PhysicsObject* other) override {};

public:
    Box();
    ~Box();

    Box(Vector3 pos);
    Box(Vector3 pos, float w, float h, float d);

    virtual void Update() override;
    virtual void Draw3D() override;
    virtual void Draw() override;
    virtual void DrawDebug() override;

    void CheckCollision(std::shared_ptr<PhysicsObject> other = nullptr) override;


    float GetMinX() { return Position.x - Width / 2; }
    float GetMaxX() { return Position.x + Width / 2; }
    float GetMinY() { return Position.y - Height / 2; }
    float GetMaxY() { return Position.y + Height / 2; }
    float GetMinZ() { return Position.z - Depth / 2; }
    float GetMaxZ() { return Position.z + Depth / 2; }

    void Offset(Vector3 offsetValue);

    bool isFloor = false;
    void SetTransparency(float newTrans) { color.a = newTrans; }

};