#include "raylib.h"
#include <string>
#include "Globals.h"
#include "Vehicle.h"
#include "FlockCamera.h"
using namespace std;

// Class FlockCamera

// checks if the vehicle is detected by a Flock camera
bool FlockCamera::scanVehicle(Vehicle car) {
    string plate = car.getLicensePlate(); // cets the vehicle's license plate and stores it into plate
    bool detected = isVehicleInRange(car); // checks if the vehicle is within the camera's detection range

    for (int i = 0; i < carsInside.size(); i++) { // for loop runs through the license plate stored inside carsInside

        if (carsInside[i] == plate) { // checks if the vehicle's license plate is in the carsInside vector

            if (!detected) {
                carsInside.erase(carsInside.begin() + i); // CITATION: https://www.geeksforgeeks.org/cpp/stdstringerase-in-cpp/ erase and  begin help  prevent duplicate detentions by  erasing detections after  the first.  Geeks4Geeks helped teach us both of these vector properties.
            }

            return false; // returns false because the vehicle has already been recorded as being inside
        }
    }

    if (detected) { // checks if the vehicle is within the camera's range
        carsInside.push_back(plate); // appends the vehicle's license plate into carsInside
        VehicleInfo attribute = car.getVehicleInfo(); // gets the vehicle's information and stores it into attribute
        
        if (attribute.speed > SPEED_LIMIT) { // checks if the vehicle's speed is greater than the speed limit
            cameraColor = RED; // changes camera color to red if the vehicle is speeding
        }
        else {
            cameraColor = GREEN; // changes camera color to green if the vehicle is not speeding
        }

        return true; // return true since this is a new detection of the vehicle
    }

    return false; // return false if vehicle is not newly detected and is not in range
};

// constructor for FlockCamera class
FlockCamera::FlockCamera(int cx, int cy, float crange)
        : x(cx), y(cy), range(crange) {} // x receives cx, y receives cy, and range receives crange

// draws camera and detection circle on the screen
void FlockCamera::drawCamera() {

    DrawCircle(x, y, range, Fade(cameraColor, 0.3f)); // draws filled circle representing the camera's detection range
    DrawCircleLines(x, y, range, cameraColor); // draws outline of the detection circle
    DrawCircle(x, y, 8.0f, cameraColor); // draws a small filled circle at camera's position

}

// resets the camera's color
void FlockCamera::resetColor() {
    cameraColor = BLACK; // change camera color back to black
}

// checks if the vehicle's hitbox overlaps with the Flock camera
bool FlockCamera::isVehicleInRange(Vehicle car) {
    Rectangle carBox = car.getHitBox(); // gets the vehicle's hitbox rectangle and stores it in carBox
        
    return CheckCollisionCircleRec({(float)x, (float)y}, range, carBox); // returns to see if the Flock camera and the vehicle's hitbox overlap
}

