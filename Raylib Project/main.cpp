#include "raylib.h"
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <deque>
#include "Memory1.h"
#include <algorithm>
#include <random>
#include <map>
#include "raymath.h"
#include "Game.h"
#include "Constants.h"

//class GameWindow
//{
//public:
//	GameWindow(int width, int height, const std::string& title)
//	{
//		InitWindow(width, height, title.c_str());
//		SetTargetFPS(60);
//	}
//
//	~GameWindow()
//	{
//		CloseWindow();
//	}
//
//	bool ShouldClose() const
//	{
//		return WindowShouldClose();
//	}
//};
//
//class Renderer
//{
//public:
//	void Begin() const
//	{
//		BeginDrawing();
//	}
//
//	void End() const
//	{
//		EndDrawing();
//	}
//
//	void ClearBackground(Color color) const
//	{
//		::ClearBackground(color);
//	}
//
//	void DrawCircle(int centerX, int centerY, float radius, Color color) const
//	{
//		::DrawCircle(centerX, centerY, radius, color);
//	}
//
//	void DrawText(const std::string& text, int posX, int posY, int frontSize, Color color) const
//	{
//		::DrawText(text.c_str(), posX, posY, frontSize, color);
//	}
//};
//
//class Game
//{
//public:
//	Game() : window(500, 500, "My Game"), renderer() {}
//
//	void CircleRun()
//	{
//		while (!window.ShouldClose())
//		{
//			renderer.Begin();
//			renderer.ClearBackground(Color{ 40, 40, 40, 255 });
//
//			renderer.DrawCircle(100, 100, 20, WHITE);
//
//			std::string txt = "This is my game";
//			renderer.DrawText(txt, 150, 150, 24, RED);
//
//			renderer.End();
//		}
//	}
//
//	void LinesAndPolies()
//	{
//		while (!window.ShouldClose())
//		{
//			renderer.Begin();
//			renderer.ClearBackground(PURPLE);
//
//			DrawLine(100, 100, 300, 100, RED);
//			DrawCircle(200, 200, 50, BLUE);
//			DrawRectangle(100, 300, 200, 50, YELLOW);
//
//			DrawLineEx(Vector2{ 200, 50 }, Vector2{ 200, 400 }, 5, BLACK);
//
//			DrawPoly(Vector2{ 400, 200 }, 7, 50, 0, ORANGE);
//
//			renderer.End();
//		}
//	}
//
//	void PrintMousePositio()
//	{
//		while (!window.ShouldClose())
//		{
//			renderer.Begin();
//			renderer.ClearBackground(Color{ 40, 40, 40, 255 });
//
//			std::string mouseX = "Mouse X: " + std::to_string(GetMouseX());
//			std::string mouseY = "Mouse Y: " + std::to_string(GetMouseY());
//
//			DrawText(mouseX.c_str(), GetScreenWidth() / 2, GetScreenHeight() / 2, 24, RAYWHITE);
//			DrawText(mouseY.c_str(), GetScreenWidth() / 2, GetScreenHeight() / 2 + 40, 24, RAYWHITE);
//
//			renderer.End();
//		}
//	}
//
//	void DrawAnImage()
//	{
//		Image img = LoadImage("Resource Files/cat.jpg");
//
//		Texture2D tex = LoadTextureFromImage(img);
//		UnloadImage(img);
//
//		while (!window.ShouldClose())
//		{
//			renderer.Begin();
//			renderer.ClearBackground(Color{ 140, 140, 140, 255 });
//			DrawTexture(tex, 150, 150, WHITE);
//
//			renderer.End();
//		}
//	}
//
//private:
//	GameWindow window;
//	Renderer renderer;
//};
//
//void CalculateTriangle(Vector2 center, float sideLength, Vector2* vertices)
//{
//	float height = (sqrt(3) / 2) * sideLength;
//	vertices[0] = { center.x, center.y - (2.0f / 3.0f) * height };
//	vertices[1] = { center.x - sideLength / 2, center.y + (1.0f / 3.0f) * height };
//	vertices[2] = { center.x + sideLength / 2, center.y + (1.0f / 3.0f) * height };
//}
//
//int main()
//{
//	//Game game;
//
//	//game.CircleRun();
//	//game.LinesAndPolies();
//	//game.PrintMousePositio();
//	//game.DrawAnImage();
//
//	const int screenWidth = 500;
//	const int scrrenHeight = 500;
//	InitWindow(screenWidth, scrrenHeight, "Triangle and Circles");
//
//	Vector2 center = { screenWidth / 2, scrrenHeight / 2 };
//	float sideLength = 250.0f;
//	Vector2 vertries[3];
//	CalculateTriangle(center, sideLength, vertries);
//
//	float radius = sideLength / 1.8;
//
//	Vector2 circlePositions[3] = { vertries[0], vertries[1], vertries[2] };
//	Color circleColor[3] = { RED, GREEN, BLUE };
//
//	bool dragging[3] = { false, false, false };
//	Vector2 offset[3] = { 0 };
//
//	SetTargetFPS(60);
//
//	while (!WindowShouldClose())
//	{
//		Vector2 mousePosition = GetMousePosition();
//
//		for (int i = 0; i < 3; i++)
//		{
//			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
//				CheckCollisionPointCircle(mousePosition, circlePositions[i], radius))
//			{
//				dragging[i] = true;
//				offset[i] = { mousePosition.x - circlePositions[i].x, 
//					mousePosition.y - circlePositions[i].y };
//			}
//
//			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
//			{
//				dragging[i] = false;
//			}
//
//			if (dragging[i])
//			{
//				circlePositions[i] = { mousePosition.x - offset[i].x,
//					mousePosition.y - offset[i].y };
//			}
//		}
//
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//
//		DrawTriangle(vertries[0], vertries[1], vertries[2], BLACK);
//
//		BeginBlendMode(BLEND_ADDITIVE);
//
//		for (int i = 0; i < 3; i++)
//		{
//			DrawCircleV(circlePositions[i], radius, Fade(circleColor[i], 1.0f));
//		}
//
//		EndBlendMode();
//
//		EndDrawing();
//	}
//
//	CloseWindow();
//
//	return 0;
//}

