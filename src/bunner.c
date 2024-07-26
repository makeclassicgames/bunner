//Include Lib
#include <raylib.h>
#include "util/resources.h"
#include "game.h"

//Main Function
int main(){
    //Window Dimensions
    const int screenWidth = 450;
    const int screenHeight = 800;
    
    //Init Window (width, Height, title)
    InitWindow(screenWidth,screenHeight,"Infinite Bunner");


     initTextures();
     
     initRows(Game.rows,MAX_TERRAINS);
     initPlayer(&Game.player,(Vector2){screenWidth/2,40},3);
       

    //Set target FPS
    SetTargetFPS(60);
    //Init()
    //While windows is open
    while(!WindowShouldClose()){

        //update()

        //Draw()
        //init drawing mode
        BeginDrawing();
        //Clear Background
        ClearBackground(RAYWHITE);
        //Draw Text
       
        for(int i=0;i<MAX_TERRAINS;i++){
            drawRow(&Game.rows[i]);
        }

        drawPlayer(&Game.player);
        //Finish Drawing Mode
        EndDrawing();
    }

    for(int i=0;i<MAX_TERRAINS;i++){
            deInitRow(&Game.rows[i]);
        }
    
    //Close Window
    CloseWindow();
    return 0;
}