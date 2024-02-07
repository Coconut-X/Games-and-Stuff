#include "raylib.h"
#include<string>
#include<math.h>
#include<iostream>

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

    SetTargetFPS(60);
    InitWindow(screenHeight, screenHeight, "Bouncing Ball");
    float posX = screenWidth / 2.0f;
    float posY = initialHeight;
    float velocityY = 0;
    int bounce = 0;
    int totalBounces=log_base(1/initialHeight,coefficientOfRestitution);
    Color color = RED;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        std::string text = std::to_string(bounce);
        SetTargetFPS(60);

        DrawText(text.c_str(), 20, 20, 50, GREEN);
      
        velocityY += 0.5f;
        posY += velocityY;

        color = RED;
        if ((posY + ballRadius +2 >= screenHeight))
        {
            ClearBackground(ORANGE);
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

    CloseWindow();
    return 0;
}
