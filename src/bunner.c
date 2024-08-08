// Include Lib
#include <raylib.h>
#include "game.h"
#include "terrain.h"
#include "util/resource.h"

//Functions Prototype

//Initialization function
//screenWidth-> Screen Width in pixels.
//screenHeight->Screen Height in pixels.
void init(int, int);
//Update Logic Funcions
void update(void);
//Draw Funcion
void draw(void);

//Check Inputs Function
void checkInputs(void);

//Check Collisions Function
void checkCollisions(void);

//Restart the game.
void restartGame(void);

// Main Function
int main()
{
    // Window Dimensions
    const int screenWidth = 450;
    const int screenHeight = 800;
    //Initialization
    init(screenWidth, screenHeight);
    // While windows is open
    while (!WindowShouldClose())
    {
        //Check the inputs
        checkInputs();
        // update()
        update();
       
        // Draw
        // init drawing mode
        BeginDrawing();
        // Clear Background
        ClearBackground(RAYWHITE);
        //Call to Draw Function
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
    //Init all the textures to VRAM
    initTextures();
    //INit all the rows and entities.
    initRows(Game.rows, MAX_ROWS);
    //Init the player
    initPlayer(&Game.player, (Vector2){screenWidth / 2, 2}, 2);
    // Set target FPS
    SetTargetFPS(60);
    //Set initial game status.
    Game.status=MENU;
}

void checkInputs(void)
{
    //Check the player input
    Game.player.playerInput = checkPlayerInput();
}

void update(void)
{
    //Switch Game status and update the logic
    switch (Game.status)
    {
    //Menu State
    case MENU:
    //IF the player press Enter, go to next state
        if(Game.player.playerInput==INTRO){
            Game.status=GAME;
        }
        break;
    //Game State
    case GAME:
        //Update the player logic
        updatePlayer(&Game.player);
        //Update row and entities positions
        updateRows(Game.rows,MAX_ROWS);
        //Get current active row (the current row where the player is setted)
        Game.activeRow=getCurrentActiveRow(Game.rows,MAX_ROWS,getCurrentPlayerHitBox(&Game.player));
        //Check the current collisions (only for the currentRow)
        checkCollisions();
        //if the player is splashed or drowing (on water)
        if((Game.player.state==SPLAH || Game.player.state==DROWING) && Game.player.playerInput==INTRO){
            //If there is remain lives
            if(Game.player.lives>=0){
                //Restart the game
                restartGame();
            }else{
                //IF there is no lives go to game over
                Game.status=GAME_OVER;
            }
        }
        break;
        //Game over state
    case GAME_OVER:
    //If the player press Intro, go to menu state
        if(Game.player.playerInput==INTRO){
            Game.status=MENU;
        }
        break;
        

    default:
        break;
    }
}

//Check the player collisions
void checkCollisions(void){
    //Get current activeRow
    Row activeRow = Game.rows[Game.activeRow];
    //depends on active row type, check the collision
    switch (activeRow.type)
    {
    //Road Type (Check the current cars doesn't collide)
    case ROAD:
        for(int i=0;i<activeRow.entity_size;i++){
            //IF there is collision the player splash
            if(checkCarEntitiesCollision(activeRow.entity[i],getCurrentPlayerHitBox(&Game.player))){
                Game.player.state=SPLAH;
            }
        }
        break;
    //Rail type (Check the player doesn't collide with the train)
    case RAIL:

        if(activeRow.entity_size>0){
            //Check the current train doesn't collide
            if(checkTrainEntitiesCollision(activeRow.entity[0],getCurrentPlayerHitBox(&Game.player))){
                Game.player.state=SPLAH;
            }
        }
        break;
    //Water type (Check if there is no coolide to drow under water)
    case WATER:
        //If there is no collide with one log, the player Drown.
        bool drown=true;
        for(int i=0;i<activeRow.entity_size;i++){
            if(checkLogEntitiesCollision(activeRow.entity[i],getCurrentPlayerHitBox(&Game.player))){
                drown=false;
            }
        }
        //change player state
        if(drown){
            Game.player.state = DROWING;
        }
        break;
    default:
        break;
    }
}

//Draw Function
void draw(void)
{
    //Depends on Game State
    switch (Game.status)
    {
        //Menu state
    case MENU:
        //Draw All the rows
        drawRows(Game.rows,MAX_ROWS);
        //Draw Title Screen
        DrawTexture(*getGfxTexture(TITLE_TYPE,0),-8,0,WHITE);
        //Draw Text Message
        DrawText("Press Enter To Continue...",100,600,20,WHITE);
        break;
    //Game State
    case GAME:
     //Begin Mode 2d (To update the camera)
     BeginMode2D(Game.player.camera);
        //Draw All the rows
        drawRows(Game.rows, MAX_ROWS);

        //Draw Obstacles (Entities)
        for (int i = 0; i < MAX_ROWS; i++)
        {
            for (int j = 0; j < Game.rows[i].entity_size; j++)
            {
                Row row = Game.rows[i];
                DrawTexture(row.entity[j].texture, row.entity[j].position.x, row.entity[j].position.y, WHITE);
            }
        }
        //Draw The Player
        drawPlayer(&Game.player);
        //If the player is not alive show the message
        if(Game.player.state==SPLAH || Game.player.state==DROWING){
           DrawText("Press Enter To Continue...",100,600,20,WHITE);
        }
        EndMode2D();
        
        break;
    //Game Over State
    case GAME_OVER:
        //Draw The Game Over Screen
        DrawTexture(*getGfxTexture(TITLE_TYPE,1),-4,0,WHITE);
        //Draw The Message.
        DrawText("Press Enter To Continue...",100,600,20,WHITE);
        break;

    default:
        break;
    }
}

//Restart current game.
void restartGame(void){
    Game.player.lives--;
    Game.player.position=(Vector2){GetScreenWidth()/2,0};
    Game.player.state=SIT;
    Game.player.offset=0;
    Game.player.direction=DOWN_DIR;
    Game.player.texture=getSpriteTexture(PLAYER_SIT_TYPE,DOWN_DIR);
}