#include "raylib.h"
#include <string>
using namespace std;
#include "Globals.h"
#include "Vehicle.h"
#include "FlockCamera.h"

// Class FlockCamera

bool FlockCamera::scanVehicle(Vehicle car) {
    string plate = car.getLicensePlate();
    bool detected = isVehicleInRange(car);

    for (int i = 0; i < carsInside.size(); i++) {

        if (carsInside[i] == plate) {

            if (!detected) {
                carsInside.erase(carsInside.begin() + i); // https://www.geeksforgeeks.org/cpp/stdstringerase-in-cpp/ erase and  begin help  prevent duplicate detentions by  erasing detections after  the first.  Geeks4Geeks helped teach me both of these vector properties.
            }

            return false;
        }
    }

    if (detected) {
        carsInside.push_back(plate);
        VehicleInfo attribute = car.getVehicleInfo();
        if (attribute.speed > SPEED_LIMIT) {
            cameraColor = RED;
        }
        else {
            cameraColor = GREEN;
        }
        return true;
    }

    return false;
};


FlockCamera::FlockCamera(int cx, int cy, float crange)
        : x(cx), y(cy), range(crange) {}

void FlockCamera::drawCamera() {
    DrawCircle(x, y, range, Fade(cameraColor, 0.3f));
    DrawCircleLines(x, y, range, cameraColor);
    DrawCircle(x, y, 8.0f, cameraColor);
}
void FlockCamera::resetColor() {
    cameraColor = BLACK;
}


bool FlockCamera::isVehicleInRange(Vehicle car) { // still needs distance calculation added
    Rectangle carBox = car.getHitBox();
        
    return CheckCollisionCircleRec({(float)x, (float)y}, range, carBox);
}

