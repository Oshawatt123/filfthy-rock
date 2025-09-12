#include "FilthyEngine.h"
#include "raymath.h"

#include "FilthyUtil.h"

#include <iostream>

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
	}

	for (std::shared_ptr<PhysicsObject> object : objects)
	{
		object->Update();
	}

	for (std::shared_ptr<PhysicsObject> object : objects)
	{
		object->PostPhysics();
	}


	physicsTime += FilthyUtil::GetFrameTime();
}

void FilthyEngine::Draw()
{
	for (std::shared_ptr<PhysicsObject> object : objects)
	{
		object->Draw3D();
	}
}

void FilthyEngine::AddObjectToSimulation(std::shared_ptr<PhysicsObject> object)
{
	objects.push_back(object);

	selectedDebugObject = objects.size() - 1;
}

void FilthyEngine::DrawDebugForObject()
{
	if (IsKeyPressed(KEY_P))
	{
		selectedDebugObject++;
		std::cout << "Selecting debug object: " << selectedDebugObject << std::endl;
	}
	if (IsKeyPressed(KEY_O))
	{
		selectedDebugObject--;
		std::cout << "Selecting debug object: " << selectedDebugObject << std::endl;
	}

	if (selectedDebugObject < 0)
	{
		selectedDebugObject = objects.size() - 1;
	}
	else if (selectedDebugObject >= objects.size())
	{
		selectedDebugObject = 0;
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->SetDebugDraw(i == selectedDebugObject);
		if (i == selectedDebugObject)
		{
			objects[i]->DrawDebug();
		}
	}
}
