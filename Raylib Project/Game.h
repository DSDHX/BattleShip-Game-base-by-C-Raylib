#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <vector>
#include "Constants.h"

enum class GameState
{
	MainMenu, PlacingShips, PlayerTurn, ComputerTurn, GameOver
};

class Game
{
public:
	Game();

	void Initialize();
	void Update();
	void Draw();

private:
	GameState gameState;
	Grid playerGrid;
	Grid computerGrid;
	Player player;
	Player computer;
	bool placingShips;
	int currentShipIndex;
	bool isHorizontal;
	bool playerTurn;
	bool gameOver;
	std::vector<int> shipSizes;

	void HandlePlayerShipPlacement();
	void HandlePlayerAttack();
	void ComputerAttack();
	void UpdateShipState(Player& player, Vector2 hitPos);
	void ShowGameOverMessage();
	void PlaceComputerShips();
	void DrawMainMenu();
	void HandleMainMenuInput();
	void DrawAttackPreview();
};

#endif // !GAME_H