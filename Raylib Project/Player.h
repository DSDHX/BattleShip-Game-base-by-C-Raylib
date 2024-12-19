#ifndef PLAYER_H
#define PLAYER_H

#include "Grid.h"

class Player
{
public:
	Player(bool isHuman, Grid& grid);

	bool IsHuman() const;
	Grid& GetGrid();

private:
	bool isHuman;
	Grid& grid;
};

#endif // !PLAYER_H