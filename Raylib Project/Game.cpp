#include "Game.h"
#include "Constants.h"

Game::Game()
	: playerGrid(Constants::gridSize, Constants::cellSize, Constants::playerGridX, Constants::playerGridY),
	computerGrid(Constants::gridSize, Constants::cellSize, Constants::computerGridX, Constants::computerGridY),
	player(true, playerGrid),
	computer(false, computerGrid),
	placingShips(true),
	currentShipIndex(0),
	isHorizontal(true),
	playerTurn(true),
	gameOver(false)
{
	shipSizes = { 5, 4, 3, 3, 2 };
}

void Game::Initialize()
{
	playerGrid.Initialize();
	computerGrid.Initialize();
	placingShips = true;
	currentShipIndex = 0;
	isHorizontal = true;
	playerTurn = true;
	gameOver = false;
	gameState = GameState::MainMenu;
}

void Game::HandleMainMenuInput()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		gameState = GameState::PlacingShips;
	}
	else if (IsKeyPressed(KEY_ESCAPE))
	{
		CloseWindow();
		exit(0);
	}
}

void Game::Update()
{
	switch (gameState)
	{
	case GameState::MainMenu:
		HandleMainMenuInput();
		break;

	case GameState::PlacingShips:
		HandlePlayerShipPlacement();
		break;

	case GameState::PlayerTurn:
		HandlePlayerAttack();
		break;

	case GameState::ComputerTurn:
		ComputerAttack();
		break;

	case GameState::GameOver:
		break;

	default:
		break;
	}
}

void Game::DrawMainMenu()
{
	const char* title = "BattleShip";
	int titleFontSize = 60;
	int titleWidth = MeasureText(title, titleFontSize);
	DrawText(title, (Constants::screenWidth - titleWidth) / 2, 170, titleFontSize, DARKBLUE);

	const char* startText = "Press ENTER to start game";
	int startFontSize = 30;
	int startWidth = MeasureText(startText, startFontSize);
	DrawText(startText, (Constants::screenWidth - startWidth) / 2, 500, startFontSize, BLACK);

	const char* exitText = "Press ESC to quit game";
	int exitWidth = MeasureText(exitText, startFontSize);
	DrawText(exitText, (Constants::screenWidth - exitWidth) / 2, 550, startFontSize, BLACK);
}

void Game::DrawAttackPreview()
{
	Vector2 mousePos = GetMousePosition();
	int gridX = (mousePos.x - Constants::computerGridX) / Constants::cellSize;
	int gridY = (mousePos.y - Constants::computerGridY) / Constants::cellSize;

	if (gridX >= 0 && gridY < Constants::gridSize && gridY >= 0 && gridY < Constants::gridSize)
	{
		CellState state = computerGrid.GetCellState(gridX, gridY);
		if (state == EMPTY || state == SHIP)
		{
			Color previewColor = Fade(RED, 0.3f);
			DrawRectangle(Constants::computerGridX + gridX * Constants::cellSize,
				Constants::computerGridY + gridY * Constants::cellSize, Constants::cellSize,
				Constants::cellSize, previewColor);
		}
	}
}

void Game::Draw()
{
	switch (gameState)
	{
	case GameState::MainMenu:
		DrawMainMenu();
		break;

	case GameState::PlacingShips:
		playerGrid.DrawGrid();
		computerGrid.DrawGrid();

		playerGrid.DrawShips(true);
		break;

	case GameState::PlayerTurn:
		playerGrid.DrawGrid();
		computerGrid.DrawGrid();

		playerGrid.DrawShips(true);
		//computerGrid.DrawShips(true);

		playerGrid.DrawAttacks();
		computerGrid.DrawAttacks();

		DrawAttackPreview();
		break;

	case GameState::ComputerTurn:
		playerGrid.DrawGrid();
		computerGrid.DrawGrid();

		playerGrid.DrawShips(true);
		//computerGrid.DrawShips(true);

		playerGrid.DrawAttacks();
		computerGrid.DrawAttacks();
		break;

	case GameState::GameOver:
		playerGrid.DrawGrid();
		computerGrid.DrawGrid();

		playerGrid.DrawShips(true);
		//computerGrid.DrawShips(true);

		playerGrid.DrawAttacks();
		computerGrid.DrawAttacks();

		ShowGameOverMessage();
		break;

	default:
		break;
	}
}

void Game::PlaceComputerShips()
{
	int shipIndex = 0;
	while (shipIndex < shipSizes.size())
	{
		bool horizontal = GetRandomValue(0, 1) == 1;
		int x = GetRandomValue(0, Constants::gridSize - 1);
		int y = GetRandomValue(0, Constants::gridSize - 1);

		Ship tempShip(shipSizes[shipIndex], { (float)x, (float)y }, horizontal);

		if (computerGrid.CanPlaceShip(tempShip))
		{
			computerGrid.PlaceShip(tempShip);
			shipIndex++;
		}
	}
}

