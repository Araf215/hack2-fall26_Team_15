#include <iostream>
#include "raylib.h"
using namespace std;

int main() {

    InitWindow(1000, 800, "map");
    SetTargetFPS(60);

    Texture2D photo = LoadTexture("map.png.webp");
    if (photo.id == 0) {
        CloseWindow();
        return -1;
    }



    return 0;
}
