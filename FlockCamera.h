#ifndef FLOCKCAMERA_H
#define FLOCKCAMERA_H
#include "Vehicle.h"
#include "Globals.h"
#include <vector>
#include <string>

class FlockCamera {
private:
    int x = 0;
    int y = 0;
    float range = 40.0f;
    std::vector<std::string> carsInside;\
    Color cameraColor = BLACK;

public:
    FlockCamera(int cx, int cy, float crange = 40.0f);
    
    void resetColor();
    
    void drawCamera();
    
    // void setFade() {} // gonna make it red when a vehicle passes through
    bool isVehicleInRange(Vehicle car);

    bool scanVehicle(Vehicle car);
};

#endif