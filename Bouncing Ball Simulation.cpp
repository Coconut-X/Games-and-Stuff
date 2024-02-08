#include "raylib.h"
#include<string>
#include<math.h>


float log_base(float x, float base)
{
    return log(x) / log(base);
}

int main()
{

    const int screenWidth = 800;
    const int screenHeight = 800;
    const int ballRadius = 20;
    const float initialHeight = 100;
    const float coefficientOfRestitution = 0.9f;

    float posX = screenWidth / 2.0f;
    float posY = initialHeight;
    float velocityY = 0;
    int bounce = 0;
    int totalBounces=log_base(1/initialHeight,coefficientOfRestitution);

    SetTargetFPS(60);
    InitWindow(screenHeight, screenHeight, "Bouncing Ball");
    Color color = RED;
    
    InitAudioDevice();
    Wave wave = LoadWave("ballBounce.wav");
    Sound sound = LoadSound("ballBounce.wav");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        color = RED;

        std::string text = std::to_string(bounce);
        DrawText(text.c_str(), 20, 20, 50, GREEN);
        
        velocityY += 0.5f;
        posY += velocityY;

        if ((posY + ballRadius +2 >= screenHeight))
        {
            ClearBackground(ORANGE);
            PlaySound(sound);

            if (bounce <= totalBounces) bounce++;

            posY = screenHeight - ballRadius;
            velocityY *= -coefficientOfRestitution;
            color = GREEN;
        }

        DrawLine(0, screenHeight-1, screenWidth, screenHeight-1, color);
        DrawLine(0, screenHeight, screenWidth, screenHeight, color);

        DrawCircle(posX, posY, ballRadius, DARKPURPLE);
       
        EndDrawing();
    }

    UnloadWave(wave);
    UnloadSound(sound);

    CloseWindow();
    return 0;
}
