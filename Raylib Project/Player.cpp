#include "Player.h"

Player::Player(bool isHuman, Grid& grid) : isHuman(isHuman), grid(grid) { }

bool Player::IsHuman() const
{
	return isHuman;
}

Grid& Player::GetGrid()
{
	return grid;
}