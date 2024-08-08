// Include Lib
#include <raylib.h>
#include "game.h"
#include "terrain.h"
#include "util/resource.h"

void init(int, int);
void update(void);
void draw(void);

void checkInputs(void);

void checkCollisions(void);

void restartGame(void);
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
    deInitRows(Game.rows,MAX_ROWS);
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
    Game.status=MENU;
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
        if(Game.player.playerInput==INTRO){
            Game.status=GAME;
        }
        break;
    case GAME:
    updatePlayer(&Game.player);
        updateRows(Game.rows,MAX_ROWS);
        Game.activeRow=getCurrentActiveRow(Game.rows,MAX_ROWS,getCurrentPlayerHitBox(&Game.player));
        checkCollisions();
        if((Game.player.state==SPLAH || Game.player.state==DROWING) && Game.player.playerInput==INTRO){
            if(Game.player.lives>=0){
                restartGame();
            }else{
                Game.status=GAME_OVER;
            }
        }
        break;
    case GAME_OVER:
        if(Game.player.playerInput==INTRO){
            Game.status=MENU;
        }
        break;
        

    default:
        break;
    }
}

void checkCollisions(void){
    Row activeRow = Game.rows[Game.activeRow];
    switch (activeRow.type)
    {
    case ROAD:
        for(int i=0;i<activeRow.entity_size;i++){
            if(checkCarEntitiesCollision(activeRow.entity[i],getCurrentPlayerHitBox(&Game.player))){
                Game.player.state=SPLAH;
            }
        }
        break;
    case RAIL:
        if(activeRow.entity_size>0){
            if(checkTrainEntitiesCollision(activeRow.entity[0],getCurrentPlayerHitBox(&Game.player))){
                Game.player.state=SPLAH;
            }
        }
        break;
    case WATER:
        bool drown=true;
        for(int i=0;i<activeRow.entity_size;i++){
            if(checkLogEntitiesCollision(activeRow.entity[i],getCurrentPlayerHitBox(&Game.player))){
                drown=false;
            }
        }
        if(drown){
            Game.player.state = DROWING;
        }
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
        drawRows(Game.rows,MAX_ROWS);
        DrawTexture(*getGfxTexture(TITLE_TYPE,0),-8,0,WHITE);
        DrawText("Press Enter To Continue...",100,600,20,WHITE);
        break;
    case GAME:
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
    case GAME_OVER:
        DrawTexture(*getGfxTexture(TITLE_TYPE,1),-4,0,WHITE);
        DrawText("Press Enter To Continue...",100,600,20,WHITE);
        break;

    default:
        break;
    }
}

void restartGame(void){
    Game.player.lives--;
    Game.player.position=(Vector2){GetScreenWidth()/2,0};
    Game.player.state=SIT;
    Game.player.offset=0;
    Game.player.direction=DOWN_DIR;
    Game.player.texture=getSpriteTexture(PLAYER_SIT_TYPE,DOWN_DIR);
}