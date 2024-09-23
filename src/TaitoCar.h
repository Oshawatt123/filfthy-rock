#pragma once

#include "raylib.h"

class TaitoCar
{
private:

	// To go to base class
	Vector3 position = { 0,0,0 };
	Vector3 rotation = { 0,0,0 };

	// Car specific
	Vector3 velocity = { 0,0,0 };
	Vector3 carForce = { 0,0,0 };
	Vector3 carAcceleration = { 0,0,0 };

	float resistance = 3.0f;
	
	float mass = 1.0f;
	float moveSpeed = 1.0f;

	Model carModel;

public:

	TaitoCar();

	// To go to base class
	void Update();
	void Draw3D();
	void Draw();
};