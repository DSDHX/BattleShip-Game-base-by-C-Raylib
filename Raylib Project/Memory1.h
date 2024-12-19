#pragma once

#include "raylib.h"
#include <vector>
#include "tile.h"

#ifndef MEMORY1_H
#define MEMORY1_H

class Memory
{
public:
#define GAP 8
#define WAIT_TIME 0.3

	int gridSize = 4;
	static const int widthHeight = 800;
	std::vector<Tile> tilesArr;
	Color WholeBGColor;
	bool compareMode = false;
	float timeOfSecondClick;

	bool gameFinished = false;

	Tile* tile1 = nullptr;
	Tile* tile2 = nullptr;

	void Main();
	void Start();
	void Draw();
	void Update();

private:

};

#endif // !MEMORY1_H