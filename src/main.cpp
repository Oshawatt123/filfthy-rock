/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include <memory>


#include "raylib.h"

#include "Particle.h"
#include "Box.h"
#include "TaitoCar.h"

#include "FilthyEngine.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	Camera camera = { 0 };
	camera.position = { 10.0f, 15.0f, 30.0f };
	camera.target = { 10.0f, 5.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	DisableCursor();



	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Model carModel = LoadModel("RaceCar.glb");
	Model trackModel = LoadModel("Track.glb");


	std::unique_ptr<FilthyEngine> filthyEngine = std::make_unique<FilthyEngine>();

	// floow
	std::shared_ptr<Box> floor = std::make_shared<Box>(Vector3{ 0, -0.5, 0 }, 100, 1, 100);
	floor->isFloor = true;
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(floor));


	// test case 1
	std::shared_ptr<Particle> particle = std::make_shared<Particle>(Vector3{ 0, 5, 0 }, Vector3{0,0,0});


	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle));
	
	// test case 2
	std::shared_ptr<Particle> particle2 = std::make_shared<Particle>(Vector3{ 5, 5, 0 }, Vector3{ 0,0,0 });
	std::shared_ptr<Box> box2 = std::make_shared<Box>(Vector3{ 5, 1, 0 }, 2, 1, 2);

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle2));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box2));

	// test case 3
	std::shared_ptr<Particle> particle3 = std::make_shared<Particle>(Vector3{ 10, 0, 0 }, Vector3{ 0,10,0 });
	std::shared_ptr<Box> box3 = std::make_shared<Box>(Vector3{ 10, 5, 0 }, 2, 1, 2);

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle3));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box3));

	// test case 4
	std::shared_ptr<Particle> particle4 = std::make_shared<Particle>(Vector3{ 15, 0, 0 }, Vector3{ 10, 2, 0 });
	std::shared_ptr<Box> box4 = std::make_shared<Box>(Vector3{ 12, 2, 0 }, 1, 4, 2);
	std::shared_ptr<Box> box4_1 = std::make_shared<Box>(Vector3{ 18, 2, 0 }, 1, 4, 2);

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle4));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box4));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box4_1));

	// test case 5
	std::shared_ptr<Particle> particle5 = std::make_shared<Particle>(Vector3{ 15, 10, 0 }, Vector3{ 10, 2, 0 });
	std::shared_ptr<Box> box5 = std::make_shared<Box>(Vector3{ 12, 10, 0 }, 1, 4, 2);
	std::shared_ptr<Box> box5_1 = std::make_shared<Box>(Vector3{ 18, 10, 0 }, 1, 4, 2);
	std::shared_ptr<Box> box5_2 = std::make_shared<Box>(Vector3{ 15, 8, 0 }, 5, 1, 2);

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle5));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box5));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box5_1));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box5_2));




	SetTargetFPS(60);

	std::unique_ptr<TaitoCar> car = std::make_unique<TaitoCar>(carModel);



	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);
				
				//DrawCube({ -4.0f, 0.0f, 2.0f }, 1.0f, 1.0f, 1.0f, RED);

				filthyEngine->Update();

				DrawGrid(100, 1.0f);

				DrawLine3D({ 0,0,0 }, { 3, 0, 0 }, RED);
				DrawLine3D({ 0,0,0 }, { 0, 0, 3 }, GREEN);
				DrawLine3D({ 0,0,0 }, { 0, 3, 0 }, BLUE);

			EndMode3D();

			particle->DrawDebug();

			DrawFPS(10, 10);

		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}