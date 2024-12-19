#pragma once

#include "raylib.h"

#ifndef TILE_H
#define TILE_H

enum TileState
{
	Hidden, Flipped, Found
};

class Tile
{
public:
	Tile(int h, int x, int tileSize, int num);

	Rectangle rect;
	Vector2 txtPos;
	int num;

	TileState state = TileState::Hidden;

	Color bgColor;
	Color txtColor;

	void Draw();

private:

};

#endif // !TILE_H
