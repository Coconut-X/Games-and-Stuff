#include"raylib.h"
#include<vector>

#define MAX_BULLETS 35
using namespace std;

const int screenWidth = 500;
const int screenHeight = 900;

class aliens
{
public:
	Vector2 position;
	float speed;
	Color color;
};

int main()
{
	InitWindow(screenWidth, screenHeight, "Bullet Attack");
	SetTargetFPS(250);
	InitAudioDevice();
	Sound play= LoadSound("chiptune-grooving-142242.mp3");
	PlaySound(play);
	START:
					
	aliens *bullet=new aliens[MAX_BULLETS];	
	
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullet[i].position.x = GetRandomValue(0, screenWidth);
		bullet[i].position.y = GetRandomValue(-screenHeight, 0);	// negative makes it move at top again
		bullet[i].speed = (float)GetRandomValue(10, 20) / 10.0f;
		bullet[i].color = Color{ 0, 100, 255, 255 };

	}
	
	int bulletLength = 12;

	int recX = 225, recY = screenHeight - 10;
	bool lose = false, win = false;

	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLACK);

		if (!IsSoundPlaying(play)) PlaySound(play);
		
		DrawText("R E A C H   H E R E   T O   W I N", 85, 250, 20, GREEN);
		DrawLine(0, 270, screenWidth, 270, GREEN);
		DrawRectangle(recX, recY, 50, 10, RED);
		
		if (!lose && !win)
		{

///																	INPUTS
			if (IsKeyDown(KEY_RIGHT))		recX++;

			else if (IsKeyDown(KEY_LEFT))	recX--;

			else if (IsKeyDown(KEY_UP))		recY--;

			else if (IsKeyDown(KEY_DOWN))	recY++;

			if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN))		recX++, recY++;

			else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP))		recX++, recY--;

			else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN))	recX--, recY++;

			else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP))		recX--, recY--;

///																	 BOUNDARIES
			if (recX <= 0) recX+=2;									//left boundary

			else if (recX + 50 >= screenWidth) recX-=2;				//right boundary

			else if (recY+10 >= screenHeight) recY-=2;				//bottom boundary
		}
		

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if(!lose && !win)
				bullet[i].position.y += bullet[i].speed;

			DrawLineV(bullet[i].position, Vector2 { bullet[i].position.x, bullet[i].position.y + bulletLength }, bullet[i].color);

///													REINITIALIZE BULLET POSITION WHEN IT TOUCHES BOTTOM
			if(!lose && !win)
				if (bullet[i].position.y > screenHeight) 
				{
					bullet[i].position.y = GetRandomValue(-screenHeight, 0);
					bullet[i].position.x = GetRandomValue(0, screenWidth);
					bullet[i].speed = (float)GetRandomValue(10, 20) / 10.0f;
				}
///															CHECK COLLISION/ LOSING CONDITION
			if (bullet[i].position.x >= recX && bullet[i].position.x <= recX + 50 && bullet[i].position.y >= recY && bullet[i].position.y <= recY + 10)
			{
				lose = true;
				DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), { 128, 128, 128, 100 });
				DrawText("YOU LOST", 120, 120, 50, RED);
				StopSound(play);
			}

		}

///																	WINNING CONDITION  
		if (recY <= 270 && !lose)
		{
			win = true;
			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), { 128, 128, 128, 100 });
			DrawText("YOU WON", 130, 450, 50, GREEN);
			StopSound(play);
		}

		if (win || lose)
		{
			DrawText("Press Enter to Replay", 80, 50, 30, DARKBLUE);

			if (IsKeyPressed(KEY_ENTER))
				goto START;
		}

		EndDrawing();

	}
	delete[] bullet;
	

	UnloadSound(play);

	CloseWindow();
	return 0;
}