//void DrawPolygon()
//{
//	int numOfCorners = 24; // this is the initial value
//	std::vector<Vector2> cornersArr;
//
//	int screenWidth = 500;
//	int screenHeight = 500;
//	InitWindow(screenWidth, screenHeight, "Polygoner");
//	SetTargetFPS(30);
//
//	Vector2 viewCenter = Vector2{ (float)(screenWidth / 2.0), (float)(screenHeight / 2.0) };
//
//	while (!WindowShouldClose())
//	{
//		// populate the cornersArr
//		float angle = 360.0 / numOfCorners; // 360 / 5 -> 72
//		if (cornersArr.size() < numOfCorners)
//		{
//			// push one moer corner into it
//			float x = cos(DEG2RAD * (angle * cornersArr.size())) * 100 + viewCenter.x; // cos
//			float y = sin(DEG2RAD * (angle * cornersArr.size())) * 100 + viewCenter.y; // sin
//			cornersArr.push_back(Vector2{ x, y });
//		}
//
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//
//		if (cornersArr.size() > 2)
//		{
//			for (int i = 0; i < cornersArr.size() - 1; i++)
//			{
//				DrawTriangle(viewCenter, cornersArr[(i + 1) % cornersArr.size()], cornersArr[i], 
//					Color{ (unsigned char)(colorAngle * i * r), (unsigned char)(colorAngle)})
//			}
//		}
//
//		EndDrawing();
//	}
//	CloseWindow();
//}

//void BouncingOffTheWalls()
//{
//	int w = 500;
//	int h = 500;
//
//	int x = 200;
//	int y = 200;
//	int r = 50;
//	float speedX = 5;
//	float speedY = 7;
//	float speedIncrease = 0.5;
//
//	srand(time(nullptr));
//
//	Color ballColor = WHITE;
//
//	std::deque<Vector2> trail;
//	int maxTrailLength = 50;
//	
//	InitWindow(w, h, "Bouncing Off the Walls");
//	SetTargetFPS(60);
//
//	while (!WindowShouldClose())
//	{
//		BeginDrawing();
//		ClearBackground(GRAY);
//
//		if (x + r >= w || x - r <= 0)
//		{
//			speedX *= -1;
//			ballColor = { static_cast<unsigned char>(rand() % 256),
//						  static_cast<unsigned char>(rand() % 256),
//						  static_cast<unsigned char>(rand() % 256), 255 };
//			speedX += (speedX > 0 ? speedIncrease : -speedIncrease);
//		}
//		if (y + r >= h || y - r <= 0)
//		{
//			speedY *= -1;
//			ballColor = { static_cast<unsigned char>(rand() % 256),
//						  static_cast<unsigned char>(rand() % 256),
//						  static_cast<unsigned char>(rand() % 256), 255 };
//			speedY += (speedY > 0 ? speedIncrease : -speedIncrease);
//		}
//
//		x += speedX;
//		y += speedY;
//
//		trail.push_back({ static_cast<float>(x), static_cast<float>(y) });
//		if (trail.size() > maxTrailLength)
//		{
//			trail.pop_front();
//		}
//
//		for (const auto& position : trail)
//		{
//			DrawCircleV(position, r / 4, ballColor);
//		}
//
//		DrawCircle(x, y, r, ballColor);
//
//		std::string positionText = "x: " + std::to_string(x) + " y: " + std::to_string(y);
//		DrawText(positionText.c_str(), w - 200, h - 30, 30, WHITE);
//
//		EndDrawing();
//	}
//	CloseWindow();
//}
//
//int main()
//{
//	BouncingOffTheWalls();
//
//	return 0;
//}

