#include "TaitoCar.h"
#include <string>
#include <iomanip>
#include <sstream>

#include "raymath.h"

TaitoCar::TaitoCar()
{
	Mesh carMesh = GenMeshCube(2.0f, 1.0f, 1.0f);
	carModel = LoadModelFromMesh(carMesh);
}

void TaitoCar::Update()
{
	engineForce = { 0,0,0 };
	brakingForce = { 0,0,0 };

	carAcceleration = { 0,0,0 };
	if (IsKeyDown(KEY_LEFT))
	{
		rotation.y += (moveSpeed);
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		rotation.y -= (moveSpeed);
	}
	if (IsKeyDown(KEY_UP))
	{
		engineForce.x += (moveSpeed);
	}
	if (IsKeyDown(KEY_DOWN))
	{
		// negative because braking force acts opposite to velocity
		brakingForce = Vector3Multiply(Vector3Normalize(velocity), { -brakePower, -brakePower, -brakePower });
	}


	forward = Vector3RotateByAxisAngle({ 1,0,0 }, { 0,1,0 }, rotation.y * DEG2RAD);
	right = Vector3RotateByAxisAngle({ 0,0,1 }, { 0,1,0 }, rotation.y * DEG2RAD);

	// convert car forces to face forward
	engineForce = Vector3RotateByAxisAngle(engineForce, { 0,1,0 }, rotation.y * DEG2RAD);
	brakingForce = Vector3RotateByAxisAngle(brakingForce, { 0,1,0 }, rotation.y * DEG2RAD);

	Vector3 rollingResistance = { 0,0,0 };
	rollingResistance.x = velocity.x * -resistance;
	rollingResistance.y = velocity.y * -resistance;
	rollingResistance.z = velocity.z * -resistance;

	// multiply our rolling resistance when we are parallel to our velocity
	// to mimick car sliding and slowing down faster as a result
	float resistanceMultiplier = abs(Vector3DotProduct(Vector3Normalize(velocity), right)) + 1;

	rollingResistance.x = rollingResistance.x * resistanceMultiplier;
	rollingResistance.y = rollingResistance.y * resistanceMultiplier;
	rollingResistance.z = rollingResistance.z * resistanceMultiplier;

	engineForce.x = engineForce.x + rollingResistance.x;
	engineForce.y = engineForce.y + rollingResistance.y;
	engineForce.z = engineForce.z + rollingResistance.z;

	engineForce.x = engineForce.x + brakingForce.x;
	engineForce.y = engineForce.y + brakingForce.y;
	engineForce.z = engineForce.z + brakingForce.z;

	carAcceleration.x = engineForce.x / mass;
	carAcceleration.z = engineForce.z / mass;

	velocity.x += carAcceleration.x * GetFrameTime();
	velocity.z += carAcceleration.z * GetFrameTime();

	position.x += velocity.x * GetFrameTime();
	position.z += velocity.z * GetFrameTime();
}

void TaitoCar::Draw3D()
{
	Vector3 lineEnd;
	lineEnd.x = position.x + engineForce.x;
	lineEnd.y = position.y + engineForce.y;
	lineEnd.z = position.z + engineForce.z;
	DrawLine3D(position, lineEnd, YELLOW);

	lineEnd.x = position.x + (forward.x * 5.0f);
	lineEnd.y = position.y + (forward.y * 5.0f);
	lineEnd.z = position.z + (forward.z * 5.0f);
	DrawLine3D(position, lineEnd, RED);

	lineEnd.x = position.x + (velocity.x * 5.0f);
	lineEnd.y = position.y + (velocity.y * 5.0f);
	lineEnd.z = position.z + (velocity.z * 5.0f);
	DrawLine3D(position, lineEnd, GREEN);

	DrawModelEx(carModel, position, { 0,1,0 }, rotation.y, { 1,1,1 }, BLUE);
}

void TaitoCar::Draw()
{
	std::stringstream stream;
	stream << "Position: " << std::fixed << std::setprecision(2) << position.x << ";" << position.y << ";" << position.z;
	std::string textString = stream.str();
	DrawText(textString.c_str(), 10, 30, 30, GREEN);

	stream.str("");
	stream << "Rotation: " << std::fixed << std::setprecision(2) << rotation.x << ";" << rotation.y << ";" << rotation.z;
	textString = stream.str();
	DrawText(textString.c_str(), 10, 80, 30, GREEN);
}