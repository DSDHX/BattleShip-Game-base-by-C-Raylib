//#include "Particle.h"
//#include <time.h>
//#include "Circle.h"

//void Particle::Main()
//{
//	Start();
//
//	InitWindow(800, 800, "Particle");
//	SetTargetFPS(60);
//
//	while (!WindowShouldClose())
//	{
//		BeginDrawing();
//
//		ClearBackground(BLACK);
//
//		Update();
//		Draw();
//
//		EndDrawing();
//	}
//	CloseWindow();
//}

//void Particle::Start()
//{
//
//}
//
//void Particle::Update()
//{
	//if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	//{
	//	Vector2 mousePos = GetMousePosition();

	//	int rate = rand() % 8 + 8;
	//	for (int i = 0; i < rate; i++)
	//	{
	//		float angle = rand() % 360;
	//		float radius = rand() % 25;

	//		Color color = colors[rand() & colors.size()];

	//		Circle circle = Circle(mousePos, angle, radius, color);;
	//		circles.push_back(circle);
	//	}
	//}

	//for (int i = 0; i < circles.size(); i++)
	//{
	//	circles[i].Update();
	//}
//}

//void Particle::Draw()
//{
//	for (int i = 0; i < circles.size(); i++)
//	{
//		circles[i].Draw();
//	}
//}