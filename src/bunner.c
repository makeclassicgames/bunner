//Include Lib
#include <raylib.h>
#include "game.h"

//Main Function
int main(){
    //Window Dimensions
    const int screenWidth = 450;
    const int screenHeight = 800;
    
    //Init Window (width, Height, title)
    InitWindow(screenWidth,screenHeight,"Infinite Bunner");

     Rectangle position = {0,80,screenWidth,40};
        Row* row= &Game.rows[0];
        Row* row2=&Game.rows[1];
        Row* row3=&Game.rows[2];
        Row* row4=&Game.rows[4];
        Row* row5=&Game.rows[5];
        Row* row6=&Game.rows[6];
        Row* row7=&Game.rows[7];
        Row* row8=&Game.rows[8];
        Row* row9=&Game.rows[9];
        Row* row10=&Game.rows[10];
        Row* row11=&Game.rows[11];
        Row* row12=&Game.rows[12];
        Row* row13=&Game.rows[13];
        Row* row14=&Game.rows[14];
        Row* row15=&Game.rows[15];
        Row* row16=&Game.rows[16];
        Row* row17=&Game.rows[17];
        Row* row18=&Game.rows[18];
        Row* row19=&Game.rows[19];
        Row* row20=&Game.rows[20];
        Row* row21=&Game.rows[21];
        Row* row22=&Game.rows[22];
        Row* row23=&Game.rows[23];

        Texture2D title = LoadTexture("../resources/gfx/title.png");


        initRow(row3,ROAD,0,position);
        initRow(row2,ROAD,1,(Rectangle){0,40,screenWidth,40});
        initRow(row,GRASS,0,(Rectangle){0,0,screenWidth,40});
        initRow(row4,RAIL,3,(Rectangle){0,100,screenWidth,40});
        initRow(row5,RAIL,2,(Rectangle){0,140,screenWidth,40});
        initRow(row6,RAIL,1,(Rectangle){0,180,screenWidth,40});
        initRow(row7,DIRT,12,(Rectangle){0,220,screenWidth,40});
        initRow(row8,DIRT,3,(Rectangle){0,260,screenWidth,40});
        initRow(row9,WATER,1,(Rectangle){0,300,screenWidth,40});
        initRow(row10,WATER,2,(Rectangle){0,340,screenWidth,40});
        initRow(row11,WATER,3,(Rectangle){0,380,screenWidth,40});
        initRow(row12,WATER,4,(Rectangle){0,400,screenWidth,40});
        initRow(row13,GRASS,15,(Rectangle){0,400,screenWidth,40});
        initRow(row14,GRASS,11,(Rectangle){0,440,screenWidth,40});
        initRow(row15,GRASS,12,(Rectangle){0,480,screenWidth,40});
        initRow(row16,GRASS,1,(Rectangle){0,520,screenWidth,40});
        initRow(row17,ROAD,2,(Rectangle){0,560,screenWidth,40});
        initRow(row18,ROAD,3,(Rectangle){0,600,screenWidth,40});
        initRow(row19,ROAD,4,(Rectangle){0,640,screenWidth,40});
        initRow(row20,RAIL,3,(Rectangle){0,660,screenWidth,40});
        initRow(row21,RAIL,2,(Rectangle){0,700,screenWidth,40});
        initRow(row22,RAIL,1,(Rectangle){0,740,screenWidth,40});
        initRow(row23,GRASS,7,(Rectangle){0,780,screenWidth,40});

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
    
        drawRow(row);
        drawRow(row2);
        drawRow(row3);
        drawRow(row4);
        drawRow(row5);
        drawRow(row6);
        drawRow(row7);
        drawRow(row8);
        drawRow(row9);
        drawRow(row10);
        drawRow(row11);
        drawRow(row13);
        drawRow(row14);
        drawRow(row15);
        drawRow(row16);
        drawRow(row17);
        drawRow(row18);
        drawRow(row19);
        drawRow(row20);
        drawRow(row21);
        drawRow(row22);
        drawRow(row23);

        DrawTexture(title,-10,0,WHITE);
        //Finish Drawing Mode
        EndDrawing();
    }

    deInitRow(row);
    deInitRow(row2);
    deInitRow(row3);
    deInitRow(row4);
    deInitRow(row5);
    deInitRow(row6);
    deInitRow(row7);
    deInitRow(row8);
    deInitRow(row9);
    deInitRow(row10);
    deInitRow(row11);
    deInitRow(row12);
    deInitRow(row13);
    deInitRow(row14);
    deInitRow(row15);
    deInitRow(row16);
    deInitRow(row17);
    deInitRow(row18);
    deInitRow(row19);
    deInitRow(row20);
    deInitRow(row21);
    deInitRow(row22);
    deInitRow(row23);

    //Close Window
    CloseWindow();
    return 0;
}