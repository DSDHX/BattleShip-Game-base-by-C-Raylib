#include "raylib.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <algorithm>
#include <random>
#include <map>
#include "raymath.h"
#include "Game.h"
#include "Constants.h"

int main()
{
	InitWindow(Constants::screenWidth, Constants::screenHeight, "BattleShip");

	Game game;
	game.Initialize();

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		game.Update();
		game.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}