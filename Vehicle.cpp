#include "Vehicle.h"
#include "raylib.h"
#include <string>
#include "Globals.h"
#include <cmath>
using namespace std;

// Class Vehicle

// Gets all the information of the vehicle
VehicleInfo Vehicle::getVehicleInfo() {
    VehicleInfo attributes; // created to store the vehicle's information

    attributes.licensePlate = licensePlate; // copies the vehicle's license into attributes
    attributes.make = carMake; // copies the vehicle's make into attributes
    attributes.color = carColor; // copies the vehicle's color into attributes
    attributes.speed = sqrt(xSpeed * xSpeed + ySpeed * ySpeed); // copies the vehicle's speed into attributes

    return attributes; // returns completed attributes
};

// default constructor
Vehicle::Vehicle() {
    int temploc = rand() % 6; // use a number to randomly choose a predetermined position to start
    int tempColor = rand() % 3;
    int speedingMultiplier = rand() % 2 + 1; // multiplies speed to make some vehicles speed
    int make = rand() % 4;
    
    if (temploc == 0) {x = 0; y = 360; angle = 0.0f; xSpeed = 1.0f; ySpeed = 0.0f;}
    else if (temploc == 1) {x = 0; y = 700; angle = 0.0f; xSpeed = 1.0f; ySpeed = 0.0f;}
    else if (temploc == 2) {x = 900; y = 205; angle = 180.0f; xSpeed = -1.0f; ySpeed = 0.0f;}
    else if (temploc == 3) {x = 890; y = 45; angle = 270.0f; xSpeed = 0.0f; ySpeed = 1.0f;}
    else if (temploc == 4) {x = 155; y = 380; angle = 30.0f; xSpeed = 0.867f; ySpeed = 0.415f;}
    else if (temploc == 5) {x = 1180; y = 235; angle = -30.0f; xSpeed = 0.867f; ySpeed= -0.40f;}
    
    xSpeed *= speedingMultiplier;
    ySpeed *= speedingMultiplier;
    
    // assign colors to the car
    if (tempColor == 0) {carColor = "Red";}
    if (tempColor == 1) {carColor = "Green";}
    if (tempColor == 2) {carColor = "Blue";}
    // assigned car make
    if (make == 0) {carMake = "Toyota";}
    else if (make == 1) {carMake = "BMW";}
    else if (make == 2) {carMake = "Volvo";}
    else if (make == 3) {carMake = "Honda";}

    generateLicensePlate(); // generates a unique license plate

}

// constructor for the vehicle class
Vehicle::Vehicle(float startX, float startY, string make, string color)
            : x(startX), y(startY), // starting coordinates for x and y
            carMake(make), carColor(color), // carMake and carColor receive make and color
            angle(0.0f), xSpeed(0.0f), ySpeed(0.0f) // angle, xSpeed, and ySpeed are initially set to 0
        {
        generateLicensePlate(); // generates random license plate
        }

// draws the vehicle on the map
void Vehicle::drawVehicle() {
        Texture2D texture; 

        if (carColor == "Green") { // checks if the car color is green
            texture = CarGreen; // assigns CarGreen to texture
        }
        else if (carColor == "Blue") { // checks if the car color is blue
            texture = CarBlue; // assigns CarBlue to texture
        }
        else { // checks if car color is red
            texture = CarRed; // assigns carRed to texture
        }

        DrawTextureEx(texture, {x, y}, angle, 0.03f, WHITE); // draws the car's texture on the screen
    }

// returns the vehicle's license plate
string Vehicle::getLicensePlate() {
    return licensePlate;
}

// returns the vehicle's make
string Vehicle::getCarMake() {
    return carMake;
    }

// returns the vehicle's color   
string Vehicle::getCarColor() {
    return carColor;
}

