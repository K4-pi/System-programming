#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void guiWindow(int bufferSize)
{
    int screenWidth = 400;
    int screenHeight = 200;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raygui - controls test suite");
    SetTargetFPS(60);

    bool showMessageBox = false;

    while (!WindowShouldClose())
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        Rectangle textBox = { 10, screenHeight - 60, screenWidth - 100, 50};

        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if (GuiButton((Rectangle){screenWidth - 110, screenHeight - 60, 100, 50}, "SEND"))
        {
            // Send message to server    
        }




        EndDrawing();
    }

    CloseWindow();
}
