#ifndef SHIP_H
#define SHIP_H

#include "raylib.h"
#include <vector>

class Ship
{
public:
	Ship(int size, Vector2 position, bool horizontal);

	int GetSize() const;
	Vector2 GetPosition() const;
	bool IsHorizontal() const;
	bool IsSunk() const;

	void SetHit(int index);
	bool IsHitAt(int index) const;

private:
	int size;
	Vector2 position;
	bool horizontal;
	std::vector<bool> hits;
	bool sunk;

	void UpdateSunkStatus();
};

#endif // !SHIP_H