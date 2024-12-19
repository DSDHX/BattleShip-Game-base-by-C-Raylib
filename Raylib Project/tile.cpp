#include "tile.h"
#include "raylib.h"
#include "Memory1.h"
#include <string>

Tile::Tile(int h, int v, int tileSize, int num)
{
	//define the ract
	rect = Rectangle{ (float)h * (tileSize + GAP) + GAP,
					  (float)v * (tileSize + GAP) + GAP,
					  (float)tileSize,
					  (float)tileSize };

	this->num = num;
}

void Tile::Draw()
{
	float fontSize = 50;
	std::string txt = "";
	float txtWideth;

	switch (state)
	{
	case Hidden:

		txt = "?";
		bgColor = DARKGRAY;
		txtColor = WHITE;

		break;

	case Flipped:
		txt = std::to_string(num);
		bgColor = ORANGE;
		txtColor = BLACK;

		break;

	case Found:
		txt = "";
		bgColor = GRAY;
		break;

	default:
		break;
	}

	txtWideth = MeasureText(txt.c_str(), fontSize);
	DrawRectangleRounded(rect, 0.2, 12, bgColor);
	txtPos = { rect.x + rect.width / 2 - txtWideth / 2,
		   rect.y + rect.height / 2 - fontSize / 2 };
	DrawText(txt.c_str(), txtPos.x, txtPos.y, fontSize, txtColor);
}