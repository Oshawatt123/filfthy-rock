#include "PhysicsObject.h"

#include <sstream>
#include <iomanip>

void PhysicsObject::PrePhysics()
{
	ImpactForces = { 0,0,0 };
	shouldRelocatePostPhysics = false;
}

void PhysicsObject::DrawDebug()
{
    std::stringstream stream;

    char isNeg = Position.x > 0.0f ? ' ' : '-';
    stream << "Position: " << std::fixed << std::setprecision(2) << isNeg << abs(Position.x) << ";";
    std::string textString = stream.str();
    DrawText(textString.c_str(), 10, 30, 30, GREEN);

    stream.str("");
    isNeg = Position.y> 0.0f ? ' ' : '-';
    stream << std::fixed << std::setprecision(2) << isNeg << abs(Position.y) << ";";
    textString = stream.str();
    DrawText(textString.c_str(), 240, 30, 30, GREEN);

    stream.str("");
    isNeg = Position.z > 0.0f ? ' ' : '-';
    stream << std::fixed << std::setprecision(2) << isNeg << abs(Position.z) << ";";
    textString = stream.str();
    DrawText(textString.c_str(), 320, 30, 30, GREEN);



    stream.str("");
    isNeg = Velocity.x > 0.0f ? ' ' : '-';
    stream << "Velocity: " << std::fixed << std::setprecision(2) << isNeg << abs(Velocity.x) << ";";
    textString = stream.str();
    DrawText(textString.c_str(), 10, 80, 30, GREEN);

    stream.str("");
    isNeg = Velocity.y > 0.0f ? ' ' : '-';
    stream << std::fixed << std::setprecision(2) << isNeg << abs(Velocity.y) << ";";
    textString = stream.str();
    DrawText(textString.c_str(), 240, 80, 30, GREEN);

    stream.str("");
    isNeg = Velocity.z > 0.0f ? ' ' : '-';
    stream << std::fixed << std::setprecision(2) << isNeg << abs(Velocity.z) << ";";
    textString = stream.str();
    DrawText(textString.c_str(), 320, 80, 30, GREEN);


    
    stream.str("");
    isNeg = Acceleration.x > 0.0f ? ' ' : '-';
    stream << "Acceleration: " << std::fixed << std::setprecision(2) << isNeg << abs(Acceleration.x) << ";";
    textString = stream.str();
    DrawText(textString.c_str(), 10, 130, 30, GREEN);

    stream.str("");
    isNeg = Acceleration.y > 0.0f ? ' ' : '-';
    stream << std::fixed << std::setprecision(2) << isNeg << abs(Acceleration.y) << ";";
    textString = stream.str();
    DrawText(textString.c_str(), 320, 130, 30, GREEN);

    stream.str("");
    isNeg = Acceleration.z > 0.0f ? ' ' : '-';
    stream << std::fixed << std::setprecision(2) << isNeg << abs(Acceleration.z) << ";";
    textString = stream.str();
    DrawText(textString.c_str(), 400, 130, 30, GREEN);


    //DrawCylinderWiresEx(Position, Position + (Acceleration * 5), 0.2, 0, 3, PURPLE);
}