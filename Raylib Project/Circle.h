#pragma once
#include <raylib.h>
#include <math.h>
#include <algorithm>
#include <iostream>

struct Circle
{
	Vector2 center;

	float angle;
	float radius;
	Color color;
	bool alive = true;

	float gravity = 10;
	float speed = 5;

	Circle(Vector2 center, float angle, float raidus, Color color)
	{
		this->center = center;
		this->angle = angle;
		this->radius = raidus;
		this->color = color;
	}

	//void Update()
	//{
	//	center.x += cos(angle * DEG2RAD) * speed;
	//	center.y += sin(angle * DEG2RAD) * speed + gravity;

	//	speed -= 0.1;

	//	speed = std::max(speed, 1);
	//}

	//void Draw()
	//{
	//	DrawCircleV(center, 20, BLUE);
	//}
};