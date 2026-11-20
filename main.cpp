#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"

using namespace std;

#define FLOCK_CIRCLE_FADE Fade(BLACK, 0.3f)

//declarations
Texture2D Car;
Texture2D Map;
static int maxX = 1500;
static int maxY = 750;
vector <string> licensePlatesRegistered; // might make a separate class later

//custom classes
class Vehicle {
private: // these private  fields are attributes for our cars, we plan to add more identification attributes like car  color and  make if  time permits
    float x = 0;
    float y = 0;
    float xSpeed = 0.0;
    float ySpeed = 0.0;
    float angle = 0.00f;
    string licensePlate = "DEFAULT";
public:
    Vehicle(float startX, float startY, string plate, float startAngle,float startXSpeed, float startYSpeed) : x(startX), y(startY), licensePlate(plate), angle(startAngle), xSpeed(startXSpeed), ySpeed(startYSpeed) {

    }
    Vehicle(float startX, float startY) : x(startX), y(startY), licensePlate("DEFAULT"), angle(0.00f), xSpeed(0.0f), ySpeed(0.0f) {
        
    }
    void drawVehicle() {
        DrawTextureEx(Car, {x, y}, angle, 0.03f, WHITE); // load car
    }
    string getLicensePlate() { // getter  function
        return licensePlate;
    }
    void generateLicensePlate() {
    
    }
    void moveVehicle(float xAmount, float yAmount) {
        x += xAmount;
        y += yAmount;
    }
    void moveVehicle() {
        x += xSpeed;
        y += ySpeed;
    }
    void setSpeed(float newXSpeed, float newYSpeed) {
        xSpeed = newXSpeed;
        ySpeed = newYSpeed;
    }
    void setAngle(float newAngle) {angle = newAngle;}
    void turnUp() {angle = 90.0f;}
    void turnDown() {angle = 270.0f;}
    void turnLeft() {angle = 180.0f;}
    void turnRight() {angle = 0.00f;}
    // flip speed of Vehicles to come back upon exiting maxX, maxY
    void applyCorrection() {
        int absXSpeed = abs(xSpeed);
        int absYSpeed = abs(ySpeed);
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
};

class FlockCamera {
private:
    int x = 0.0;
    int y = 0.0;
    float range = 40.0f;
public:
    FlockCamera(int cx, int cy, float crange) : x(cx) , y(cy) , range(crange) {

    }
    FlockCamera(int cx, int cy) : x(cx), y(cy),range(40.0f) {

    }
    void drawCamera() {
        DrawCircle(x,y,range,FLOCK_CIRCLE_FADE); // circle fade
        DrawCircleLines(x,y,range,BLACK);
        DrawCircle(x,y,8.0f,BLACK);
    }
    // void setFade() {} // gonna make it red when a vehicle passes through
    bool isVehicleInRange(Vehicle victim) { // still needs distance calculation added
        float distance = 0.0;
        if (distance <= range) return true;
        return false;
    }
};

int main() {

    // Window size
    InitWindow(1500, 750, "FlockWatch");
    SetTargetFPS(60); //Set FPS

    Car = LoadTexture("car.png"); // Car img
    Map = LoadTexture("Map.png"); // Map img
    
    // if map didn't load close window
    if (Map.id == 0) {
        CloseWindow();
        return -1;
    }

    // spawn cameras and cars
    FlockCamera flock1 = FlockCamera(200,355);
    // Vehicle car1 = Vehicle(200,175);
    Vehicle car1 = Vehicle(200,355);
    car1.setSpeed(1,0);


    while (!WindowShouldClose()) {  //while window's opening
        BeginDrawing(); // start drawing anim

        Rectangle source = { 0, 0, (float)Map.width, (float)Map.height }; // map
        Rectangle dest   = { 0, 0, 1500, 750 }; // map dimensions


       DrawTexturePro(Map, source, dest, {0, 0}, 0.0f, WHITE); // load map

        // draw the flock cameras and vehicles and give them behavior
        flock1.drawCamera();
        car1.drawVehicle();
        car1.moveVehicle();
        car1.applyCorrection();

       EndDrawing(); // end drawing anim
    }

    UnloadTexture(Map);
    UnloadTexture(Car);
    CloseWindow();
    return 0;
}