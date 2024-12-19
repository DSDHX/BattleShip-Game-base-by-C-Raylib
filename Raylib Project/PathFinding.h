#pragma once

#include "raylib.h"
#include <iostream>
#include <vector>

#ifndef PATHFINDING_H
#define PATHFINDING_H

struct Node
{
	int row, col;
	Vector2 position;
	Color fillColor, outlineColor;
	bool blocked = false;
	bool visited = false; //
	Node* parent = nullptr; //
	int distanceFromStart = -1; // record number
	std::string txt = "";

	Node(int row = 0, int col = 0, Vector2 position = {}, Color fillColor = BLACK,
		Color outlineColor = GRAY)
	{
		this->position = position;
		this->row = row;
		this->col = col;
		this->fillColor = fillColor;
		this->outlineColor = outlineColor;
	}

	void Draw()
	{
		if (blocked)
		{
			DrawRectangleV(position, Vector2{ 50, 50 }, fillColor);
		}
		else
		{
			DrawRectangleLines(position.x, position.y, 50, 50, outlineColor);
		}
		
		if (!txt.empty())
		{
			int fontSize = 20;
			int txtWidth = MeasureText(txt.c_str(), fontSize);
			int txtPosX = position.x + 25 - txtWidth / 2;
			int txtPosY = position.y + 25 - fontSize / 2;
			DrawText(txt.c_str(), txtPosX, txtPosY, fontSize, BLACK);
		}
	}
};

class PathFinding
{
public:
#define ROW_COUNT 10
#define COL_COUNT 20
#define NODE_SIZE 50

	const int screenWidth = 1258;
	const int screenHeight = 729;

	std::vector<std::vector<Node>> grid;
	Node pointA, pointB;

	std::vector<Node*> path;

	void Main();
	void Start();
	void Draw();
	void Update();
	void BFS(); //

private:

};

#endif // !PATHFINDING_H