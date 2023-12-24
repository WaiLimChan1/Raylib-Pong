#include "raylib.h"
#include <string>
using namespace std;

struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;
	float speedUp;

	void Draw()
	{
		DrawCircle(x, y, radius, WHITE);
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2.0f, y - height / 2.0f, width, height };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};

Ball ball;
Paddle leftPaddle;
Paddle rightPaddle;
const char* winnerText;

void SetUp()
{
	InitWindow(1000, 600, "Pong Raylib");
	SetWindowState(FLAG_VSYNC_HINT);
	winnerText = "Undetermined";

	//ball variables initialization
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;
	ball.speedUp = 1.1f;

	//leftPaddle variables initialization
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2.0f;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	//rightPaddle variables initialization
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2.0f;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	if (winnerText == "Undetermined")
	{
		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();
		DrawFPS(10, 10);
	}
	else
	{
		int textWidth = MeasureText(winnerText, 60);
		DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		if (IsKeyPressed(KEY_SPACE))
		{
			winnerText = "Undetermined";

			//ball variables initialization
			ball.x = GetScreenWidth() / 2.0f;
			ball.y = GetScreenHeight() / 2.0f;
			ball.radius = 5;
			ball.speedX = 300;
			ball.speedY = 300;
			ball.speedUp = 1.01f;

			//leftPaddle variables initialization
			leftPaddle.x = 50;
			leftPaddle.y = GetScreenHeight() / 2.0f;
			leftPaddle.width = 10;
			leftPaddle.height = 100;
			leftPaddle.speed = 500;

			//rightPaddle variables initialization
			rightPaddle.x = GetScreenWidth() - 50;
			rightPaddle.y = GetScreenHeight() / 2.0f;
			rightPaddle.width = 10;
			rightPaddle.height = 100;
			rightPaddle.speed = 500;
		}
	}
	EndDrawing();
}

void Input()
{
	if (IsKeyDown(KEY_W))
	{
		leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		if (leftPaddle.y < leftPaddle.height / 2)
			leftPaddle.y = leftPaddle.height / 2;
	}
	if (IsKeyDown(KEY_S))
	{
		leftPaddle.y += leftPaddle.speed * GetFrameTime();
		if (leftPaddle.y > GetScreenHeight() - leftPaddle.height / 2)
			leftPaddle.y = GetScreenHeight() - leftPaddle.height / 2;
	}
	if (IsKeyDown(KEY_UP))
	{
		rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		if (rightPaddle.y < rightPaddle.height / 2)
			rightPaddle.y = rightPaddle.height / 2;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		rightPaddle.y += rightPaddle.speed * GetFrameTime();
		if (rightPaddle.y > GetScreenHeight() - rightPaddle.height / 2)
			rightPaddle.y = GetScreenHeight() - rightPaddle.height / 2;
	}

	ball.x += ball.speedX * GetFrameTime();
	ball.y += ball.speedY * GetFrameTime();
}

void leftHacks()
{
	//if (ball.x < GetScreenWidth() / 2)
	leftPaddle.y = ball.y;
}

void rightHacks()
{
	//if (ball.x > GetScreenWidth() / 2)
	rightPaddle.y = ball.y;
}

void Logic()
{
	if (ball.y > GetScreenHeight())
	{
		ball.y = GetScreenHeight();
		ball.speedY *= -1;
	}
	else if (ball.y < 0)
	{
		ball.y = 0;
		ball.speedY *= -1;
	}

	if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
	{
		if (ball.speedX < 0)
		{
			ball.speedX *= -1 * ball.speedUp;
			if (ball.y - leftPaddle.y == 0)
				ball.speedY *= -1 * ball.speedUp;
			else
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
		}
	}

	if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
	{
		if (ball.speedX > 0)
		{
			ball.speedX *= -1 * ball.speedUp;
			if (ball.y - rightPaddle.y == 0)
				ball.speedY *= -1 * ball.speedUp;
			else
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -1.0f * ball.speedX;
		}
	}

	if (ball.x > GetScreenWidth())
	{
		winnerText = "Left Player Wins!";
	}
	if (ball.x < 0)
	{
		winnerText = "Right Player Wins!";
	}
}

int main()
{
	SetUp();

	while (!WindowShouldClose())
	{
		Draw();
		Input();
		//leftHacks();
		rightHacks();
		Logic();
	}

	CloseWindow();
	return 0;
}