#include "FilthyEngine.h"

void FilthyEngine::Update()
{
	for (std::shared_ptr<PhysicsObject> object : objects)
	{
		object->PrePhysics();
	}


	for (std::shared_ptr<PhysicsObject> object : objects)
	{
		for (std::shared_ptr<PhysicsObject> other : objects)
		{
			if (other != object)
			{
				object->CheckCollision(other);
			}
		}

		object->Update();
		object->Draw3D();
	}
}

void FilthyEngine::AddObjectToSimulation(std::shared_ptr<PhysicsObject> object)
{
	objects.push_back(object);
}