//struct Ball
//{
//	Vector2 position;
//	Vector2 speed;
//	Color color;
//};
//
//bool CheckCollision_own(Vector2 circlePos, float radius, Rectangle rec)
//{
//	float closestX = fmax(rec.x, fmin(circlePos.x, rec.x + rec.width));
//	float closestY = fmax(rec.y, fmin(circlePos.y, rec.y + rec.height));
//
//	float distanceX = circlePos.x - closestX;
//	float distanceY = circlePos.y - closestY;
//
//	float distance = sqrt((distanceX * distanceY) + (distanceX * distanceY));
//
//	return distance <= radius;
//}
//
//int main()
//{
//	const int screenWidth = 800;
//	const int screenHeight = 600;
//	InitWindow(screenWidth, screenHeight, "Ball Fall Game");
//
//	Rectangle player = { screenWidth / 2 - 50, screenHeight - 40, 120, 25 };
//	int score = 0;
//	bool gameOver = false;
//
//	std::vector<Ball> balls;
//	std::srand(std::time(nullptr));
//
//	SetTargetFPS(60);
//
//	while (!WindowShouldClose())
//	{
//		if (!gameOver)
//		{
//			if (IsKeyDown(KEY_LEFT)) player.x -= 5.0f;
//			if (IsKeyDown(KEY_RIGHT)) player.x += 5.0f;
//
//			if (player.x < 0) player.x = 0;
//			if (player.x + player.width > screenWidth) player.x = screenWidth - player.width;
//
//			if (GetRandomValue(0, 100) < 2)
//			{
//				Ball ball;
//				ball.position = { (float)GetRandomValue(0, screenWidth), 0 };
//				ball.speed = { 0, (float)GetRandomValue(2, 5) };
//				ball.color = { (unsigned char)GetRandomValue(50, 255),
//							   (unsigned char)GetRandomValue(50, 255),
//							   (unsigned char)GetRandomValue(50, 255), 255 };
//				balls.push_back(ball);
//			}
//
//			for (auto& ball : balls)
//			{
//				ball.position.y += ball.speed.y;
//			}
//
//			for (auto it = balls.begin(); it != balls.end();)
//			{
//				if (CheckCollisionCircleRec(it->position, 10, player))
//				{
//					it = balls.erase(it);
//					score += 1;
//				}
//				else
//				{
//					++it;
//				}
//			}
//
//			for (const auto& ball : balls)
//			{
//				if (ball.position.y > screenHeight)
//				{
//					gameOver = true;
//				}
//			}
//		}
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//
//		if (!gameOver)
//		{
//			DrawRectangleRec(player, BLACK);
//			for (const auto& ball : balls)
//			{
//				DrawCircleV(ball.position, 10, ball.color);
//			}
//			DrawText(TextFormat("Score: %i", score), 10, 10, 30, DARKGRAY);
//		}
//		else
//		{
//			DrawText("GAME OVER!", screenWidth / 2 - MeasureText("GAME OVER!", 50) / 2,
//				screenHeight / 2 - 20, 50, RED);
//			DrawText(TextFormat("Final Score: %i", score),
//				screenWidth / 2 - MeasureText(TextFormat("Final Score: %i", score), 30) / 2,
//				screenHeight / 2 + 30, 30, DARKGRAY);
//		}
//
//		EndDrawing();
//	}
//
//	CloseWindow();
//	return 0;
//}

//int main()
//{
//	InitWindow(500, 500, "Circle Rect Collision");
//
//	SetTargetFPS(60);
//
//	int y = 100;
//	bool collision = false;
//	int r = 50;
//
//	Rectangle rect = { 200, 400, 100, 50 };
//
//	while (!WindowShouldClose())
//	{
//		BeginDrawing();
//		ClearBackground(GRAY);
//		Vector2 cen = { 250, y };
//		collision = CheckCollisionCircleRec(cen, r, rect);
//
//		if (!collision)
//		{
//			DrawCircle(cen.x, cen.y, r, BLUE);
//			y += 1;
//		}
//		DrawRectangleRec(rect, GREEN);
//
//		EndDrawing();
//	}
//
//	return 0;
//}

