#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define BUFFER_SIZE 512

int main()
{
    //-------------------Network section-------------------------
    char sendBuffer[BUFFER_SIZE] = "\0";
    char readBuffer[BUFFER_SIZE] = { 0 };
    int client_fd;
    int letterCount = 0;

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Faild to create socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1500);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) < 0)
    {
        perror("Wrong server addres");
        exit(1);
    }
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection error");
        exit(1);
    }

    //-------------------GUI section-------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 500;
    bool sendMsg = false;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raygui - controls test suite");
    SetTargetFPS(60);

    bool showMessageBox = false;

    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        int key = GetCharPressed();
        
        while (key > 0) //It allows to queue chars 
        {
            
            if (key >= 32 && key <= 125) 
            {
                sendBuffer[letterCount] = key;
                letterCount++;
            }
            
            key = GetCharPressed(); //Checks next char in queue
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
        {
            letterCount--;
            sendBuffer[letterCount] = '\0';
        }

        Rectangle textBox = { 10, screenHeight - 60, screenWidth - 140, 50};
        if (sendMsg)
        {
            send(client_fd, sendBuffer, strlen(sendBuffer), 0);
            printf("client send packet\n");
            memset(sendBuffer, 0, BUFFER_SIZE); //Clear buffer
            letterCount = 0;

            read(client_fd, readBuffer, BUFFER_SIZE - 1);
            printf("%s", readBuffer);
            memset(readBuffer, 0, BUFFER_SIZE - 1); //Clear buffer
            sendMsg = false;
        }

        BeginDrawing();
        
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawRectangleRec(textBox, LIGHTGRAY);

        DrawText(sendBuffer, textBox.x + 5, textBox.y + 5, 40, MAROON);

        if (GuiButton((Rectangle){screenWidth - 110, screenHeight - 60, 100, 50}, "SEND")) sendMsg = true;
        
        EndDrawing();
    }
    CloseWindow();
    
    close(client_fd); 
    return 0;
}
