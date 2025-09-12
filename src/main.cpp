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
#include <cmath>
#include <array>


#include "raylib.h"

#include "Particle.h"
#include "Box.h"
#include "TaitoCar.h"
#include "ForceField.h"

#include "FilthyEngine.h"
#include "FilthyUtil.h"

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

	// test case 6
	std::shared_ptr<Particle> particle6 = std::make_shared<Particle>(Vector3{ 20, 5, 0 }, Vector3{ 0,0,0 });
	std::shared_ptr<Box> box6 = std::make_shared<Box>(Vector3{ 20, 1, 0 }, 2, 1, 2);

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle6));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box6));

	// test case 6b
	std::shared_ptr<Particle> particle6b = std::make_shared<Particle>(Vector3{ 20, 5, -5 }, Vector3{ 0,0,0 });
	std::shared_ptr<Box> box6b = std::make_shared<Box>(Vector3{ 20, 1, -5 }, 2, 1, 2);

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle6b));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box6b));


	// test case 7
	std::shared_ptr<Particle> particle7 = std::make_shared<Particle>(Vector3{ 28, 5, 0 }, Vector3{ 0,0,0 });
	std::shared_ptr<Particle> particle7_1 = std::make_shared<Particle>(Vector3{ 38, 5, 0 }, Vector3{ 0,0,0 });
	std::shared_ptr<Box> box7 = std::make_shared<Box>(Vector3{ 25, 1, 0 }, 2, 10, 2);
	std::shared_ptr<Box> box7_1 = std::make_shared<Box>(Vector3{ 40, 1, 0 }, 2, 10, 2);
	std::shared_ptr<ForceField> field7 = std::make_shared<ForceField>(Vector3{ 26, 1, 0 }, Vector3{ 20, 0, 0 }, 5, 2, 2);
	std::shared_ptr<ForceField> field7_1 = std::make_shared<ForceField>(Vector3{ 38, 1, 0 }, Vector3{ -20, 0, 0 }, 5, 2, 2);

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle7));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle7_1));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box7));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box7_1));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field7));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field7_1));


	// fun
	std::shared_ptr<Particle> particle_fun = std::make_shared<Particle>(Vector3{ 0.6, 25, 10 }, Vector3{ 0, 0, 0 });
	std::shared_ptr<Particle> particle_fun2 = std::make_shared<Particle>(Vector3{ 3, 25, 10 }, Vector3{ 0, 0, 0 });
	std::shared_ptr<Particle> particle_fun3 = std::make_shared<Particle>(Vector3{ -2, 25, 10 }, Vector3{ 0, 0, 0 });
	std::shared_ptr<Particle> particle_fun4 = std::make_shared<Particle>(Vector3{ 5, 20, 10 }, Vector3{ 0, 0, 0 });
	std::shared_ptr<Particle> particle_fun5 = std::make_shared<Particle>(Vector3{ -3, 5, 10 }, Vector3{ 0, 0, 0 });
	std::shared_ptr<Particle> particle_fun6 = std::make_shared<Particle>(Vector3{ 2, 2, 10 }, Vector3{ 0, 0, 0 });

	std::array<Color, 5> colors = { PURPLE, BLUE, YELLOW, WHITE, BLACK };

	for (int i = 0; i < 30; i++)
	{
		float min = -5.0f;
		float max = 5.0f;
		float x = GetRandomValue(min, max);

		min = 15;
		max = 25;
		float y = GetRandomValue(min, max);
		std::shared_ptr<Particle> newParticle = std::make_shared<Particle>(Vector3{ x, y, 10 }, Vector3{ 0, 0, 0 });
		newParticle->SetColor(colors[GetRandomValue(0, 4)]);

		filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(newParticle));
	}

	// walls
	std::shared_ptr<Box> box_fun = std::make_shared<Box>(Vector3{ 0, 0, 10 }, 30, 1, 2);
	std::shared_ptr<Box> box_fun2 = std::make_shared<Box>(Vector3{ -15, 15, 10 }, 1, 30, 2);
	std::shared_ptr<Box> box_fun3 = std::make_shared<Box>(Vector3{ 15, 15, 10 }, 1, 30, 2);
	std::shared_ptr<Box> box_fun4 = std::make_shared<Box>(Vector3{ 0, 30, 10 }, 30, 1, 2);

	// backboard
	std::shared_ptr<Box> box_fun_back = std::make_shared<Box>(Vector3{ 0, 15, 7 }, 30, 30, 2);
	box_fun_back->SetColor(GRAY);

	// staircase
	std::shared_ptr<Box> box_fun5 = std::make_shared<Box>(Vector3{  -1,  20, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun6 = std::make_shared<Box>(Vector3{  0,  19, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun7 = std::make_shared<Box>(Vector3{  1,  18, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun8 = std::make_shared<Box>(Vector3{  2,  17, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun9 = std::make_shared<Box>(Vector3{  3,  16, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun10 = std::make_shared<Box>(Vector3{ 4, 15, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun11 = std::make_shared<Box>(Vector3{ 5, 14, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun12 = std::make_shared<Box>(Vector3{ 6, 13, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun13 = std::make_shared<Box>(Vector3{ 7, 12, 10 }, 1, 1, 2);

	// chute
	std::shared_ptr<Box> box_fun14 = std::make_shared<Box>(Vector3{ 12, 8, 10 }, 5, 1, 2);
	std::shared_ptr<Box> box_fun_chute = std::make_shared<Box>(Vector3{ -11, 14, 10 }, 1, 25, 2);
	std::shared_ptr<Box> box_fun_chute1 = std::make_shared<Box>(Vector3{ -14, 28, 10 }, 1, 1, 2);
	std::shared_ptr<Box> box_fun_chute2 = std::make_shared<Box>(Vector3{ -13, 29, 10 }, 1, 1, 2);
	std::shared_ptr<ForceField> field_fun_chute = std::make_shared<ForceField>(Vector3{ -13, 27, 10 }, Vector3{ 1000, 0, 0 }, 5, 2, 2);
	std::shared_ptr<ForceField> field_fun = std::make_shared<ForceField>(Vector3{ -13, 12, 10 }, Vector3{ 0, 1000, 0 }, 2, 27, 2);

	// chute2
	std::shared_ptr<Box> box_fun_chute_2 = std::make_shared<Box>(Vector3{ -9, 25, 10 }, 4, 1, 2);
	std::shared_ptr<Box> box_fun_chute_2_1 = std::make_shared<Box>(Vector3{ -2, 25, 10 }, 3, 1, 2);

	// splitter
	std::shared_ptr<Box> box_fun_splitter = std::make_shared<Box>(Vector3{ -5.5, 18, 10 }, 1, 7, 2);
	std::shared_ptr<Box> box_fun_splitter1 = std::make_shared<Box>(Vector3{ -8, 12, 10 }, 4, 1, 2);
	std::shared_ptr<Box> box_fun_splitter2 = std::make_shared<Box>(Vector3{ -3, 12, 10 }, 4, 1, 2);
	std::shared_ptr<ForceField> field_fun_splitter = std::make_shared<ForceField>(Vector3{-8, 13, 10}, Vector3{500, 0, 0}, 5, 1, 2);
	std::shared_ptr<ForceField> field_fun_splitter1 = std::make_shared<ForceField>(Vector3{ -3, 13, 10 }, Vector3{ -500, 0, 0 }, 5, 1, 2);

	// snake
	std::shared_ptr<ForceField> field_fun_snake1 = std::make_shared<ForceField>(Vector3{ 11, 27, 10 }, Vector3{ 500, -500, 0 }, 5, 3, 2);
	std::shared_ptr<Box> box_fun_snake = std::make_shared<Box>(Vector3{ 8, 25, 10 }, 11, 1, 2);
	std::shared_ptr<ForceField> field_fun_snake = std::make_shared<ForceField>(Vector3{ 13, 24, 10 }, Vector3{ -500, 0, 0 }, 3, 1, 2);
	std::shared_ptr<Box> box_fun_snake3 = std::make_shared<Box>(Vector3{ 9, 23, 10 }, 11, 1, 2);
	std::shared_ptr<ForceField> field_fun_snake2 = std::make_shared<ForceField>(Vector3{ 3, 22, 10 }, Vector3{ 500, 0, 0 }, 3, 1, 2);
	std::shared_ptr<Box> box_fun_snake1 = std::make_shared<Box>(Vector3{ 8, 21, 10 }, 10, 1, 2);
	std::shared_ptr<Box> box_fun_snake2 = std::make_shared<Box>(Vector3{ 2, 23, 10 }, 1, 6, 2);

	// center
	std::shared_ptr<Box> box_fun15 = std::make_shared<Box>(Vector3{ 2, 8, 10 }, 7, 1, 2);
	std::shared_ptr<Box> box_fun16 = std::make_shared<Box>(Vector3{ 0, 10, 10 }, 2, 1, 2);
	std::shared_ptr<Box> box_fun17 = std::make_shared<Box>(Vector3{ -1, 10, 10 }, 1, 5, 2);
	std::shared_ptr<ForceField> field_fun3 = std::make_shared<ForceField>(Vector3{ 4, 9, 10 }, Vector3{ -1000, 0, 0 }, 5, 1, 2);
	std::shared_ptr<ForceField> field_fun4 = std::make_shared<ForceField>(Vector3{ 1, 13, 10 }, Vector3{ -1000, 0, 0 }, 5, 5, 2);

	std::shared_ptr<ForceField> field_fun2 = std::make_shared<ForceField>(Vector3{ 12, 9, 10 }, Vector3{ -1000, 0, 0 }, 5, 1, 2);

	std::shared_ptr<ForceField> field_fun5 = std::make_shared<ForceField>(Vector3{ 3, 1, 10 }, Vector3{ -1000, 0, 0 }, 20, 1, 2);


	/*filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle_fun));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle_fun2));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle_fun3));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle_fun4));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle_fun5));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(particle_fun6));*/


	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun2));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun3));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun4));

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_back));

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun5));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun6));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun7));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun8));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun9));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun10));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun11));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun12));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun13));

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun14));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_chute));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_chute1));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_chute2));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun_chute));

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_chute_2));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_chute_2_1));

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_splitter));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_splitter1));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_splitter2));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun_splitter));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun_splitter1));

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_snake));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_snake1));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_snake2));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun_snake3));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun_snake));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun_snake1));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun_snake2));

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun15));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun16));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(box_fun17));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun3));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun4));

	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun2));
	filthyEngine->AddObjectToSimulation(std::static_pointer_cast<PhysicsObject>(field_fun5));


	SetTargetFPS(60);

	std::unique_ptr<TaitoCar> car = std::make_unique<TaitoCar>(carModel);


	bool shouldStepPhysics = true;
	bool stepOneFrame = false;


	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{

		// gameplay



		if (IsKeyPressed(KEY_SIX))
		{
			shouldStepPhysics = !shouldStepPhysics;
		}
		if (!shouldStepPhysics && IsKeyPressed(KEY_SEVEN))
		{
			shouldStepPhysics = true;
			stepOneFrame = true;
		}

		if(shouldStepPhysics)
		{
			box6->Offset(Vector3{ 0, std::sinf(filthyEngine->GetPhysicsTime()), 0 });
			box6b->Offset(Vector3{ 0, std::sinf(filthyEngine->GetPhysicsTime()) * 3, 0 });

			box_fun16->Offset(Vector3{ 0, std::sinf(filthyEngine->GetPhysicsTime()) * 2, 0 });
		}

		// end gameplay


		// render + physics
		
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);
				
				//DrawCube({ -4.0f, 0.0f, 2.0f }, 1.0f, 1.0f, 1.0f, RED);

				if(shouldStepPhysics)
				{
					filthyEngine->Update();
				}
				filthyEngine->Draw();

				DrawGrid(100, 1.0f);

				DrawLine3D({ 0,0,0 }, { 3, 0, 0 }, RED);
				DrawLine3D({ 0,0,0 }, { 0, 0, 3 }, GREEN);
				DrawLine3D({ 0,0,0 }, { 0, 3, 0 }, BLUE);

			EndMode3D();

			filthyEngine->DrawDebugForObject();

			// end render + physics
			

			DrawFPS(10, 10);

		EndDrawing();

		if (stepOneFrame)
		{
			stepOneFrame = false;
			shouldStepPhysics = false;
		}
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}