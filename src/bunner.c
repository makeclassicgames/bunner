//Include Lib
#include <raylib.h>
#include "game.h"
#include "terrain.h"
#include "util/resource.h"

void init(int,int);
void update(void);
void draw(void);

//Main Function
int main(){
    //Window Dimensions
    const int screenWidth = 450;
    const int screenHeight = 800;
    
    init(screenWidth,screenHeight);
    //While windows is open
    while(!WindowShouldClose()){

        //update()

        //Draw()
        //init drawing mode
        BeginDrawing();
        //Clear Background
        ClearBackground(RAYWHITE);
        draw();
        //Finish Drawing Mode
        EndDrawing();
    }
    //Close Window
    CloseWindow();
    return 0;
}

void init(int screenWidth,int screenHeight){
    //Init Window (width, Height, title)
    InitWindow(screenWidth,screenHeight,"Hello Raylib");

    initTextures();
    initRows(Game.rows,MAX_ROWS);
    //Set target FPS
    SetTargetFPS(60);
}

void update(void){

}

void draw(void){

    switch (Game.status)
    {
    case MENU:
    case GAME:
    case GAME_OVER:
        drawRows(Game.rows,MAX_ROWS);
        break;
    
    default:
        break;
    }
}