void Game::HandlePlayerShipPlacement()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		isHorizontal = !isHorizontal;
	}

	Vector2 mousePos = GetMousePosition();
	int gridX = (mousePos.x - Constants::playerGridX) / Constants::cellSize;
	int gridY = (mousePos.y - Constants::playerGridY) / Constants::cellSize;

	if (gridX >= 0 && gridX < Constants::gridSize && gridY >= 0 && gridY < Constants::gridSize)
	{
		int	shipSize = shipSizes[currentShipIndex];
		Ship tempShip(shipSize, { (float)gridX, (float)gridY }, isHorizontal);

		Color previewColor = DARKGREEN;

		if (!playerGrid.CanPlaceShip(tempShip))
		{
			previewColor = RED;
		}

		for (int i = 0; i < shipSize; i++)
		{
			int x = gridX + (isHorizontal ? i : 0);
			int y = gridY + (isHorizontal ? 0 : i);

			if (x < Constants::gridSize && y < Constants::gridSize)
			{
				DrawRectangle(Constants::playerGridX + x * Constants::cellSize,
					Constants::playerGridY + y * Constants::cellSize, Constants::cellSize,
					Constants::cellSize, previewColor);
			}
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (playerGrid.CanPlaceShip(tempShip))
			{
				playerGrid.PlaceShip(tempShip);
				currentShipIndex++;
				if (currentShipIndex >= shipSizes.size())
				{
					placingShips = false;
					PlaceComputerShips();
					gameState = GameState::PlayerTurn;
				}
			}
		}
	}
}

void Game::HandlePlayerAttack()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = GetMousePosition();
		int gridX = (mousePos.x - Constants::computerGridX) / Constants::cellSize;
		int gridY = (mousePos.y - Constants::computerGridY) / Constants::cellSize;

		if (gridX >= 0 && gridX < Constants::gridSize && gridY >= 0 && gridY < Constants::gridSize)
		{
			CellState state = computerGrid.GetCellState(gridX, gridY);
			if (state == EMPTY || state == SHIP)
			{
				if (state == SHIP)
				{
					computerGrid.SetCellState(gridX, gridY, HIT);
					UpdateShipState(computer, { (float)gridX, (float)gridY });
					if (computerGrid.IsAllShipsSunk())
					{
						gameOver = true;
					}
				}
				else
				{
					computerGrid.SetCellState(gridX, gridY, MISS);
				}
				playerTurn = false;
			}
		}

		if (!gameOver)
		{
			gameState = GameState::ComputerTurn;
		}
		else
		{
			gameState = GameState::GameOver;
		}
	}
}

void Game::ComputerAttack()
{
	int x, y;
	do
	{
		x = GetRandomValue(0, Constants::gridSize - 1);
		y = GetRandomValue(0, Constants::gridSize - 1);
	} while (playerGrid.GetCellState(x, y) == MISS || playerGrid.GetCellState(x, y) == HIT);

	CellState state = playerGrid.GetCellState(x, y);
	if (state == SHIP)
	{
		playerGrid.SetCellState(x, y, HIT);
		UpdateShipState(player, { (float)x, (float)y });
		if (playerGrid.IsAllShipsSunk())
		{
			gameOver = true;
			gameState = GameState::GameOver;
		}
	}
	else
	{
		playerGrid.SetCellState(x, y, MISS);
	}
	playerTurn = true;

	if (!gameOver)
	{
		gameState = GameState::PlayerTurn;
	}
}

void Game::UpdateShipState(Player& player, Vector2 hitPos)
{
	std::vector<Ship>& ships = player.GetGrid().GetShips();

	for (Ship& ship : ships)
	{
		for (int i = 0; i < ship.GetSize(); i++)
		{
			int x = ship.GetPosition().x + (ship.IsHorizontal() ? i : 0);
			int y = ship.GetPosition().y + (ship.IsHorizontal() ? 0 : i);
			if (x == hitPos.x && y == hitPos.y)
			{
				ship.SetHit(i);
				if (ship.IsSunk())
				{
					// hint
				}
				break;
			}
		}
	}
}

void Game::ShowGameOverMessage()
{
	const char* message = playerGrid.IsAllShipsSunk() ? "YOU LOSS!" : "YOU WIN!";
	int fontSize = 40;
	int textWidth = MeasureText(message, fontSize);
	DrawText(message, (Constants::screenWidth - textWidth) / 2,
		Constants::screenHeight / 2 - fontSize / 2, fontSize, RED);

	DrawText("Press ENTER back to main menu", ((Constants::screenWidth - textWidth) / 2) - 50,
		Constants::screenHeight / 2 + 260, 20, BLACK);

	if (IsKeyPressed(KEY_ENTER))
	{
		Initialize();
	}
}