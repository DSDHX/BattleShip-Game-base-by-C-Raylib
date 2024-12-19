#ifndef GRID_H
#define GRID_H

#include "raylib.h"
#include "Ship.h"
#include <vector>

enum CellState
{
	EMPTY, SHIP, MISS, HIT
};

class Grid
{
public:
	Grid(int gridSize, int cellSize, int startX, int startY);

	void Initialize();
	bool CanPlaceShip(const Ship& ship) const;
	void PlaceShip(const Ship& ship);
	CellState GetCellState(int x, int y) const;
	void SetCellState(int x, int y, CellState state);

	void DrawGrid() const;
	void DrawShips(bool showShips) const;
	void DrawAttacks() const;

	bool IsAllShipsSunk() const;
	std::vector<Ship>& GetShips();

private:
	int gridSize;
	int cellSize;
	int startX;
	int startY;
	std::vector<std::vector<CellState>> cells;
	std::vector<Ship> ships;
};

#endif // !GRID_H