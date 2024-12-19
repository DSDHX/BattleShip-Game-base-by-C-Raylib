#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants
{
	//constant value
	const int screenWidth = 1400;
	const int screenHeight = 700;

	const int gridSize = 10; // 10x10
	const int cellSize = 50; // pixel for one cell
	const int gridMargin = 90; // distance away border

	const int playerGridX = gridMargin;
	const int playerGridY = gridMargin;

	const int computerGridX = screenWidth - gridMargin - gridSize * cellSize;
	const int computerGridY = gridMargin;
}

#endif // !CONSTANTS_H