#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <string>
#include <cmath>
#include "raylib.h"
#include "Globals.h"



class Vehicle {
private: // these private  fields are attributes for our cars, we plan to add more identification attributes like car  color and  make if  time permits
    float x = 0; // stores vehicle's horizontal position
    float y = 0; // stores vehicle's vertical position
    float xSpeed = 0.0; // stores vehicle's horizontal speed
    float ySpeed = 0.0; // stores vehicle's vertical speed
    float angle = 0.00f; // stores vehicle's rotation angle
    std::string carMake; // stores the make of the vehicle
    std::string carColor; // stores the color of the vehicle
    std::string licensePlate; // stores the license plate of the vehicle
public:
    Vehicle(); // default constructor

    Vehicle(float startX, float startY, std::string make, std::string color); // constructor that creates vehicle with starting position, make, and color

    VehicleInfo getVehicleInfo(); // returns VehicleInfo structure with vehicle information

    void drawVehicle(); // draws the vehicle's texture onto the screen
    
    std::string getLicensePlate(); // returns the vehicle's license plate

    std::string getCarMake(); // returns the make of the vehicle

    std::string getCarColor(); // returns the color of the vehicle

    std::string generateLicensePlate(); // returns random license plate generated

    void moveVehicle(float xAmount, float yAmount); // moves the vehicles with specified x and y amounts

    void moveVehicle(); // moves the vehicle using xSpeed and ySpeed

    void setSpeed(float newXSpeed, float newYSpeed); // sets vehicle's horizontal and vertical speed

    void setAngle(float newAngle); // sets the vehicle's rotation angle
    void turnUp(); // turns the vehicle to face upward
    void turnDown(); // turns the vehicle to face downward
    void turnLeft(); // turns the vehicle to face left
    void turnRight(); // turns the vehicle to face right
    
    // flip speed of Vehicles to come back upon exiting maxX, maxY
    void applyCorrection();

    // check if car is out of bounds
    bool isCarOutside();

    Rectangle getHitBox(); // returns rectangle representing the vehicle's hitbox

};

#endif
