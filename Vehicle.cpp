#include "Vehicle.h"
#include "raylib.h"
#include <string>
using namespace std;
#include "Globals.h"
#include "FlockCamera.h"

// Class Vehicle

Vehicle::Vehicle(float startX, float startY, string make, string color)
            : x(startX), y(startY),
            carMake(make), carColor(color),
            angle(0.0f), xSpeed(0.0f), ySpeed(0.0f)
        {
        generateLicensePlate();
        }

void Vehicle::drawVehicle() {
        Texture2D texture;

        if (carColor == "Green") {
            texture = CarGreen;
        }
        else if (carColor == "Blue") {
            texture = CarBlue;
        }
        else {
            texture = CarRed;
        }

        DrawTextureEx(texture, {x, y}, angle, 0.03f, WHITE);
    }

string Vehicle::getLicensePlate() { // getter  function
    return licensePlate;
}

string Vehicle::getCarMake() {
    return carMake;
    }

string Vehicle::getCarColor() {
    return carColor;
}

string Vehicle::generateLicensePlate() {

        string plate = "";

        for(int i  = 0;  i  < 3;  i++)  {
            plate += ('A' + rand() % 26);

        }

        plate +=  '-';

        for(int i  = 0;  i  < 4;  i++)  {
            plate += ('0' + rand() % 10);
        }

        licensePlate = plate;
        return plate;
    
    }

void Vehicle::moveVehicle(float xAmount, float yAmount) {
    x += xAmount;
    y += yAmount;
}

void Vehicle::moveVehicle() {
    x += xSpeed;
    y += ySpeed;
}

void Vehicle::setSpeed(float newXSpeed, float newYSpeed) {
    xSpeed = newXSpeed;
    ySpeed = newYSpeed;
}

void Vehicle::setAngle(float newAngle) {angle = newAngle;}
void Vehicle::turnUp() {angle = 90.0f;}
void Vehicle::turnDown() {angle = 270.0f;}
void Vehicle::turnLeft() {angle = 180.0f;}
void Vehicle::turnRight() {angle = 0.00f;}

// flip speed of Vehicles to come back upon exiting maxX, maxY
void Vehicle::applyCorrection() {
    float absXSpeed = abs(xSpeed);
    float absYSpeed = abs(ySpeed);
    if (x < 0) {
        y -= 15; //reset  previous car correction  (y+= 15)
        xSpeed = absXSpeed;
        turnRight();
    }
    if (y < 0) {
        ySpeed = absYSpeed;
        turnDown();
    }
    if (x > maxX) {
        y += 15;  //temporary correction for the car to  be on the road  when it drives on  the left side of the  road (FIXME FUTURE)
        x = maxX;
        xSpeed = -absXSpeed;
        turnLeft();
    }
    if (y > maxY) {
        y = maxY;
        ySpeed = -absYSpeed;
        turnUp();
    }
}

Rectangle Vehicle::getHitBox() {
    float width = CarGreen.width * 0.03f;
    float height = CarGreen.height * 0.03f;

    if (angle == 90.0f) {
        return {x - height, y, height, width};
    }
    else if (angle == 180.0f) {
        return {x - width, y - height, width, height};
    }
    else if (angle == 270.0f) {
        return {x, y - width, height, width};
    }

    return {x, y, width, height};
}