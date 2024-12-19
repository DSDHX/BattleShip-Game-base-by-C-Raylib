#include "WallBreaker.h"
#include <raymath.h>

bool WallBreaker::CheckBallBrickCollision(Ball& ball, Brick& brick,
	Vector2& collisionNormal)
{
	float radius = brick.roundness * fminf(brick.rect.width, brick.rect.height) / 2.0f;

	Rectangle innerRect =
	{
		brick.rect.x + radius,
		brick.rect.y,
		brick.rect.width - 2 * radius,
		brick.rect.height
	};
	Rectangle leftRect =
	{
		brick.rect.x,
		brick.rect.y + radius,
		radius,
		brick.rect.height - 2 * radius
	};
	Rectangle rightRect =
	{
		brick.rect.x + brick.rect.width - radius,
		brick.rect.y + radius,
		radius,
		brick.rect.height - 2 * radius
	};

	if (CheckCollisionCircleRec(ball.position, ball.radius, innerRect))
	{
		if (ball.position.y < innerRect.y)
		{
			collisionNormal = { 0, -1 }; // UP
		}
		else if (ball.position.y > innerRect.y + innerRect.height)
		{
			collisionNormal = { 0, 1 }; // DOWN
		}
		else if (ball.position.x < innerRect.x)
		{
			collisionNormal = { -1, 0 }; // LEFT
		}
		else
		{
			collisionNormal = { 1, 0 }; // RIGHT
		}

		return true;
	}

	if (CheckCollisionCircleRec(ball.position, ball.radius, leftRect))
	{
		collisionNormal = { -1, 0 };
		return true;
	}
	if (CheckCollisionCircleRec(ball.position, ball.radius, rightRect))
	{
		collisionNormal = { 1, 0 };
		return true;
	}

	Vector2 cornerCenters[4] =
	{
		{ brick.rect.x + radius, brick.rect.y + radius},
		{ brick.rect.x + brick.rect.width - radius, brick.rect.y + radius},
		{ brick.rect.x + radius, brick.rect.y + brick.rect.height - radius},
		{ brick.rect.x + brick.rect.width - radius, brick.rect.y + brick.rect.height - radius}
	};

	for (int i = 0; i < 4; i++)
	{
		if (CheckCollisionCircles(ball.position, ball.radius, cornerCenters[i], radius))
		{
			collisionNormal = Vector2Normalize(Vector2Subtract(ball.position, cornerCenters[i]));
			return true;
		}
	}

	return false;
}

void WallBreaker::Main()
{
	Start();

	InitWindow(screenWidth, screenHeigh, "Wall Breaker Game");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		Update();
		Draw();

		EndDrawing();
	}
	CloseWindow();
}

void WallBreaker::Start()
{
	bricks.clear();

	brickHeight = screenHeigh * 0.05;
	brickGap = brickHeight * 0.4;

	rowCount = 5;
	colCount = 8;

	float spaceForBriks = screenWidth - (colCount * brickGap + brickGap);
	float brickWdith = spaceForBriks / colCount;
	Vector2 brickSize = { brickWdith, brickHeight };

	for (int row = 0; row < rowCount; row++)
	{
		for (int col = 0; col < colCount; col++)
		{
			float x = brickGap + (brickWdith + brickGap) * col;
			float y = brickGap + (brickHeight + brickGap) * row;

			Rectangle rect = { x, y, brickWdith, brickHeight };

			Brick brick = Brick{ YELLOW, rect, 0.8f, 8 };
			bricks.push_back(brick);
		}
	}

	player.currentLife = MAX_LIVES;
	player.position = { screenWidth / 2, screenHeigh - 100 };
}

void WallBreaker::Update()
{
#pragma region playerContral
	if (IsKeyDown(KEY_LEFT))
	{
		player.position.x -= 10;
	}
	if (player.position.x - player.size.x / 2 < 0)
	{
		player.position.x = player.size.x / 2;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		player.position.x += 10;
	}
	if (player.position.x > screenWidth - player.size.x / 2)
	{
		player.position.x = screenWidth - player.size.x / 2;
	}
#pragma endregion

	if (IsKeyPressed(KEY_SPACE))
	{
		ball.active = true;
		ball.speed = { 0, -5 };
	}
	if (!ball.active)
	{
		ball.position = { player.position.x,
			player.position.y + player.size.y / 2 - ball.radius };
	}
	else
	{
		ball.position.x += ball.speed.x;
		ball.position.y += ball.speed.y;
	}

	if (ball.active)
	{
		ball.position.x += ball.speed.x;
		ball.position.y += ball.speed.y;

		// touch with x-screen
		if ((ball.position.x - ball.radius <= 0 && ball.speed.x < 0) ||
			(ball.position.x + ball.radius >= screenWidth && ball.speed.x > 0))
		{
			ball.speed.x *= -1;
		}
		// touch with top-screen
		if (ball.position.y - ball.radius <= 0 && ball.speed.y < 0)
		{
			ball.speed.y *= -1;
		}
		// touch with bottom
		if (ball.position.y - ball.radius > screenHeigh)
		{
			ball.active = false;
			player.currentLife--;

			if (player.currentLife <= 0)
			{
				Start();

				//DrawText("GAME OVER!", screenWidth / 2 - MeasureText("GAME OVER!", 40) / 2,
				//	screenHeigh / 2 - 20, 40, RED);
				//if (IsKeyPressed(KEY_SPACE))
				//{
				//}
			}
		}
	}

	if (ball.active) // ball hit player
	{
		Rectangle playerRect = { player.position.x - player.size.x / 2,
								 player.position.y + player.size.y / 2,
								 player.size.x,
								 player.size.y };

		if (CheckCollisionCircleRec(ball.position, ball.radius, playerRect)
			&& ball.speed.y > 0)
		{
			float hitPosition = (ball.position.x - player.position.x) /
				(player.size.x / 2);
			ball.speed.x = hitPosition * 5;
			ball.speed.y *= -1;
		}
	}

	// collection
	for (int i = 0; i < bricks.size(); i++)
	{
		Vector2 collisionNormal;
		if (CheckBallBrickCollision(ball, bricks[i], collisionNormal))
		{
			ball.speed = Vector2Subtract(ball.speed, Vector2Scale(collisionNormal,
				2 * Vector2DotProduct(ball.speed, collisionNormal)));

			bricks.erase(bricks.begin() + i);
			break;
		}
	}
	if (bricks.empty())
	{
		DrawText("YOU WIN!", screenWidth / 2 - MeasureText("YOU WIN!", 40) / 2,
			screenHeigh / 2 - 20, 40, GREEN);
		if (IsKeyPressed(KEY_SPACE))
		{
			Start();
		}
	}
}

void WallBreaker::Draw()
{
	player.Draw();
	ball.Draw();

	for (Brick brick : bricks)
	{
		brick.Draw();
	}

	int cellWidth = 30;
	int cellHeight = 15;
	int cellGap = 15;
	int borderGap = 20;

	for (int i = 0; i < MAX_LIVES; i++)
	{
		Color cellColor = DARKGRAY;

		if (i < player.currentLife)
		{
			cellColor = RAYWHITE;
		}

		int x = borderGap + (cellWidth + cellGap) * i;
		int y = screenHeigh - borderGap - cellHeight;
		DrawRectangle(x, y, cellWidth, cellHeight, cellColor);
	}
}