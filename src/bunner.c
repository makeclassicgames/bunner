// Include Lib
#include <raylib.h>
#include "game.h"
#include "terrain.h"
#include "util/resource.h"

void init(int, int);
void update(void);
void draw(void);

void checkInputs(void);

// Main Function
int main()
{
    // Window Dimensions
    const int screenWidth = 450;
    const int screenHeight = 800;

    init(screenWidth, screenHeight);
    // While windows is open
    while (!WindowShouldClose())
    {

        checkInputs();
        // update()
        update();
        // Draw()
        // init drawing mode
        BeginDrawing();
        // Clear Background
        ClearBackground(RAYWHITE);
        draw();
        // Finish Drawing Mode
        EndDrawing();
    }
    // Close Window
    CloseWindow();
    return 0;
}

void init(int screenWidth, int screenHeight)
{
    // Init Window (width, Height, title)
    InitWindow(screenWidth, screenHeight, "Hello Raylib");

    initTextures();
    initRows(Game.rows, MAX_ROWS);
    initPlayer(&Game.player, (Vector2){screenWidth / 2, 2}, 2);
    // Set target FPS
    SetTargetFPS(60);
}

void checkInputs(void)
{
    Game.player.playerInput = checkPlayerInput();
}

void update(void)
{
    switch (Game.status)
    {
    case MENU:
    case GAME:
    case GAME_OVER:

        updatePlayer(&Game.player);
        break;

    default:
        break;
    }
}

void draw(void)
{

    switch (Game.status)
    {
    case MENU:
    case GAME:
    case GAME_OVER:
        BeginMode2D(Game.player.camera);
        drawRows(Game.rows, MAX_ROWS);

       
        for (int i = 0; i < MAX_ROWS; i++)
        {
            for (int j = 0; j < Game.rows[i].entity_size; j++)
            {
                Row row = Game.rows[i];
                DrawTexture(row.entity[j].texture, row.entity[j].position.x, row.entity[j].position.y, WHITE);
            }
        }
        drawPlayer(&Game.player);

        EndMode2D();
        break;

    default:
        break;
    }
}