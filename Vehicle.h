#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <string>
#include "raylib.h"
#include "Globals.h"
#include "FlockCamera.h"

class Vehicle {
private: // these private  fields are attributes for our cars, we plan to add more identification attributes like car  color and  make if  time permits
    float x = 0;
    float y = 0;
    float xSpeed = 0.0;
    float ySpeed = 0.0;
    float angle = 0.00f;
    std::string carMake;
    std::string carColor;
    std::string licensePlate;
public:
    Vehicle(float startX, float startY, std::string make, std::string color);

    void drawVehicle();
    
    std::string getLicensePlate(); // getter  function

    std::string getCarMake();

    std::string getCarColor();

    std::string generateLicensePlate();

    void moveVehicle(float xAmount, float yAmount);

    void moveVehicle();

    void setSpeed(float newXSpeed, float newYSpeed);

    void setAngle(float newAngle);
    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();
    
    // flip speed of Vehicles to come back upon exiting maxX, maxY
    void applyCorrection();

    Rectangle getHitBox();

};

#endif
