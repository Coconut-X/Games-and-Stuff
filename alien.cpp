#include"raylib.h"
#include<vector>

///																			CONSTANTS
#define MAX_BULLETS 40
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 900

using namespace std;

struct Bullet
{
	Vector2 position;
	float speed;
	Color color;
};

int main()
{
///																	SETTING UP WINDOW AND AUDIO
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bullet Attack");
	SetTargetFPS(250);
	InitAudioDevice();
	Sound play= LoadSound("chiptune-grooving-142242.mp3");
	PlaySound(play);

	START:   /// RESTART LABEL
					
	Bullet *bullet=new Bullet[MAX_BULLETS];							// array of objects(different bullets)	
	
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullet[i].position.x = GetRandomValue(0, SCREEN_WIDTH);
		bullet[i].position.y = GetRandomValue(-SCREEN_HEIGHT, 0);	// negative makes it move at top again
		bullet[i].speed = (float)GetRandomValue(10, 20) / 10.0f;
		bullet[i].color = Color{ 0, 100, 255, 255 };

	}
	
	int bulletLength = 12;
	int recX = 225, recY = SCREEN_HEIGHT - 10;
	bool lose = false, win = false;

	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLACK);

		if (!IsSoundPlaying(play)) PlaySound(play);
		
		DrawText("R E A C H   H E R E   T O   W I N", 85, 250, 20, GREEN);
		DrawLine(0, 270, SCREEN_WIDTH, 270, GREEN);
		DrawRectangle(recX, recY, 50, 10, RED);
		
		if (!lose && !win)
		{

///																			INPUTS
			if (IsKeyDown(KEY_RIGHT))		recX++;

			else if (IsKeyDown(KEY_LEFT))	recX--;

			else if (IsKeyDown(KEY_UP))		recY--;

			else if (IsKeyDown(KEY_DOWN))	recY++;

			if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN))		recX++, recY++;

			else if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP))		recX++, recY--;

			else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN))	recX--, recY++;

			else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP))		recX--, recY--;

///																		 BOUNDARIES
			if (recX <= 0) recX+=2;									//left boundary

			else if (recX + 50 >= SCREEN_WIDTH) recX-=2;			//right boundary

			else if (recY+10 >= SCREEN_HEIGHT) recY-=2;				//bottom boundary
		}
		

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if(!lose && !win)
				bullet[i].position.y += bullet[i].speed;

			DrawLineV(bullet[i].position, Vector2 { bullet[i].position.x, bullet[i].position.y + bulletLength }, bullet[i].color);

///													REINITIALIZE BULLET POSITION WHEN IT TOUCHES BOTTOM
			if(!lose && !win)
				if (bullet[i].position.y > SCREEN_HEIGHT) 
				{
					bullet[i].position.y = GetRandomValue(-SCREEN_HEIGHT, 0);
					bullet[i].position.x = GetRandomValue(0, SCREEN_WIDTH);
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
///																	  REPLAY OPTION
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
