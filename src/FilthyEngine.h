#pragma once

#include <vector>
#include <memory>

#include "PhysicsObject.h"

class FilthyEngine
{
private:
	std::vector<std::shared_ptr<PhysicsObject>> objects;
	int selectedDebugObject = 0;

	float physicsTime = 0.0f;

public:
	void Update();
	void Draw();

	void AddObjectToSimulation(std::shared_ptr<PhysicsObject> object);

	void DrawDebugForObject();

	float GetPhysicsTime() { return physicsTime; }
};