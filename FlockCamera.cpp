#include "FlockWatch.h"
#include "raylib.h"
#include <string>
using namespace std;
#include "Globals.h"
#include "Vehicle.h"


// Class FlockCamera

FlockCamera::FlockCamera(int cx, int cy, float crange)
        : x(cx), y(cy), range(crange) {}

void FlockCamera::drawCamera() {
        DrawCircle(x,y,range,FLOCK_CIRCLE_FADE); // circle fade
        DrawCircleLines(x,y,range,BLACK);
        DrawCircle(x,y,8.0f,BLACK);
    }

// void setFade() {} // gonna make it red when a vehicle passes through
bool FlockCamera::isVehicleInRange(Vehicle car) { // still needs distance calculation added
    Rectangle carBox = car.getHitBox();
        
    return CheckCollisionCircleRec({(float)x, (float)y}, range, carBox);
}

