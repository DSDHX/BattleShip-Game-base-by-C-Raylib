#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include <raymath.h>

#ifndef WALLBREAKER_H
#define WALLBREAKER_H

class WallBreaker
{
public:
#define MAX_LIVES 5

	float brickGap;
	float brickHeight;
	int rowCount;
	int colCount;

	typedef struct Player
	{
		int currentLife;
		Vector2 position;
		Vector2 size = { 125, 25 };

		void Draw()
		{
			int xCen = position.x - size.x / 2;
			int yCen = position.y + size.y / 2;

			Rectangle rect = Rectangle{ (float)xCen, (float)yCen, size.x, size.y };

			DrawRectangleRounded(rect, 0.4, 12, DARKGREEN);
		}
	};
	Player player = { 0 };

	typedef struct Ball
	{
		Vector2 position;
		int radius = 12;
		bool active = false;
		Vector2 speed;

		void Draw()
		{
			DrawCircle(position.x, position.y, radius, BLUE);
		}
	};
	Ball ball = { 0 };

	typedef struct Brick
	{
		Color color;
		Rectangle rect;
		float roundness;
		int segments;
		void Draw()
		{
			DrawRectangleRounded(rect, roundness, segments, color);
		}
	};
	std::vector<Brick> bricks;

	bool CheckBallBrickCollision(Ball& ball, Brick& brick,
		Vector2& collisionNormal);

	static const int screenWidth = 1400;
	static const int screenHeigh = 500;

	void Main();
	void Start();
	void Draw();
	void Update();

private:

};

#endif // !WALLBREAKER_H