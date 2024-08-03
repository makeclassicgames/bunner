// Include Lib
#include <stdio.h>
#include <raylib.h>
#include "game.h"
#include "util/resources.h"

void init(int, int);
void checkInputs(void);
void update(void);
void draw(void);

void restartGame(void);

void checkCollisions(void);

// Main Function
int main()
{
    // Window Dimensions
    const int screenWidth = 450;
    const int screenHeight = 800;

    init(screenWidth, screenHeight);
    // Set target FPS
    SetTargetFPS(60);
    // While windows is open
    while (!WindowShouldClose())
    {
        checkInputs();
        update();
        draw();
    }

    for (int i = 0; i < MAX_TERRAINS; i++)
    {
        deInitRow(&Game.rows[i]);
    }

    // Close Window
    CloseWindow();
    return 0;
}

void init(int screenWidth, int screenHeight)
{
    // Init Window (width, Height, title)
    InitWindow(screenWidth, screenHeight, "Infinite Bunner");

    initTextures();

    initRows(Game.rows, MAX_TERRAINS);
    initPlayer(&Game.player, (Vector2){screenWidth / 2, 0}, 2);
    Game.status = MENU;
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
        if (Game.player.playerInput == INTRO)
        {
            Game.player.lives = 2;
            Game.status = GAME;
        }
        break;
    case GAME:

        updatePlayer(&Game.player);
        updateRows(Game.rows, MAX_TERRAINS);
        Game.activeRow = getCurrentActiveRow(Game.rows, MAX_TERRAINS, getCurrentHitBox(&Game.player));
        checkCollisions();
        if ((Game.player.state == SPLASH || Game.player.state == DROWING) && Game.player.playerInput == INTRO)
        {
            if (Game.player.lives >= 0)
            {
                restartGame();
            }
            else
            {
                Game.status = GAME_OVER;
            }
        }
        break;
    case GAME_OVER:
        if (Game.player.playerInput == INTRO)
        {
            Game.status = MENU;
            initRows(Game.rows,MAX_TERRAINS);
            initPlayer(&Game.player,(Vector2){GetScreenWidth()/2,2},2);
        }
        break;
    default:
        break;
    }
}

void checkCollisions(void)
{
    Row activeRow = Game.rows[Game.activeRow];
    switch (activeRow.type)
    {
    case ROAD:

        for (int i = 0; i < activeRow.entity_size; i++)
        {
            if (checkCarEntitiesCollision(activeRow.entities[i], getCurrentHitBox(&Game.player)))
            {
                // Game.player.state=SPLASH;
            }
        }
        break;
    case RAIL:
        if (activeRow.entity_size > 0)
        {
            if (checkTrainEntityCollision(activeRow.entities[0], getCurrentHitBox(&Game.player)))
            {
                //  Game.player.state=SPLASH;
            }
        }
        break;
    case WATER:
        bool drown = true;
        for (int i = 0; i < activeRow.entity_size; i++)
        {
            if (checkLogEntityCollision(activeRow.entities[i], getCurrentHitBox(&Game.player)))
            {
                drown = false;
            }
        }
        if (drown)
        {
            Game.player.state = DROWING;
        }
    default:
        break;
    }
}

void restartGame(void)
{
    Game.player.lives--;
    Game.player.position = (Vector2){GetScreenWidth() / 2, 0};
    Game.player.state = SIT;
    Game.player.offset = 0;
    Game.player.direction = DOWN_DIR;
    Game.player.texture = getSpriteTexture(PLAYER_SIT_TYPE, DOWN_DIR);
}

void draw(void)
{
    // init drawing mode
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (Game.status)
    {
    case MENU:

        drawRows(Game.rows, MAX_TERRAINS);
        DrawTexture(getGfxTexture(TITLE_TYPE, 0), -8, 0, WHITE);
        DrawText("Press Enter to Continue...", 100, 600, 20, WHITE);
        break;
    case GAME:
        BeginMode2D(Game.player.camera);
        drawRows(Game.rows, MAX_TERRAINS);
        drawPlayer(&Game.player);
        if (Game.player.state == SPLASH || Game.player.state == DROWING)
        {
            DrawText("Press Enter to Continue...", 100, 600, 20, WHITE);
        }
        EndMode2D();
        //Draw Lives
        drawLives(&Game.player);
        break;
    case GAME_OVER:
        DrawTexture(getGfxTexture(TITLE_TYPE, 1), -8, 0, WHITE);
        DrawText("Press Enter to Continue...", 100, 600, 20, WHITE);
        break;
    default:
        break;
    }
    // Finish Drawing Mode
    EndDrawing();
}