//const int screenWidth = 1280;
//const int screenHeigh = 720;
//
//enum Suit
//{
//	CLUBS, DIAMONDS, HEARTS, SPADES
//};
//
//struct Card
//{
//	Suit suit;
//	int value; // 1 - 13
//	bool isFaceDown; // check Unknow card
//	std::string textureKey;
//};
//
//struct Player
//{
//	std::vector<Card> hand;
//	int life = 3; // 3 life, can change it
//};
//
//Player user;
//Player computer;
//
//std::vector<Card> deck;
//std::map<std::string, Texture2D> cardTextures;
//
//void LoadCardTextures()
//{
//	std::string suits[] = { "clubs", "diamonds", "hearts", "spades" };
//
//	for (const std::string& suit : suits)
//	{
//		for (int value = 1; value <= 13; ++value)
//		{
//			std::string cardName = "card_" + suit + "_" + std::to_string(value);
//			std::string filename = "cards/" + cardName + ".png";
//			Texture2D texture = LoadTexture(filename.c_str());
//			cardTextures[cardName] = texture;
//		}
//	}
//	cardTextures["card_back"] = LoadTexture("cards/card_back.png");
//}
//
//void DrawPlayerHand()
//{
//	for (size_t i = 0; i < user.hand.size(); ++i)
//	{
//		Card& card = user.hand[i];
//		Texture2D texture = cardTextures[card.textureKey];
//		Vector2 position = { 100.0f + (i * 120.0f), screenHeigh - 280.0f };
//		DrawTexture(texture, position.x, position.y, WHITE);
//	}
//}
//
//void DrawComputerHand()
//{
//	for (size_t i = 0; i < computer.hand.size(); ++i)
//	{
//		Card& card = computer.hand[i];
//		Texture2D texture;
//		if (card.isFaceDown)
//		{
//			texture = cardTextures["card_back"];
//		}
//		else
//		{
//			texture = cardTextures[card.textureKey];
//		}
//		Vector2 position = { 100.0f + (i * 120.0f), 70.0f };
//		DrawTexture(texture, position.x, position.y, WHITE);
//	}
//}
//
//void UnloadCardTextures()
//{
//	for (auto& pair : cardTextures)
//	{
//		UnloadTexture(pair.second);
//	}
//	cardTextures.clear();
//}
//
//void InitializeDeck()
//{
//	std::string suits[] = { "clubs", "diamonds", "hearts", "spades" };
//
//	for (int i = CLUBS; i <= SPADES; i++)
//	{
//		for (int v = 1; v <= 13; v++)
//		{
//			Card card;
//			card.suit = static_cast<Suit>(i);
//			card.value = v <= 10 ? v : 10; // card J Q K as 10
//			card.isFaceDown = false;
//			card.textureKey = "card_" + suits[i] + "_" + std::to_string(v);
//			deck.push_back(card);
//		}
//	}
//}
//
//void ShuffleDeck()
//{
//	std::random_device rd;
//	std::default_random_engine rng(rd());
//	std::shuffle(deck.begin(), deck.end(), rng);
//}
//
//bool isUserTurn;
//
//void DealInitialCards()
//{
//	isUserTurn = GetRandomValue(0, 1); // decide who first
//
//	if (isUserTurn)
//	{
//		user.hand.push_back(deck.back());
//		deck.pop_back();
//	}
//	else
//	{
//		Card firstCard = deck.back();
//		firstCard.isFaceDown = true; // Unknown Card
//		computer.hand.push_back(firstCard);
//		deck.pop_back();
//	}
//
//	// Second Card
//	user.hand.push_back(deck.back());
//	deck.pop_back();
//
//	computer.hand.push_back(deck.back());
//	deck.pop_back();
//}
//
//int CalculatePoints(const std::vector<Card>& hand)
//{
//	int total = 0;
//	int aceCount = 0;
//	for (const Card& card : hand)
//	{
//		total += card.value;
//		if (card.value == 1)
//		{
//			aceCount++;
//		}
//	}
//	while (aceCount > 0 && total <= 11) // check A as 1 or 11
//	{
//		total += 10;
//		aceCount--;
//	}
//	return total;
//}
//
//void ComputerTurn()
//{
//	if (CalculatePoints(computer.hand) < 17)
//	{
//		computer.hand.push_back(deck.back());
//		deck.pop_back();
//	}
//}
//
//void ComparePoints()
//{
//	computer.hand[0].isFaceDown = false;
//
//	std::string resultMessage;
//
//	while (CalculatePoints(computer.hand) < 17)
//	{
//		computer.hand.push_back(deck.back());
//		deck.pop_back();
//		if (CalculatePoints(computer.hand) > 21)
//		{
//			computer.life--;
//			return;
//		}
//	}
//
//	if (CalculatePoints(user.hand) > CalculatePoints(computer.hand))
//	{
//		computer.life--;
//		return;
//	}
//	else if (CalculatePoints(user.hand) == CalculatePoints(computer.hand))
//	{
//		return;
//	}
//	else
//	{
//		user.life--;
//		return;
//	}
//}
//
//Rectangle addButton = { screenWidth / 2 - 150, screenHeigh / 2 - 50, 110, 60 };
//Rectangle callButton = { screenWidth / 2 + 20, screenHeigh / 2 - 50, 110, 60 };
//
//void DrawGame()
//{
//	BeginDrawing();
//	ClearBackground(RAYWHITE);
//
//	DrawComputerHand();
//	DrawPlayerHand();
//
//	//for (size_t i = 0; i < user.hand.size(); i++)
//	//{
//	//	DrawRectangle(100 + (i * 200), screenHeigh - 250, 100, 150, BLUE);
//	//}
//
//	//for (size_t i = 0; i < computer.hand.size(); i++)
//	//{
//	//	Color cardColor = computer.hand[i].isFaceDown ? GRAY : RED;
//	//	DrawRectangle(100 + (i * 200), 100, 100, 150, cardColor);
//	//}
//
//	DrawRectangleRec(addButton, ORANGE);
//	DrawRectangleRec(callButton, ORANGE);
//	DrawText("ADD", addButton.x + 33, addButton.y + 20, 23, BLACK);
//	DrawText("CALL", callButton.x + 30, callButton.y + 20, 23, BLACK);
//
//	int userPoints = CalculatePoints(user.hand);
//	int computerPoints = CalculatePoints(computer.hand);
//
//	DrawText(TextFormat("%d", userPoints), screenWidth - 150, screenHeigh - 170, 40, BLACK);
//	if (isUserTurn)
//	{
//		DrawText(TextFormat("%d", computerPoints),
//			screenWidth - 150, 150, 40, BLACK);
//	}
//	else if (computer.hand[0].isFaceDown)
//	{
//		DrawText(TextFormat("X + %d", computerPoints - computer.hand[0].value),
//			screenWidth - 200, 150, 40, BLACK);
//	}
//	else
//	{
//		DrawText(TextFormat("%d + %d", computer.hand[0].value,
//			computerPoints - computer.hand[0].value),
//			screenWidth - 200, 150, 40, BLACK);
//	}
//	DrawText(TextFormat("Your life: %d", user.life), screenWidth / 2 - 100,
//		screenHeigh - 50, 30, BLACK);
//	DrawText(TextFormat("Computer life: %d", computer.life), screenWidth / 2 - 140, 20, 30, BLACK);
//
//	EndDrawing();
//}
//
//void RestGame()
//{
//	user.hand.clear();
//	computer.hand.clear();
//
//	deck.clear();
//	InitializeDeck();
//	ShuffleDeck();
//
//	DealInitialCards();
//}
//
//int main()
//{
//	//Memory memory;
//	//memory.Main();
//	InitWindow(screenWidth, screenHeigh, "Blackjack");
//	SetTargetFPS(60);
//
//	LoadCardTextures();
//	InitializeDeck();
//	ShuffleDeck();
//
//	enum GameState
//	{
//		DEAL, PLAYER_TURN, RESULT, GAME_OVER
//	};
//	GameState gameState = DEAL;
//	std::string resultMessage = "";
//	std::string finalMessage_player = "";
//	std::string finalMessage_computer = "";
//
//	while (!WindowShouldClose())
//	{
//		switch (gameState)
//		{
//		case DEAL:
//			DealInitialCards();
//			gameState = PLAYER_TURN;
//			break;
//		case PLAYER_TURN:
//			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
//			{
//				Vector2 mousePoint = GetMousePosition();
//				if (CheckCollisionPointRec(mousePoint, addButton))
//				{
//					user.hand.push_back(deck.back());
//					deck.pop_back();
//					if (CalculatePoints(user.hand) > 21)
//					{
//						user.life--;
//						gameState = RESULT;
//					}
//					ComputerTurn();
//				}
//				else if (CheckCollisionPointRec(mousePoint, callButton))
//				{
//					ComparePoints();
//					gameState = RESULT;
//				}
//			}
//			break;
//		case RESULT:
//			if (CalculatePoints(user.hand) > 21)
//			{
//				resultMessage = "YOUR CARD BUST! YOU LOSE THIS TURN!";
//			}
//			else if (CalculatePoints(computer.hand) > 21)
//			{
//				resultMessage = "COMPUTER CARD BUST! YOU WIN!";
//			}
//			else if (CalculatePoints(user.hand) > CalculatePoints(computer.hand))
//			{
//				resultMessage = "You win this turn!";
//			}
//			else if (CalculatePoints(user.hand) == CalculatePoints(computer.hand))
//			{
//				resultMessage = "Same! No one lose.";
//			}
//			else
//			{
//				resultMessage = "You lose this turn!";
//			}
//			DrawText(resultMessage.c_str(),
//				screenWidth / 2 - MeasureText(resultMessage.c_str(), 30) / 2,
//				screenHeigh / 2 + 20, 30, BLACK);
//			DrawText("Pressed Space to Continue.",
//				screenWidth / 2 - MeasureText("Pressed Space to Continue.", 30) / 2 + 60,
//				screenHeigh / 2 + 50, 20, GRAY);
//			if (IsKeyPressed(KEY_SPACE))
//			{
//				if (user.life == 0 || computer.life == 0)
//				{
//					gameState = GAME_OVER;
//				}
//				else
//				{
//					RestGame();
//					gameState = PLAYER_TURN;
//					break;
//				}
//			}
//		case GAME_OVER:
//			if (user.life == 0)
//			{
//				finalMessage_player = "GAME OVER!";
//			}
//			else if (computer.life == 0)
//			{
//				finalMessage_computer = "YOU WIN THE GAME!";
//			}
//			DrawText(finalMessage_player.c_str(), 
//				screenWidth / 2 - MeasureText(finalMessage_player.c_str(), 40) / 2 - 10,
//				screenHeigh / 2 - 100, 40, RED);
//			DrawText(finalMessage_computer.c_str(),
//				screenWidth / 2 - MeasureText(finalMessage_computer.c_str(), 40) / 2 - 10,
//				screenHeigh / 2 - 100, 40, GREEN);
//			break;
//		default:
//			break;
//		}
//		DrawGame();
//	}
//
//	UnloadCardTextures();
//	CloseWindow();
//	return 0;
//}

