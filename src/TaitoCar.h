#pragma once

#include "raylib.h"

class TaitoCar
{
private:

	// To go to base class
	Vector3 position = { 0,0,0 };
	Vector3 rotation = { 0,0,0 };

	Vector3 forward = { 0,0,0 };
	Vector3 right = { 0,0,0 };

	// Car specific
	Vector3 velocity = { 0,0,0 };
	Vector3 engineForce = { 0,0,0 };
	Vector3 brakingForce = { 0,0,0 };
	Vector3 carAcceleration = { 0,0,0 };

	float maxSteeringAngle = 35.0f;
	float steeringAngle = 0.0f;
	float steerForce = 70.0f;
	float steerNeutralForce = 50.0f;
	float steeringNeurtalBuffer = 5.0f;

	float carLength = 4.0f;

	float resistance = 0.3f;
	
	float mass = 1.0f;
	float moveSpeed = 8.0f;
	float brakePower = 3.0f;

	Model carModel;

public:

	TaitoCar();
	TaitoCar(Model _carModel);

	// To go to base class
	void Update();
	void Draw3D();
	void Draw();
};