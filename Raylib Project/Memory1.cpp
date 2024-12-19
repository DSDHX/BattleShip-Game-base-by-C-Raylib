#include "Memory1.h"
#include <time.h>

void Memory::Main()
{
	Start(); // do all initial settings

	InitWindow(widthHeight, widthHeight, "Memory Puzzle Game");
	SetTargetFPS(60);

	WholeBGColor = RAYWHITE;

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WholeBGColor);

		Update(); // do all settings
		Draw(); // draw all my object

		EndDrawing();
	}
	CloseWindow();
}

void Memory::Start()
{
	tilesArr.clear();
	int tileSize = (int)((widthHeight - (GAP * (gridSize + 1))) / gridSize);
	
	std::vector<int> numbers;
	for (int i = 0; i < gridSize * gridSize / 2; i++)
	{
		numbers.push_back(i + 1); // 1 -> 8
		numbers.push_back(i + 1); // 1 -> 8
	}

	srand(time(NULL));
	for (int row = 0; row < gridSize; row++)
	{
		for (int col = 0; col < gridSize; col++)
		{
			int randomIndex = rand() % numbers.size(); 
			int tileNum = numbers[randomIndex];
			Tile tile = Tile(row, col, tileSize, tileNum);
			tilesArr.push_back(tile);
			numbers.erase(numbers.begin() + randomIndex);
		}
	}

}

void Memory::Draw()
{
	if (!gameFinished)
	{
		for (Tile tile : tilesArr)
		{
			tile.Draw();
		}
	}
}

void Memory::Update()
{
	if (compareMode)
	{
		if (GetTime() > timeOfSecondClick + WAIT_TIME)
		{
			if (tile1->num == tile2->num)
			{
				tile1->state = Found;
				tile2->state = Found;

				gameFinished = true;
				for (int i = 0; i < tilesArr.size(); i++)
				{
					if (tilesArr[i].state == Hidden)
					{
						gameFinished = false;
						break;
					}
				}
			}
			else
			{
				tile1->state = Hidden;
				tile2->state = Hidden;
			}
			tile1 = nullptr;
			tile2 = nullptr;
			compareMode = false;
		}
		return;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < tilesArr.size(); i++)
		{
			if (CheckCollisionPointRec(GetMousePosition(), tilesArr[i].rect))
			{
				if (tilesArr[i].state != Hidden)
				{
					return;
				}

				tilesArr[i].state = Flipped;

				if (tile1 == nullptr)
				{
					tile1 = &tilesArr[i];
				}
				else
				{
					tile2 = &tilesArr[i];
					compareMode = true;
					timeOfSecondClick = GetTime();
				}
			}
		}
	}
}