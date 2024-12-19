#include "Snake.h"
#include <time.h>
#include <string>
#include <fstream>
#include <iostream>

Vector2& operator+=(Vector2& a, const Vector2& b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

void Snake::Main()
{
	Start();

    srand(time(NULL));

	InitWindow(screenWidth, screenHeight, "Snake Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		Update();

		BeginDrawing();
		ClearBackground(BLACK);

		Draw();

		EndDrawing();
	}
	CloseWindow();
}

void Snake::Start()
{
    Piece head_1;
    head_1.color = DARKBLUE;
    head_1.position = Vector2{ screenWidth / 2, screenHeight / 2 };
    players.clear();
    players.push_back(head_1);
    gameOver = false;
    frameCount = 0;
    SpawnFood();
}

void Snake::Draw()
{
	for (Piece any : players)
	{
		any.Draw();
	}

    // Draw food
    DrawRectangleV(food.position, Vector2{ TILE_SIZE, TILE_SIZE }, food.color);

	for (int i = 0; i < screenWidth / TILE_SIZE; i++)
	{
		Vector2 startV = { TILE_SIZE * i + borderGap.x / 2, borderGap.y / 2 };
		Vector2 endV = { TILE_SIZE * i + borderGap.x / 2, screenHeight - borderGap.y / 2 };
		DrawLineV(startV, endV, GRAY);
	}

	for (int j = 0; j < screenHeight / TILE_SIZE; j++)
	{
		Vector2 startH = { borderGap.x / 2, TILE_SIZE * j + borderGap.y / 2 };
		Vector2 endH = { screenWidth - borderGap.x / 2, TILE_SIZE * j + borderGap.y / 2 };
		DrawLineV(startH, endH, GRAY);
	}
	if (gameOver) // Display game over message
    {
        const char* gameOverText = "GAME OVER";
        int textWidth = MeasureText(gameOverText, 40);
        DrawText(gameOverText, screenWidth / 2 - textWidth / 2, screenHeight / 2 - 20, 40, RED);
    }

    //if (gameOver)
    //{
    //    const char* gameOverText = "GAME OVER - Press 'R' to Restart";
    //    int textWidth = MeasureText(gameOverText, 40);
    //    DrawText(gameOverText, screenWidth / 2 - textWidth / 2, screenHeight / 2 - 20, 40, RED);
    //}
}

void Snake::Update()
{
    if (gameOver)
    {
        if (IsKeyPressed(KEY_R))
        {
            Start();
        }
        return;
    }

	frameCount += 1;

	if (frameCount % 25 == 0)
	{
        // Move each segment to the position of the previous segment
        for (size_t i = players.size() - 1; i > 0; --i)
        {
            players[i].position = players[i - 1].position;
        }
        // Move the head in the direction of speed
        players[0].position += speed;
	}

	Interaction();
    CheckBorderCollision();
    CheckFoodCollision(); // Call the CheckFoodCollision function to check for food collision
    CheckSelfCollision(); // Call the CheckSelfCollision function to check for self collision
}

void Snake::CheckBorderCollision()
{
    float minX = borderGap.x / 2;
    float maxX = screenWidth - borderGap.x / 2 - TILE_SIZE;
    float minY = borderGap.y / 2;
    float maxY = screenHeight - borderGap.y / 2 - TILE_SIZE;

    if (players[0].position.x < minX || players[0].position.x > maxX ||
        players[0].position.y < minY || players[0].position.y > maxY)
    {
        gameOver = true;
        std::cout << "Game Over: Snake hit the border!" << std::endl;
    }
}

void Snake::SpawnFood()
{
    bool validPosition = false;
    while (!validPosition)
    {
        food.position = Vector2{
            static_cast<float>((rand() % ((screenWidth - static_cast<int>(borderGap.x)) / TILE_SIZE)) * TILE_SIZE + borderGap.x / 2),
            static_cast<float>((rand() % ((screenHeight - static_cast<int>(borderGap.y)) / TILE_SIZE)) * TILE_SIZE + borderGap.y / 2)
        };
        food.color = RED;

        validPosition = true;
        for (const Piece& segment : players)
        {
            if (segment.position.x == food.position.x && segment.position.y == food.position.y)
            {
                validPosition = false;
                break;
            }
        }
    }
}

void Snake::CheckFoodCollision()
{
    if (players[0].position.x == food.position.x && players[0].position.y == food.position.y)
    {
        Piece newPiece;
        Piece tail = players.back();
        newPiece.position = tail.position;
        newPiece.color = DARKBLUE;
        players.push_back(newPiece);

        SpawnFood();
    }
}


void Snake::CheckSelfCollision()
{
    for (int i = 2; i < players.size(); i++)
    {
        if (players[0].position.x == players[i].position.x &&
            players[0].position.y == players[i].position.y)
        {
            gameOver = true;
            std::cout << "Game Over: Snake collided with itself!" << std::endl;
            break;
        }
    }
}

void Snake::Interaction()
{
	if (IsKeyPressed(KEY_RIGHT) && speed.x >= 0)
	{
		speed = { TILE_SIZE, 0 };
        frameCount = 24;
	}
	if (IsKeyPressed(KEY_LEFT) && speed.x <= 0)
	{
		speed = { -TILE_SIZE, 0 };
        frameCount = 24;
	}
	if (IsKeyPressed(KEY_UP) && speed.y <= 0)
	{
		speed = { 0, -TILE_SIZE };
        frameCount = 24;
	}
	if (IsKeyPressed(KEY_DOWN) && speed.y >= 0)
	{
		speed = { 0, TILE_SIZE };
        frameCount = 24;
	}
}