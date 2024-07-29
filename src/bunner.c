//Include Lib
#include <raylib.h>
#include "util/resources.h"
#include "game.h"

void init(int, int);
void checkInputs(void);
void update(void);
void draw(void);

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
       


}

void checkInputs(void)
{
    Game.player.playerInput=checkPlayerInput();
}

void update(void){

    updatePlayer(&Game.player);
}

void draw(void){
 //init drawing mode
        BeginDrawing();
   
       
       BeginMode2D(Game.player.camera);
            //Clear Background
            ClearBackground(RAYWHITE);
            for(int i=0;i<MAX_TERRAINS;i++){
                drawRow(&Game.rows[i]);
            }

            drawPlayer(&Game.player);
        EndMode2D();
        //Finish Drawing Mode
        EndDrawing();
}