#include <raylib.h>
#include "PathFinding.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>

void PathFinding::Main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	Start();

	InitWindow(screenWidth, screenHeight, "PathFinding");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		Update();
		Draw();
	
		EndDrawing();
	}
	CloseWindow();
}

void PathFinding::Start()
{
	int left = (screenWidth - (COL_COUNT * NODE_SIZE)) / 2;
	int top = (screenHeight - (ROW_COUNT * NODE_SIZE)) / 2;

	Vector2 tl = { left, top };

	grid.clear();
	for (int row = 0; row < ROW_COUNT; row++)
	{
		std::vector<Node> rowNodes;
		for (int col = 0; col < COL_COUNT; col++)
		{
			Vector2 pos = { NODE_SIZE * col + tl.x, NODE_SIZE * row + tl.y};
			Node node = { row, col, pos, DARKGRAY };
			rowNodes.push_back(node);
		}
		grid.push_back(rowNodes);
	}

	int twentyPercent = (int)(ROW_COUNT * COL_COUNT * 0.3);
	for (int i = 0; i < twentyPercent; i++)
	{
		int r = std::rand() % grid.size();
		int c = std::rand() % grid[r].size();

		while (grid[r][c].blocked)
		{
			r = std::rand() % grid.size();
			c = std::rand() % grid[r].size();
		}
		grid[r][c].blocked = true;
	}

	int r = std::rand() % grid.size();
	int c = std::rand() % grid[r].size();
	while (grid[r][c].blocked)
	{
		r = std::rand() % grid.size();
		c = std::rand() % grid[r].size();
	}
	pointA = grid[r][c];
	pointA.fillColor = BLUE;
	pointA.blocked = true;
	pointA.txt = "A";

	r = std::rand() % grid.size();
	c = std::rand() % grid[r].size();
	while (grid[r][c].blocked)
	{
		r = std::rand() % grid.size();
		c = std::rand() % grid[r].size();
	}
	pointB = grid[r][c];
	pointB.fillColor = GREEN;
	pointB.blocked = true;
	pointB.txt = "B";

	// make sure
	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.visited = false;
			node.parent = nullptr;
		}
	}

	path.clear();
}

void PathFinding::Draw()
{
	for (Node* node : path)
	{
		DrawRectangleV(node->position, Vector2{ NODE_SIZE, NODE_SIZE }, YELLOW);
	}

	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			Node& node = grid[row][col];
			node.Draw();
			
			// 1. visited = true
			// 2. not in path
			// 3. not start or end
			// 4. not blank cell
			//&& std::find(path.begin(), path.end(), &node) == path.end()
			if (node.visited && &node != &grid[pointA.row][pointA.col] && &node != &grid[pointB.row][pointB.col]
				&& !node.blocked)
			{
				int fontSize = 20;
				std::string txt = std::to_string(node.distanceFromStart);
				int txtWidth = MeasureText(txt.c_str(), fontSize);
				int txtPosX = node.position.x + 25 - txtWidth / 2;
				int txtPosY = node.position.y + 25 - fontSize / 2;
				DrawText(txt.c_str(), txtPosX, txtPosY, fontSize, BLACK);
			}
		}
	}

	pointA.Draw();
	pointB.Draw();
}

void PathFinding::BFS()
{
	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.visited = false;
			node.parent = nullptr;
			node.distanceFromStart = -1;
			node.txt = "";
		}
	}

	std::queue<Node*> q;
	Node* startNode = &grid[pointA.row][pointA.col];
	Node* endNode = &grid[pointB.row][pointB.col];

	startNode->visited = true;
	startNode->distanceFromStart = 0;
	q.push(startNode);

	bool found = false;

	while (!q.empty() && !found)
	{
		Node* current = q.front();
		q.pop();

		if (current == endNode)
		{
			found = true;
			break;
		}

		std::vector<Node*> neighbors;

		if (current->row > 0) // UP
		{
			neighbors.push_back(&grid[current->row - 1][current->col]);
		}
		if (current->row < ROW_COUNT - 1) // DOWN
		{
			neighbors.push_back(&grid[current->row + 1][current->col]);
		}
		if (current->col > 0) // LEFT
		{
			neighbors.push_back(&grid[current->row][current->col - 1]);
		}
		if (current->col < COL_COUNT - 1) // RIGHT
		{
			neighbors.push_back(&grid[current->row][current->col + 1]);
		}

		for (Node* neighbor : neighbors)
		{
			if (!neighbor->visited && !neighbor->blocked)
			{
				neighbor->visited = true;
				neighbor->parent = current;
				neighbor->distanceFromStart = current->distanceFromStart + 1;
				q.push(neighbor);
			}
		}
	}

	if (found)
	{
		path.clear();

		Node* current = endNode;
		while (current != nullptr)
		{
			path.push_back(current);
			current = current->parent;
		}

		//std::reverse(path.begin(), path.end());
	}
	else
	{
		std::cout << "CAN NOT FOUND PATH!" << std::endl;
	}
}

void PathFinding::Update()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		BFS();
	}
	if (IsKeyPressed(KEY_R))
	{
		Start();
	}
}