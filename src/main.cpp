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

#include "TaitoCar.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	Camera camera = { 0 };
	camera.position = { 10.0f, 100.0f, -5.0f };
	camera.target = { 10.0f, 0.0f, -25.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;



	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Model carModel = LoadModel("RaceCar.glb");
	Model trackModel = LoadModel("Track.glb");

	SetTargetFPS(60);

	std::unique_ptr<TaitoCar> car = std::make_unique<TaitoCar>(carModel);
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		
		if (IsKeyDown(KEY_UP))
		{
			camera.target.z -= 1;
		}

		car->Update();

		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);
				
				DrawCube({ -4.0f, 0.0f, 2.0f }, 1.0f, 1.0f, 1.0f, RED);

				DrawModelEx(trackModel, { 0,0,0 }, { 0,0,0 }, 0, { 1,1,1 }, WHITE);

				car->Draw3D();

				DrawGrid(10, 1.0f);

				DrawLine3D({ 0,0,0 }, { 3, 0, 0 }, RED);
				DrawLine3D({ 0,0,0 }, { 0, 0, 3 }, GREEN);
				DrawLine3D({ 0,0,0 }, { 0, 3, 0 }, BLUE);

			EndMode3D();

			car->Draw();
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