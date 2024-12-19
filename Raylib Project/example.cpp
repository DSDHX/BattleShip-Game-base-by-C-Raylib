#include "example.h"

void Example::Main()
{
	Start(); // do all initial settings

	InitWindow(500, 500, "Raylib Template");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		Update(); // do all settings
		Draw(); // draw all my object

		EndDrawing();
	}
	CloseWindow();
}

void Example::Start()
{

}

void Example::Draw()
{

}

void Example::Update()
{

}