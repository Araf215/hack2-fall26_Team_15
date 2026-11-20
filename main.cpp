#include <iostream>
#include "raylib.h"

int main() {

    // Window size
    InitWindow(1500, 750, "FlockWatch");
    SetTargetFPS(60); //Set FPS

    Texture2D Car = LoadTexture("car.png"); // Car img
    Texture2D Map = LoadTexture("Map.png"); // Map img
    
    // if map didn't load close window
    if (Map.id == 0) {
        CloseWindow();
        return -1;
    }

    while (!WindowShouldClose()) {  //while window's opening
        BeginDrawing(); // start drawing anim

        Rectangle source = { 0, 0, (float)Map.width, (float)Map.height }; // map
        Rectangle dest   = { 0, 0, 1500, 750 }; // map dimensions


       DrawTexturePro(Map, source, dest, {0, 0}, 0.0f, WHITE); // load map
       DrawTextureEx(Car, {200, 175}, 0.03f, 0.03f, WHITE); // load car

       DrawCircle(200, 225, 40.0f, Fade(BLACK, 0.3f)); //Circle fade
       DrawCircleLines(200, 225, 40.0f, BLACK); // Circle outline
       DrawCircle(200, 225, 8.0f, BLACK); // Black dot

        EndDrawing(); // end drawing anim
    }

    return 0;
}