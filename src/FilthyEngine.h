#pragma once

#include <vector>
#include <memory>

#include "PhysicsObject.h"

class FilthyEngine
{
private:
	std::vector<std::shared_ptr<PhysicsObject>> objects;

public:
	void Update();

	void AddObjectToSimulation(std::shared_ptr<PhysicsObject> object);
};