#ifndef FLOCKCAMERA_H
#define FLOCKCAMERA_H
#include "Vehicle.h"
#include "Globals.h"
#include <vector>
#include <string>

class FlockCamera {
private:
    int x = 0; // stores Flock camera's horizontal position
    int y = 0; // stores Flock camera's vertical position
    float range = 40.0f; // stores Flock camera's detection radius
    std::vector<std::string> carsInside; // stores the license plate of vehicle's inside Flock camera's detection range
    Color cameraColor = BLACK; // sets camera color to black

public:
    FlockCamera(int cx, int cy, float crange = 40.0f); // constructor that creates Flock camera at cx and cy with detection radius
    
    void resetColor(); // resets camera color back to black
    
    void drawCamera(); // draws the Flock camera on the screen

    bool isVehicleInRange(Vehicle car); // checks if the vehicle is within the camera's detection range

    bool scanVehicle(Vehicle car); // checks if the vehicle is newly detected by the Flock camera
};

#endif