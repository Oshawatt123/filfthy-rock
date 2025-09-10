#include "Particle.h"

#include <sstream>
#include <iomanip>
#include <iostream>
#include <memory>

#include "raymath.h"
#include "math.h"
#include <Box.h>

void Particle::Integrate()
{
    constexpr float gravityAccel = -9.8f;
    const float deltaTime = GetFrameTime();

    Vector3 Acceleration = { 0,0,0 };

    Acceleration.x += ImpactForces.x / Mass;
    Acceleration.y += ImpactForces.y / Mass;
    Acceleration.z += ImpactForces.z / Mass;

    // Apply Gravity
    Acceleration.y += gravityAccel;

    // Integrate Velocity
    Velocity.x += Acceleration.x * deltaTime;
    Velocity.y += Acceleration.y * deltaTime;
    Velocity.z += Acceleration.z * deltaTime;

    // Integrate Position
    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
    Position.z += Velocity.z * deltaTime;

}

void Particle::CheckCollision(std::shared_ptr<PhysicsObject> other)
{
    constexpr float ParticleRestituion = 0.6f;

    // Sphere-Ground collision check
    //if (Position.y <= radius)
    //{
    //    Vector3 collisionNormal = { 0, 1, 0 };
    //    Vector3 relativeVelocity = Velocity; // ground is static; relative velocity is just particle velocity
    //    float collisionNormalDot = Vector3DotProduct(relativeVelocity, collisionNormal);

    //    // if moving towards collision plane
    //    if (collisionNormalDot < 0)
    //    {
    //        float collisionImpulse = -(collisionNormalDot) * (ParticleRestituion + 1) * Mass;

    //        Vector3 collisionForce = collisionNormal;
    //        collisionForce.x *= collisionImpulse / GetFrameTime();
    //        collisionForce.y *= collisionImpulse / GetFrameTime();
    //        collisionForce.z *= collisionImpulse / GetFrameTime();

    //        ImpactForces = Vector3Add(ImpactForces, collisionForce);

    //        std::cout << ImpactForces.x << ";" << ImpactForces.y << ";" << ImpactForces.z << std::endl;

    //        Position.y = radius;
    //    }
    //}

    if (other == nullptr)
    {
        return;
    }

    // Sphere-AABB collision check
    if (std::shared_ptr<Box> box = std::static_pointer_cast<Box>(other))
    {
        // get box closest point to sphere
        const float x = fmaxf(box->GetMinX(), fminf(Position.x, box->GetMaxX()));
        const float y = fmaxf(box->GetMinY(), fminf(Position.y, box->GetMaxY()));
        const float z = fmaxf(box->GetMinZ(), fminf(Position.z, box->GetMaxZ()));

        // Point in sphere check
        const float distanceSquared = (x - Position.x) * (x - Position.x) +
            (y - Position.y) * (y - Position.y) +
            (z - Position.z) * (z - Position.z);

        if (distanceSquared < radius * radius)
        {
            if (!box->isFloor)
                DrawSphereWires(Vector3{ x, y, z }, 1, 3, 4, BLUE);

            Vector3 collisionNormal = Position - Vector3{ x, y, z };
            collisionNormal = Vector3Normalize(collisionNormal);
            DrawLine3D(Vector3{x, y, z}, Position + (collisionNormal * 2), RED);
            DrawSphereWires(Vector3{ x, y, z }, 0.2, 2, 2, RED);
            DrawSphereWires(Position, 0.2, 2, 2, BLUE);

            Vector3 relativeVelocity = Velocity - other->GetVelocity();
            DrawLine3D(other->GetVelocity(), Velocity, BLUE);

            float collisionNormalDot = Vector3DotProduct(relativeVelocity, collisionNormal);

            // if moving towards collision plane
            if (collisionNormalDot < 0)
            {
                float collisionImpulse = -(collisionNormalDot) * (ParticleRestituion + 1) * Mass;

                Vector3 collisionForce = collisionNormal;
                collisionForce.x *= collisionImpulse / GetFrameTime();
                collisionForce.y *= collisionImpulse / GetFrameTime();
                collisionForce.z *= collisionImpulse / GetFrameTime();

                ImpactForces = Vector3Add(ImpactForces, collisionForce);

                std::cout << "Impact force from AABB collision: " << ImpactForces.x << ";" << ImpactForces.y << ";" << ImpactForces.z << std::endl;

                // reposition out of box
                
                // start at collision point
                Vector3 newParticlePos = { x, y, z };
                // move away on collision normal by radius
                Vector3 a = collisionNormal * radius;

                newParticlePos = Vector3Add(newParticlePos, a);
                Position = newParticlePos;

                DrawSphereWires(newParticlePos, 0.2, 3, 3, GREEN);
            }
        }
    }
}

Particle::Particle()
{
    Velocity = { 1, 3, 0 };
}

Particle::~Particle()
{

}

Particle::Particle(Vector3 pos)
{
    Position = pos;
}

Particle::Particle(Vector3 pos, Vector3 vel)
{
    Position = pos;
    Velocity = vel;
}

void Particle::Update()
{
    Integrate();
}

void Particle::Draw3D()
{
    DrawSphere(Position, radius, RED);
}

void Particle::Draw()
{

}

void Particle::DrawDebug()
{
    std::stringstream stream;
    stream << "Position: " << std::fixed << std::setprecision(2) << Position.x << ";" << Position.y << ";" << Position.z;
    std::string textString = stream.str();
    DrawText(textString.c_str(), 10, 30, 30, GREEN);

    stream.str("");
    stream << "Velocity: " << std::fixed << std::setprecision(2) << Velocity.x << ";" << Velocity.y << ";" << Velocity.z;
    textString = stream.str();
    DrawText(textString.c_str(), 10, 80, 30, GREEN);

    stream.str("");
    stream << "Acceleration: " << std::fixed << std::setprecision(2) << Acceleration.x << ";" << Acceleration.y << ";" << Acceleration.z;
    textString = stream.str();
    DrawText(textString.c_str(), 10, 130, 30, GREEN);
}