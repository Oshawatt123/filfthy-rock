#include "Particle.h"

#include <sstream>
#include <iomanip>
#include <iostream>
#include <memory>

#include "raymath.h"
#include "math.h"
#include "Box.h"
#include "FilthyUtil.h"

void Particle::Integrate()
{
    constexpr float gravityAccel = -9.8f;
    const float deltaTime = FilthyUtil::GetFrameTime();

    Acceleration = { 0,0,0 };

    if (drawDebug)
        std::cout << "Applying impact forces of {" << ImpactForces.x << ","
        << ImpactForces.y << "," << ImpactForces.z << "}" << std::endl;

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
    if (shouldRelocatePostPhysics)
    {
        postPhysicsLocation.x += Velocity.x * deltaTime;
        postPhysicsLocation.y += Velocity.y * deltaTime;
        postPhysicsLocation.z += Velocity.z * deltaTime;
    }
    else
    {
        Position.x += Velocity.x * deltaTime;
        Position.y += Velocity.y * deltaTime;
        Position.z += Velocity.z * deltaTime;
    }

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
    //        collisionForce.x *= collisionImpulse / FilthyUtil::GetFrameTime();
    //        collisionForce.y *= collisionImpulse / FilthyUtil::GetFrameTime();
    //        collisionForce.z *= collisionImpulse / FilthyUtil::GetFrameTime();

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
    if (std::shared_ptr<Box> box = std::dynamic_pointer_cast<Box>(other))
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
            Vector3 collisionNormal = Position - Vector3{ x, y, z };
            collisionNormal = Vector3Normalize(collisionNormal);

            Vector3 relativeVelocity = Velocity - other->GetVelocity();

            float collisionNormalDot = Vector3DotProduct(relativeVelocity, collisionNormal);

            if (drawDebug)
            {
                if (!box->isFloor)
                    DrawSphereWires(Vector3{ x, y, z }, 1, 3, 4, BLUE);

                DrawLine3D(Vector3{ x, y, z }, Position + (collisionNormal * 2), RED);
                DrawSphereWires(Vector3{ x, y, z }, 0.2, 2, 2, RED);
                DrawSphereWires(Position, 0.2, 2, 2, BLUE);
                DrawLine3D(other->GetVelocity(), Velocity, BLUE);
            }


            // if moving towards collision plane
            if (collisionNormalDot < 0)
            {
                if (other->IsSolid())
                {
                    float collisionImpulse = -(collisionNormalDot) * (ParticleRestituion + 1) * Mass;

                    Vector3 collisionForce = collisionNormal;
                    collisionForce.x *= collisionImpulse / FilthyUtil::GetFrameTime();
                    collisionForce.y *= collisionImpulse / FilthyUtil::GetFrameTime();
                    collisionForce.z *= collisionImpulse / FilthyUtil::GetFrameTime();

                    ImpactForces = Vector3Add(ImpactForces, collisionForce);

                    if(drawDebug)
                        std::cout << "Impact force from AABB collision: " << ImpactForces.x << ";" << ImpactForces.y << ";" << ImpactForces.z << std::endl;

                    // reposition out of box
                
                    // start at collision point
                    Vector3 newParticlePos = { x, y, z };
                    // move away on collision normal by radius
                    Vector3 a = collisionNormal * radius;

                    newParticlePos = Vector3Add(newParticlePos, a);
                    // if we already have a new relocation, take the average of them
                    if (shouldRelocatePostPhysics)
                    {
                        postPhysicsLocation = (postPhysicsLocation + newParticlePos) / 2;
                    }
                    else
                    {
                        postPhysicsLocation = newParticlePos;
                    }
                    shouldRelocatePostPhysics = true;

                    if(drawDebug)
                        DrawSphereWires(newParticlePos, 0.2, 3, 3, GREEN);
                }
            }
        }
    }

    // Sphere-AABB overlap check
    if (std::shared_ptr<Box> box = std::dynamic_pointer_cast<Box>(other))
    {
        if (box->GetMinX() - radius < Position.x && box->GetMaxX() + radius > Position.x &&
            box->GetMinY() - radius < Position.y && box->GetMaxY() + radius > Position.y &&
            box->GetMinZ() - radius < Position.z && box->GetMaxZ() + radius > Position.z)
        {
            other->OnCollision(this);
        }
    }

    // Sphere-Sphere collision
    if (std::shared_ptr<Particle> particle = std::dynamic_pointer_cast<Particle>(other))
    {
        if (std::abs(particle->GetPosition().x - Position.x) < particle->radius + radius &&
            std::abs(particle->GetPosition().y - Position.y) < particle->radius + radius &&
            std::abs(particle->GetPosition().z - Position.z) < particle->radius + radius)
        {
            Vector3 collisionNormal = Position - other->GetPosition();
            collisionNormal = Vector3Normalize(collisionNormal);

            Vector3 relativeVelocity = Velocity - other->GetVelocity();
            //relativeVelocity = Vector3Normalize(relativeVelocity);

            float collisionNormalDot = Vector3DotProduct(relativeVelocity, collisionNormal);


            /*std::cout << "attempting particle collision with relative velocity {" << relativeVelocity.x << ","
                << relativeVelocity.y << "," << relativeVelocity.z << "}" << std::endl;

            std::cout << "attempting particle collision with normal {" << collisionNormal.x << ","
                << collisionNormal.y << "," << collisionNormal.z << "}" << std::endl;

            std::cout << "attempting particle collision with normal dot {" << collisionNormalDot << "}" << std::endl;*/

            // if moving towards collision plane
            if (collisionNormalDot < 0)
            {
                if (other->IsSolid())
                {
                    float collisionImpulse = -(collisionNormalDot) * (ParticleRestituion + 1) * Mass;

                    float massPercent = Mass / (Mass + particle->Mass);
                    float inverseMassPercent = 1 / massPercent;

                    Vector3 collisionForce = collisionNormal / inverseMassPercent;
                    collisionForce.x *= collisionImpulse / FilthyUtil::GetFrameTime();
                    collisionForce.y *= collisionImpulse / FilthyUtil::GetFrameTime();
                    collisionForce.z *= collisionImpulse / FilthyUtil::GetFrameTime();

                    ImpactForces = Vector3Add(ImpactForces, collisionForce);

                    /*std::cout << "particle collision: {" << collisionForce.x << ","
                        << collisionForce.y << "," << collisionForce.z <<  "}" << std::endl;*/

                    //std::cout << "Impact force from AABB collision: " << ImpactForces.x << ";" << ImpactForces.y << ";" << ImpactForces.z << std::endl;

                    // reposition out of box

                    // start at collision point
                    Vector3 newParticlePos = (particle->GetPosition() + Position)/2;
                    // move away on collision normal by radius
                    Vector3 a = collisionNormal * radius;

                    newParticlePos = Vector3Add(newParticlePos, a);
                    if (shouldRelocatePostPhysics)
                    {
                        postPhysicsLocation = (postPhysicsLocation + newParticlePos) / 2;
                    }
                    else
                    {
                        postPhysicsLocation = newParticlePos;
                    }
                    shouldRelocatePostPhysics = true;

                    if (drawDebug)
                        DrawSphereWires(newParticlePos, 0.2, 3, 3, GREEN);
                }
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
    if (drawDebug)
    {
        DrawSphere(Position, radius, RED);
    }
    else
    {
        DrawSphere(Position, radius, color);
    }
}

void Particle::Draw()
{

}

void Particle::PostPhysics()
{
    if (shouldRelocatePostPhysics)
    {
        Position = postPhysicsLocation;
    }
}
