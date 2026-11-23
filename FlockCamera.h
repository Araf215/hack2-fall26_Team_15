#ifndef FLOCKCAMERA_H
#define FLOCKCAMERA_H
#include "Vehicle.h"
#include "Globals.h"

class Vehicle;

class FlockCamera {
private:
    int x = 0;
    int y = 0;
    float range = 40.0f;
public:
    FlockCamera(int cx, int cy, float crange = 40.0f);
    
    void drawCamera();
    
    // void setFade() {} // gonna make it red when a vehicle passes through
    bool isVehicleInRange(Vehicle car);
};

#endif