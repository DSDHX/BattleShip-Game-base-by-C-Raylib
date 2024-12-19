#pragma once

#include "raylib.h"
#include <vector>

#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
#define TILE_SIZE 50

	static const int screenWidth = 800;
	static const int screenHeight = 600;

	Vector2 borderGap = { screenWidth % TILE_SIZE, screenHeight % TILE_SIZE };

	typedef struct Piece
	{
		Vector2 position;
		Vector2 size = { TILE_SIZE, TILE_SIZE };
		Color color;

		void Draw()
		{
			DrawRectangleV(position, size, color);
		}
	};

	std::vector<Piece> players;
	Piece food; // Add a piece for food

	int frameCount = 0;
	Vector2 speed = { TILE_SIZE, 0 };
	bool gameOver = false;

	void Main();
	void Start();
	void Draw();
	void Update();
	void Interaction();
	void CheckBorderCollision();
	void SpawnFood();
	void CheckFoodCollision();
	void CheckSelfCollision();

private:

};

#endif // !SNAKE_H