//int main()
//{
//	Particle particle;
//	particle.Main();
//
//	return 0;
//}

//int main()
//{
//	//define
//	const int screenWidth = 800;
//	const int screenHeight = 800;
//
//	InitWindow(screenWidth, screenHeight, "Epitrochoid Drawing");
//	SetTargetFPS(60);
//
//	float R = 150.0f; // Big circle radius
//	float r = 90.0f; // small circle radius
//	float d = 90.0f; // points which draw line
//
//	float theta = 0.0f;
//	const float thetaIncrement = 0.02f;
//
//	std::vector<Vector2> points;
//
//	//bool isDragging = false;
//	//Vector2 smallCirclePos = { screenWidth / 2 + (R + r), screenHeight / 2 };
//
//	while (!WindowShouldClose())
//	{
//		//Vector2 mousePos = GetMousePosition();
//
//		//if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
//		//{
//		//	if (CheckCollisionPointCircle(mousePos, smallCirclePos, r))
//		//	{
//		//		isDragging = true;
//		//	}
//		//}
//		//else
//		//{
//		//	isDragging = false;
//		//}
//
//		float wheel = GetMouseWheelMove();
//		if (wheel != 0.0f)
//		{
//			r += wheel * 5.0f;
//			if (r < 1.0f)
//			{
//				r = 1.0f;
//			}
//			if (r > R)
//			{
//				r = R;
//			}
//
//			points.clear();
//			theta = 0.0f;
//		}
//
//		if (IsKeyDown(KEY_UP))
//		{
//			d += 1.0f;
//			if (d > (R + r))
//			{
//				d = R + r;
//				points.clear();
//				theta = 0.0f;
//			}
//		}
//		if (IsKeyDown(KEY_DOWN))
//		{
//			d -= 1.0f;
//			if (d < 0.0f)
//			{
//				d = 0.0f;
//				points.clear();
//				theta = 0.0f;
//			}
//		}
//
//		theta += thetaIncrement;
//
//		//if (isDragging)
//		//{// calcuate position // CORE PART!
//		//	Vector2 center = { screenWidth / 2, screenHeight / 2 }; // center of big
//		//	Vector2 direction = Vector2Subtract(mousePos, center);
//		//	direction = Vector2Normalize(direction);
//		//	smallCirclePos = Vector2Add(center, Vector2Scale(direction, R + r));
//
//		//	theta = atan2(direction.y, direction.x);
//		//	if (theta < 0)
//		//	{
//		//		theta += 2 * PI;
//		//	}
//		//}
//
//		float x = (R + r) * cos(theta) - d * cos(((R + r) / r) * theta);
//		float y = (R + r) * sin(theta) - d * sin(((R + r) / r) * theta);
//		points.push_back({ screenWidth / 2 + x, screenHeight / 2 + y });
//
//		const size_t maxPoints = 2000;
//		if (points.size() > maxPoints)
//		{
//			points.erase(points.begin(), points.begin() + (points.size() - maxPoints));
//		}
//
//		//points.clear(); // points postion
//		//for (float t = 0.0f; t <= theta; t += 0.01f)
//		//{
//		//	float x = (R + r) * cos(t) - d * cos(((R + r) / r) * t);
//		//	float y = (R + r) * sin(t) - d * sin(((R + r) / r) * t);
//		//	points.push_back({ screenWidth / 2 + x, screenHeight / 2 + y });
//		//}
//
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//
//		DrawCircleLines(screenWidth / 2, screenHeight / 2, R, GRAY); // Big circle
//		//DrawCircleLines((int)smallCirclePos.x, (int)smallCirclePos.y, r, LIGHTGRAY); // small circle
//
//		//for (size_t i = 0; i < points.size() - 1; i++)
//		//{// draw Epitrochoid
//		//	DrawLineV(points[i], points[i + 1], BLUE);
//		//}
//
//		if (points.size() >= 2)
//		{
//			for (size_t i = 0; i < points.size() - 1; i++)
//			{
//				DrawLineV(points[i], points[i + 1], BLUE);
//			}
//		}
//
//		if (!points.empty())
//		{
//			DrawCircleV(points.back(), 3, RED);
//		}
//
//		DrawText(TextFormat("R = %.2f, r = %.2f, d = %.2f", R, r, d), 10, 10, 20, BLACK);
//
//		EndDrawing();
//	}
//
//	CloseWindow();
//	return 0;
//}