// generates random license plate
string Vehicle::generateLicensePlate() {

    string plate = ""; // empty string created that will contain the license plate

    // for loop runs 3 times to generate three random letters
    for (int i = 0;  i < 3;  i++)  {
        plate += ('A' + rand() % 26); // stores random letters into plate

    }

    // adds hyphen between the letters and numbers
    plate +=  '-';

     // for loop runs 4 times to generate 4 random numbers
    for (int i = 0;  i < 4;  i++)  {
        plate += ('0' + rand() % 10); // stores random numbers into plate
    }

    licensePlate = plate; // stores completed license plate inside Vehicle object
        
    return plate; // returns completed license plate  
}

// moves the vehicle by a specified amount
void Vehicle::moveVehicle(float xAmount, float yAmount) {
    x += xAmount; // adds movement amount to current x position
    y += yAmount; // adds current amount to current y position
}

// move vehicle using stored speed values
void Vehicle::moveVehicle() {
    x += xSpeed; // changes x position based on the vehicle speed
    y += ySpeed; // changes y position based on the vehicle speed
}

// set the vehicle's speed
void Vehicle::setSpeed(float newXSpeed, float newYSpeed) {
    xSpeed = newXSpeed; // update the vehicle's x speed
    ySpeed = newYSpeed; // update the vehicle's y speed
}

void Vehicle::setAngle(float newAngle) {angle = newAngle;} // set the vehicles angle to the angle passed into the function
void Vehicle::turnUp() {angle = 90.0f;} // turns the vehicle to face upward
void Vehicle::turnDown() {angle = 270.0f;} // turns the vehicle to face downward
void Vehicle::turnLeft() {angle = 180.0f;} // turns the vehicle to face left
void Vehicle::turnRight() {angle = 0.00f;} // turns the vehicle to face right

// flip speed of Vehicles to come back upon exiting maxX, maxY
void Vehicle::applyCorrection() {
    float absXSpeed = abs(xSpeed); // gets absolute value of horizontal speed
    float absYSpeed = abs(ySpeed); // gets absolute value of vertical speed
    if (x < 0) { // checks if the vehicle's x position has gone past the left of the screen
        y -= 15; // moves vehicle down by 15 to correct position on road
        xSpeed = absXSpeed; // makes horizontal speed positive so vehicle moves right
        turnRight(); // turns the vehicle to face right
    }
    if (y < 0) { // checks if the vehicle's y position has gone past the top of the screen
        ySpeed = absYSpeed; // makes vertical speed positive so vehicle moves downward
        turnDown(); // turns the vehicle to face downward
    }
    if (x > maxX) { // checks if the vehicle's x position has gone past the right of the screen
        y += 15; // moves vehicle down by 15 to keep it on the road
        x = maxX; // places vehicle at allowed maximum x position
        xSpeed = -absXSpeed; // makes horizontal speed negative so vehicle moves left
        turnLeft(); // turns the vehicle to face left
    }
    if (y > maxY) { // checks if the vehicle's y position has gone past the bottom of the screen
        y = maxY; // places vehicle at allowed maximum y position
        ySpeed = -absYSpeed; // makes vertical speed negative so vehicle moves upward
        turnUp(); // turns the vehicle to face upward
    }
}

bool Vehicle::isCarOutside() {

    if (x < 0 || x > maxX || y < 0 || y > maxY) {
        return true;
    }

    return false;
}

// creates a rectangle to represent the vehicle's hitbox
Rectangle Vehicle::getHitBox() {
    float width = CarGreen.width * 0.03f; // multiples the width of carGreen by 0.03
    float height = CarGreen.height * 0.03f; // multiples the height of carGreen by 0.03

    if (angle == 90.0f) { // checks if vehicle is facing up
        return {x - height, y, height, width}; // returns hitbox for facing up
    }
    else if (angle == 180.0f) { // checks if vehicle is facing left
        return {x - width, y - height, width, height}; // returns hitbox for facing left
    }
    else if (angle == 270.0f) { // checks if vehicle is facing down
        return {x, y - width, height, width}; // returns hitbox for facing down
    }

    return {x, y, width, height}; // returns the default hitbox
}