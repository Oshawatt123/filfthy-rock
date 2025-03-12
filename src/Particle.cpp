#include "Particle.h"

#include <sstream>
#include <iomanip>
#include <iostream>

#include "raymath.h"

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

void Particle::CheckCollision()
{
    constexpr float ParticleRestituion = 0.6f;

    ImpactForces = { 0, 0, 0 };

    // Ground collision check
    if (Position.y <= radius)
    {
        Vector3 collisionNormal = { 0, 1, 0 };
        Vector3 relativeVelocity = Velocity; // ground is static; relative velocity is just particle velocity
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

            std::cout << ImpactForces.x << ";" << ImpactForces.y << ";" << ImpactForces.z << std::endl;

            Position.y = radius;
        }
    }

    // Box collision check
}

Particle::Particle()
{

}

Particle::~Particle()
{

}

void Particle::Update()
{
    CheckCollision();
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