//int main()
//{
//	WallBreaker wallBreaker;
//	wallBreaker.Main();
//
//	return 0;
//}

//int main()
//{
//	Snake snake;
//	snake.Main();
//
//	return 0;
//}

//int main()
//{
//	PathFinding path;
//	path.Main();
//
//	return 0;
//}

////constant value
//const int screenWidth = 1400;
//const int screenHeight = 700;
//
//const int gridSize = 10; // 10x10
//const int cellSize = 50; // pixel for one cell
//const int gridMargin = 90; // distance away border
//
//const int playerGridX = gridMargin;
//const int playerGridY = gridMargin;
//
//const int computerGridX = screenWidth - gridMargin - gridSize * cellSize;
//const int computerGridY = gridMargin;
//
//std::vector<int> _shipSizes = { 5, 4, 3, 3, 2 };
//
////game status
//bool placingShips = true;
//int currentShipIndex = 0;
//bool isHorizontal = true; // ship direction
//
//bool computerShipsPlaced = false;
//
//bool playerTurn = true;
//bool gameOver = false;
//
//struct Ship
//{
//	int size;
//	Vector2 position; // initial position
//	bool horizontal; // ship direction
//	std::vector<bool> hits;
//	bool sunk;
//};
//std::vector<Ship> playerShips;
//std::vector<Ship> computerShips;
//
//enum CellState
//{
//	EMPTY, SHIP, MISS, HIT
//};
//
//CellState playerGrid[gridSize][gridSize];
//CellState computerGrid[gridSize][gridSize];
//
//void DrawGrid(int startX, int startY)
//{
//	for (int i = 0; i <= gridSize; i++)
//	{
//		DrawLine(startX, startY + i * cellSize, startX + gridSize * cellSize, startY + i * cellSize,
//			GRAY); // vertical line
//		DrawLine(startX + i * cellSize, startY , startX + i * cellSize, startY + gridSize * cellSize,
//			GRAY); // horizontal line
//	}
//}
//
//void InitializeGrids()
//{
//	//player grid
//	for (int x = 0; x < gridSize; x++)
//	{
//		for (int y = 0; y < gridSize; y++)
//		{
//			playerGrid[x][y] = EMPTY;
//		}
//	}
//
//	//computer grid
//	for (int x = 0; x < gridSize; x++)
//	{
//		for (int y = 0; y < gridSize; y++)
//		{
//			computerGrid[x][y] = EMPTY;
//		}
//	}
//}
//
//bool CanPlaceShip(const std::vector<Ship>& ships, int x, int y, int size, bool horizontal)
//{
//	if (horizontal && x + size > gridSize)
//	{
//		return false;
//	}
//	if (!horizontal && y + size > gridSize)
//	{
//		return false;
//	}
//
//	//check exist ship
//	for (const Ship& ship : ships)
//	{
//		for (int i = 0; i < ship.size; i++)
//		{
//			int shipX = ship.position.x + (ship.horizontal ? i : 0);
//			int shipY = ship.position.y + (ship.horizontal ? 0 : i);
//
//			for (int j = 0; j < size; j++)
//			{
//				int newX = x + (horizontal ? j : 0);
//				int newY = y + (horizontal ? 0 : j);
//
//				if (shipX == newX && shipY == newY)
//				{
//					return false;
//				}
//			}
//		}
//	}
//
//	return true;
//}
//
//void PlaceComputerShips()
//{
//	int shipIndex = 0;
//
//	while (shipIndex < _shipSizes.size())
//	{
//		bool horizontal = GetRandomValue(0, 1) == 1;
//		int x = GetRandomValue(0, gridSize - 1);
//		int y = GetRandomValue(0, gridSize - 1);
//
//		if (CanPlaceShip(computerShips, x, y, _shipSizes[shipIndex], horizontal))
//		{
//			Ship newShip;
//			newShip.size = _shipSizes[shipIndex];
//			newShip.position = { (float)x, (float)y };
//			newShip.horizontal = horizontal;
//			newShip.hits = std::vector<bool>(newShip.size, false);
//			newShip.sunk = false;
//
//			computerShips.push_back(newShip);
//			shipIndex++;
//		}
//	}
//}
//
//void PlaceShipsOnGrid()
//{
//	// player
//	for (const Ship& ship : playerShips)
//	{
//		for (int i = 0; i < ship.size; i++)
//		{
//			int x = ship.position.x + (ship.horizontal ? i : 0);
//			int y = ship.position.y + (ship.horizontal ? 0 : i);
//			playerGrid[x][y] = SHIP;
//		}
//	}
//
//	// computer
//	for (const Ship& ship : computerShips)
//	{
//		for (int i = 0; i < ship.size; i++)
//		{
//			int x = ship.position.x + (ship.horizontal ? i : 0);
//			int y = ship.position.y + (ship.horizontal ? 0 : i);
//			computerGrid[x][y] = SHIP;
//		}
//	}
//}
//
//void UpdateGame()
//{
//	if (placingShips)
//	{
//		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
//		{
//			isHorizontal = !isHorizontal;
//		}
//
//		Vector2 mousePos = GetMousePosition();
//		int gridX = (mousePos.x - playerGridX) / cellSize;
//		int gridY = (mousePos.y - playerGridY) / cellSize;
//
//		if (gridX >= 0 && gridX < gridSize && gridY >= 0 && gridY < gridSize)
//		{
//			int shipSize = _shipSizes[currentShipIndex];
//
//			Color previewColor = DARKGREEN;
//
//			if (!CanPlaceShip(playerShips, gridX, gridY, shipSize, isHorizontal))
//			{
//				previewColor = RED;
//			}
//
//			for (int i = 0; i < shipSize; i++)
//			{
//				int x = gridX + (isHorizontal ? i : 0);
//				int y = gridY + (isHorizontal ? 0 : i);
//
//				if (x < gridSize && y < gridSize)
//				{
//					DrawRectangle(playerGridX + x * cellSize, playerGridY + y * cellSize, cellSize,
//						cellSize, previewColor);
//				}
//			}
//
//			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
//			{
//				if (CanPlaceShip(playerShips, gridX, gridY, shipSize, isHorizontal))
//				{
//					Ship newShip;
//					newShip.size = shipSize;
//					newShip.position = { (float)gridX, (float)gridY };
//					newShip.horizontal = isHorizontal;
//					newShip.hits = std::vector<bool>(shipSize, false);
//					newShip.sunk = false;
//
//					playerShips.push_back(newShip);
//					currentShipIndex++;
//
//					if (currentShipIndex >= _shipSizes.size())
//					{
//						placingShips = false;
//					}
//				}
//			}
//		}
//	}
//
//	for (const Ship& ship : playerShips)
//	{
//		for (int i = 0; i < ship.size; i++)
//		{
//			int x = ship.position.x + (ship.horizontal ? i : 0);
//			int y = ship.position.y + (ship.horizontal ? 0 : i);
//
//			DrawRectangle(playerGridX + x * cellSize, playerGridY + y * cellSize, cellSize, cellSize,
//				BLUE);
//		}
//	}
//
//	if (!placingShips && !computerShipsPlaced)
//	{
//		PlaceComputerShips();
//		PlaceShipsOnGrid();
//		computerShipsPlaced = true;
//	}
//}
//
//void UpdateShipState(std::vector<Ship>& ships, Vector2 hitPos)
//{
//	for (Ship& ship : ships)
//	{
//		for (int i = 0; i < ship.size; i++)
//		{
//			int x = ship.position.x + (ship.horizontal ? i : 0);
//			int y = ship.position.y + (ship.horizontal ? 0 : i);
//			if (x == hitPos.x && y == hitPos.y)
//			{
//				ship.hits[i] = true;
//				bool sunk = true;
//				for (bool partHit : ship.hits)
//				{
//					if (!partHit)
//					{
//						sunk = false;
//						break;
//					}
//				}
//				ship.sunk = sunk;
//				if (sunk)
//				{
//					// maybe VFX stuff
//				}
//				break;
//			}
//		}
//	}
//}
//
//bool AreAllShipsSunk(const std::vector<Ship>& ships)
//{
//	for (const Ship& ship : ships)
//	{
//		if (!ship.sunk)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//void HandlePlayerAttack()
//{
//	if (!placingShips && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//	{
//		Vector2 mousePos = GetMousePosition();
//		int gridX = (mousePos.x - computerGridX) / cellSize;
//		int gridY = (mousePos.y - computerGridY) / cellSize;
//
//		// check hits
//		if (gridX >= 0 && gridY < gridSize && gridY >= 0 && gridY < gridSize)
//		{
//			if (computerGrid[gridX][gridY] == EMPTY || computerGrid[gridX][gridY] == SHIP)
//			{
//				if (computerGrid[gridX][gridY] == SHIP)
//				{
//					computerGrid[gridX][gridY] = HIT;
//					UpdateShipState(computerShips, { (float)gridX, (float)gridY });
//					if (AreAllShipsSunk(computerShips))
//					{
//						gameOver = true;
//					}
//				}
//				else
//				{
//					computerGrid[gridX][gridY] = MISS;
//				}
//				playerTurn = false;
//			}
//		}
//	}
//}
//
//void ComputerAttack()
//{
//	int x, y;
//	do
//	{
//		x = GetRandomValue(0, gridSize - 1);
//		y = GetRandomValue(0, gridSize - 1);
//	}
//	while (playerGrid[x][y] == MISS || playerGrid[x][y] == HIT);
//
//	if (playerGrid[x][y] == SHIP)
//	{
//		playerGrid[x][y] = HIT;
//		UpdateShipState(playerShips, { (float)x, (float)y });
//		if (AreAllShipsSunk(playerShips))
//		{
//			gameOver = true;
//		}
//	}
//	else
//	{
//		playerGrid[x][y] = MISS;
//	}
//	playerTurn = true;
//}
//
//void DrawAttacks()
//{
//	// player side
//	for (int x = 0; x < gridSize; x++)
//	{
//		for (int y = 0; y < gridSize; y++)
//		{
//			int drawX = playerGridX + x * cellSize;
//			int drawY = playerGridY + y * cellSize;
//			if (playerGrid[x][y] == HIT)
//			{
//				DrawCircle(drawX + cellSize / 2, drawY + cellSize / 2, cellSize / 4, DARKGREEN);
//			}
//			else if (playerGrid[x][y] == MISS)
//			{
//				DrawLine(drawX, drawY, drawX + cellSize, drawY + cellSize, RED);
//				DrawLine(drawX + cellSize, drawY, drawX, drawY + cellSize, RED);
//			}
//		}
//	}
//
//	// computer side
//	for (int x = 0; x < gridSize; x++)
//	{
//		for (int y = 0; y < gridSize; y++)
//		{
//			int drawX = computerGridX + x * cellSize;
//			int drawY = computerGridY + y * cellSize;
//			if (computerGrid[x][y] == HIT)
//			{
//				DrawCircle(drawX + cellSize / 2, drawY + cellSize / 2, cellSize / 4, DARKGREEN);
//			}
//			else if (computerGrid[x][y] == MISS)
//			{
//				DrawLine(drawX, drawY, drawX + cellSize, drawY + cellSize, RED);
//				DrawLine(drawX + cellSize, drawY, drawX, drawY + cellSize, RED);
//			}
//		}
//	}
//}
//
//void ShowGameOverMessage()
//{
//	const char* message = AreAllShipsSunk(computerShips) ? "YOU WIN!" : "YOU LOSS!";
//	int fontSize = 40;
//	int textWidth = MeasureText(message, fontSize);
//	DrawText(message, (screenWidth - textWidth) / 2, screenHeight / 2 - fontSize / 2, fontSize, RED);
//}
//
//int main()
//{
//	InitWindow(screenWidth, screenHeight, "BattleShip");
//
//	SetTargetFPS(60);
//
//	while (!WindowShouldClose())
//	{
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//
//		DrawGrid(playerGridX, playerGridY);
//		DrawGrid(computerGridX, computerGridY);
//
//		UpdateGame();
//		//for (const Ship& ship : computerShips)
//		//{
//		//	for (int i = 0; i < ship.size; i++)
//		//	{
//		//		int x = ship.position.x + (ship.horizontal ? i : 0);
//		//		int y = ship.position.y + (ship.horizontal ? 0 : i);
//
//		//		DrawRectangle(computerGridX + x * cellSize, computerGridY + y * cellSize, cellSize,
//		//			cellSize,
//		//			BLUE);
//		//	}
//		//}
//
//		DrawAttacks();
//		if (!gameOver)
//		{
//			if (playerTurn)
//			{
//				HandlePlayerAttack();
//			}
//			else
//			{
//				ComputerAttack();
//			}
//		}
//		else
//		{
//			ShowGameOverMessage();
//		}
//
//		EndDrawing();
//	}
//
//	CloseWindow();
//
//	return 0;
//}

int main()
{
	InitWindow(Constants::screenWidth, Constants::screenHeight, "BattleShip");

	Game game;
	game.Initialize();

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		game.Update();
		game.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}