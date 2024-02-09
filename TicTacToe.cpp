#include "raylib.h"
#include"tic.h"
#include<vector>
#include<iostream>
#include<string>

using namespace std;
const int screenWidth = 900;
const int screenHeight = 900;
int draw = 0;
int main()
{
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe");
    SetTargetFPS(100);

    InitAudioDevice();                              //SOUND RELATED
    Sound ini = LoadSound("instructions.wav");
    Sound click = LoadSound("click.mp3");
    PlaySound(ini);

    Color back = RED;                               //COLOURS/TEXTURE
    Color ofx = RED;
    Color ofy = BLUE;
    Texture2D image = LoadTexture("tic.png");

    vector<vector<int>> board{                      //BOARD TO STORE VALUES -1=NOTHING, 0=X, 1=O 
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1}
    };

    bool xTurn = true;                              //CONTROL PLAYERS TURNS
    bool xwins = false, ywins = false;
    string x = "x", o = "O";

    int i, j;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (!IsSoundPlaying(ini))                   //LOOP SOUND
        {
            PlaySound(ini);
        }

        Rectangle destRect = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };                           //TEXTURE
        DrawTexturePro(image, { 0, 0, (float)image.width, (float)image.height }, destRect, { 0, 0 }, 0.0f, back);

       
        for (int row = 0; row < 3; row++)               //DISPLAY BOARD
        {
            for (int col = 0; col < 3; col++) 
            {
                if (board[row][col] == 0) 
                    DrawText(x.c_str(), col * 300 + 100, row * 300 + 100, 120, ofx);
                
                else if (board[row][col] == 1) 
                    DrawText(o.c_str(), col * 300 + 100, row * 300 + 100, 120, ofy);
                
            }
        }

       
        if (!xwins && !ywins)
        {
            if (xTurn) 
                DrawText("Player 1 Turn", 5, 5, 15, ofx);
            
            else 
                DrawText("Player 2 Turn", 5, 5, 15, ofy);
            
        }

        if (!xwins && !ywins && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))        //INPUT
        {
            int touchX = GetMouseX();
            int touchY = GetMouseY();

            int boxWidth = 900 / 3;
            int boxHeight = 900 / 3;

            i = touchY / boxHeight;
            j = touchX / boxWidth;

            draw++;
            if (board[i][j] == -1) 
            {
                if (xTurn) {
                    board[i][j] = 0; 
                    xTurn = false; 
                }
                else
                {
                    board[i][j] = 1; 
                    xTurn = true;
                }
                PlaySound(click);
            }
        }

        
        if (Winx(board) == 'x')  xwins = true;
        
        else if (WinY(board) == 'o')  ywins = true;
        
        if (xwins)
        {
            back = DARKGRAY;
            ofx = GRAY, ofy = GRAY;
            DrawText("PLAYER 1 WINS! ", 230, 400, 50, RED);
        }
        else if (ywins)
        {
            back = DARKGRAY;
            ofx = GRAY, ofy = GRAY;
            DrawText("PLAYER 2 WINS! ", 230, 400, 50, BLUE);
        }
        else if (!xwins && !ywins && draw == 9)
        {
            back = DARKGRAY;
            ofx = GRAY, ofy = GRAY;
            DrawText("IT'S A DRAW! ", 260, 400, 50, GREEN);
        }

        EndDrawing();
    }

    UnloadTexture(image);
    UnloadSound(ini);
    UnloadSound(click);
    CloseWindow();

    return 0;
}


