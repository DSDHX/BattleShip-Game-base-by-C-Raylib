#include "Ship.h"

Ship::Ship(int size, Vector2 position, bool horizontal) :
	size(size), position(position), horizontal(horizontal), sunk(false)
{
	hits = std::vector<bool>(size, false);
}

int Ship::GetSize() const
{
	return size;
}

Vector2 Ship::GetPosition() const
{
	return position;
}

bool Ship::IsHorizontal() const
{
	return horizontal;
}

bool Ship::IsSunk() const
{
	return sunk;
}

void Ship::SetHit(int index)
{
	if (index >= 0 && index < size)
	{
		hits[index] = true;
		UpdateSunkStatus();
	}
}

bool Ship::IsHitAt(int index) const
{
	if (index >= 0 && index < size)
	{
		return hits[index];
	}
	return false;
}

void Ship::UpdateSunkStatus()
{
	for (bool partHit : hits)
	{
		if (!partHit)
		{
			sunk = false;
			return;
		}
	}
	sunk = true;
}