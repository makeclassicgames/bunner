//Include Lib
#include <stdio.h>
#include <raylib.h>
#include "game.h"
#include "util/resources.h"


void init(int, int);
void checkInputs(void);
void update(void);
void draw(void);

void checkCollisions(void);


//Main Function
int main(){
    //Window Dimensions
    const int screenWidth = 450;
    const int screenHeight = 800;
    
   
    init(screenWidth,screenHeight);
    //Set target FPS
    SetTargetFPS(60);
    //While windows is open
    while(!WindowShouldClose()){
        checkInputs();
        update();
        draw();
    }

    for(int i=0;i<MAX_TERRAINS;i++){
            deInitRow(&Game.rows[i]);
    }
    
    //Close Window
    CloseWindow();
    return 0;
}


void init(int screenWidth, int screenHeight){
 //Init Window (width, Height, title)
    InitWindow(screenWidth,screenHeight,"Infinite Bunner");


     initTextures();
     
     initRows(Game.rows,MAX_TERRAINS);
     initPlayer(&Game.player,(Vector2){screenWidth/2,0},3);
     Game.status=MENU;  


}

void checkInputs(void)
{
    Game.player.playerInput=checkPlayerInput();
}

void update(void){
    switch (Game.status)
    {
    case MENU:
        if(Game.player.playerInput==INTRO){
            Game.status=GAME;
        }
        break;
    case GAME:
    updatePlayer(&Game.player);
    updateRows(Game.rows,MAX_TERRAINS);
    Game.activeRow=Game.player.position.y/40;
    checkCollisions();
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
    Row activeRow= Game.rows[Game.activeRow];
    switch (activeRow.type)
    {
    case ROAD:
    
        for(int i=0;i<activeRow.entity_size;i++){
            if(checkCarEntitiesCollision(activeRow.entities[i],Game.player.position)){
                
            }
        }
        break;
    
    default:
        break;
    }
    
}

void draw(void){
 //init drawing mode
       BeginDrawing();
       ClearBackground(RAYWHITE);
       switch (Game.status)
       {
       case MENU:
        
        drawRows(Game.rows,MAX_TERRAINS);
        DrawTexture(getGfxTexture(TITLE_TYPE,0),-8,0,WHITE);
        DrawText("Press Enter to Continue...",100,600,20,WHITE);
        break;
        case GAME:
        BeginMode2D(Game.player.camera);
            drawRows(Game.rows,MAX_TERRAINS);
            drawPlayer(&Game.player);
        EndMode2D();
        break;
        case GAME_OVER:
        DrawTexture(getGfxTexture(TITLE_TYPE,1),-8,0,WHITE);
        DrawText("Press Enter to Continue...",100,600,20,WHITE);
        break;
       default:
        break;
       }
        //Finish Drawing Mode
        EndDrawing();
}