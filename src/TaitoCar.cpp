#include "TaitoCar.h"
#include <string>
#include <iomanip>
#include <sstream>

#include "raymath.h"

TaitoCar::TaitoCar()
{
	Mesh carMesh = GenMeshCube(1.0f, 1.0f, 2.0f);
	carModel = LoadModelFromMesh(carMesh);
}

void TaitoCar::Update()
{
	carForce = { 0,0,0 };
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
		carForce.z -= (moveSpeed);
	}
	if (IsKeyDown(KEY_DOWN))
	{
		carForce.z += (moveSpeed);
	}

	carForce = Vector3RotateByAxisAngle(carForce, { 0,1,0 }, rotation.y * DEG2RAD);

	carAcceleration.x = carForce.x / mass;
	carAcceleration.z = carForce.z / mass;

	velocity.x += carAcceleration.x * GetFrameTime();
	velocity.z += carAcceleration.z * GetFrameTime();

	position.x += velocity.x * GetFrameTime();
	position.z += velocity.z * GetFrameTime();
}

void TaitoCar::Draw3D()
{
	//carModel.transform = MatrixMultiply(MatrixRotateY(rotation.y * DEG2RAD), carModel.transform);

	//DrawCube(position, 1.0f, 1.0f, 2.0f, BLUE);
	Vector3 lineEnd;
	lineEnd.x = position.x + carForce.x;
	lineEnd.y = position.y + carForce.y;
	lineEnd.z = position.z + carForce.z;
	DrawLine3D(position, lineEnd, RED);

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