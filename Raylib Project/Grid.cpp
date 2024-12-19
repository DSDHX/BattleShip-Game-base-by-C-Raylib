#include "Grid.h"
#include "Constants.h"

Grid::Grid(int gridSize, int cellSize, int startX, int startY) :
	gridSize(gridSize), cellSize(cellSize), startX(startX), startY(startY)
{
	Initialize();
}

void Grid::Initialize()
{
	cells.resize(gridSize, std::vector<CellState>(gridSize, EMPTY));
	ships.clear();
}

bool Grid::CanPlaceShip(const Ship& ship) const
{
	int x = ship.GetPosition().x;
	int y = ship.GetPosition().y;
	int size = ship.GetSize();
	bool horizontal = ship.IsHorizontal();

	if (horizontal && x + size > gridSize)
	{
		return false;
	}
	if (!horizontal && y + size > gridSize)
	{
		return false;
	}

	for (const Ship& existingShip : ships)
	{
		for (int i = 0; i < existingShip.GetSize(); i++)
		{
			int ex = existingShip.GetPosition().x + (existingShip.IsHorizontal() ? i : 0);
			int ey = existingShip.GetPosition().y + (existingShip.IsHorizontal() ? 0 : i);

			for (int j = 0; j < size; j++)
			{
				int nx = x + (horizontal ? j : 0);
				int ny = y + (horizontal ? 0 : j);

				if (ex == nx && ey == ny)
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Grid::PlaceShip(const Ship& ship)
{
	ships.push_back(ship);
	int x = ship.GetPosition().x;
	int y = ship.GetPosition().y;
	int size = ship.GetSize();
	bool horizontal = ship.IsHorizontal();

	for (int i = 0; i < size; i++)
	{
		int nx = x + (horizontal ? i : 0);
		int ny = y + (horizontal ? 0 : i);

		cells[nx][ny] = SHIP;
	}
}

CellState Grid::GetCellState(int x, int y) const
{
	if (x >= 0 && x < gridSize && y >= 0 && y < gridSize)
	{
		return cells[x][y];
	}
	return EMPTY;
}

void Grid::SetCellState(int x, int y, CellState state)
{
	if (x >= 0 && x < gridSize && y >= 0 && y < gridSize)
	{
		cells[x][y] = state;
	}
}

void Grid::DrawGrid() const
{
	for (int i = 0; i <= gridSize; i++)
	{
		DrawLine(startX, startY + i * cellSize, startX + gridSize * cellSize, startY + i * cellSize, GRAY);
		DrawLine(startX + i * cellSize, startY, startX + i * cellSize, startY + gridSize * cellSize, GRAY);
	}

	const char* playerLabel = "Player";
	int labelFontSize = 30;
	int playerLabelWidth = MeasureText(playerLabel, labelFontSize);
	DrawText(playerLabel, Constants::playerGridX +
		(Constants::gridSize * Constants::cellSize - playerLabelWidth) / 2,
		Constants::playerGridY - 40, labelFontSize, BLACK);

	const char* computerLabel = "Computer";
	int computerLabelWidth = MeasureText(computerLabel, labelFontSize);
	DrawText(computerLabel, Constants::computerGridX +
		(Constants::gridSize * Constants::cellSize - computerLabelWidth) / 2,
		Constants::computerGridY - 40, labelFontSize, BLACK);
}

void Grid::DrawShips(bool showShips) const
{
	if (!showShips) return;

	for (const Ship& ship : ships)
	{
		for (int i = 0; i < ship.GetSize(); i++)
		{
			int x = ship.GetPosition().x + (ship.IsHorizontal() ? i : 0);
			int y = ship.GetPosition().y + (ship.IsHorizontal() ? 0 : i);

			DrawRectangle(startX + x * cellSize, startY + y * cellSize, cellSize, cellSize, BLUE);
		}
	}
}

void Grid::DrawAttacks() const
{
	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			int drawX = startX + x * cellSize;
			int drawY = startY + y * cellSize;
			CellState state = cells[x][y];
			if (state == HIT)
			{
				DrawCircle(drawX + cellSize / 2, drawY + cellSize / 2, cellSize / 4, DARKGREEN);
			}
			else if (state == MISS)
			{
				DrawLine(drawX, drawY, drawX + cellSize, drawY + cellSize, RED);
				DrawLine(drawX + cellSize, drawY, drawX, drawY + cellSize, RED);
			}
		}
	}
}

bool Grid::IsAllShipsSunk() const
{
	for (const Ship& ship : ships)
	{
		if (!ship.IsSunk())
		{
			return false;
		}
	}
	return true;
}

std::vector<Ship>& Grid::GetShips()
{
	return ships;
}