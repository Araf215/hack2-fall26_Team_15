#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include <ctime>

using namespace std;

#define FLOCK_CIRCLE_FADE Fade(BLACK, 0.3f)

// Car image assets sourced from Y8 Games, "Park This Car":
// https://www.y8.com/games/park_this_car
// Original assets were edited using ChatGPT for originality.
// Credit for the original artwork belongs to its respective creators.


//declarations
Texture2D CarGreen;
Texture2D CarBlue;
Texture2D CarRed;
Texture2D Map; 
static int maxX = 1500;
static int maxY = 750;

//custom classes
class Vehicle {
private: // these private  fields are attributes for our cars, we plan to add more identification attributes like car  color and  make if  time permits
    float x = 0;
    float y = 0;
    float xSpeed = 0.0;
    float ySpeed = 0.0;
    float angle = 0.00f;
    string carMake;
    string carColor;
    string licensePlate;
public:
    Vehicle(float startX, float startY, string make, string color)
            : x(startX), y(startY),
            carMake(make), carColor(color),
            angle(0.0f), xSpeed(0.0f), ySpeed(0.0f)
        {
        generateLicensePlate();
        }

    void drawVehicle() {
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
    string getLicensePlate() { // getter  function
        return licensePlate;
    }

    string getCarMake() {
    return carMake;
    }

    string getCarColor() {
        return carColor;
    }
    string generateLicensePlate() {

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
    Rectangle getHitBox() {
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
};

class FlockCamera {
private:
    int x = 0;
    int y = 0;
    float range = 40.0f;
public:
    FlockCamera(int cx, int cy, float crange = 40.0f)
        : x(cx), y(cy), range(crange) {}
    void drawCamera() {
        DrawCircle(x,y,range,FLOCK_CIRCLE_FADE); // circle fade
        DrawCircleLines(x,y,range,BLACK);
        DrawCircle(x,y,8.0f,BLACK);
    }
    // void setFade() {} // gonna make it red when a vehicle passes through
    bool isVehicleInRange(Vehicle car) { // still needs distance calculation added
        Rectangle carBox = car.getHitBox();
        
        return CheckCollisionCircleRec({(float)x, (float)y}, range, carBox);
    }
};

int main() {

    srand(time(0));

    // Window size
    InitWindow(1500, 750, "FlockWatch");
    SetTargetFPS(60); //Set FPS

    CarGreen = LoadTexture("cars/car_green.png");
    CarBlue = LoadTexture("cars/car_blue.png");
    CarRed = LoadTexture("cars/car_red.png");
    Map = LoadTexture("Map.png"); // Map img
    
    // if map didn't load close window
    if (Map.id == 0) {
        CloseWindow();
        return -1;
    }

    // spawn cameras and cars
    vector<FlockCamera> cameras = {
        // Upper street
        FlockCamera(110, 168),
        FlockCamera(360, 168),
        FlockCamera(892, 168),
        FlockCamera(1340, 168),

        // Middle street
        FlockCamera(200, 355),
        FlockCamera(445, 355),
        FlockCamera(892, 355),
        FlockCamera(1340, 355),

        // Diagonal streets
        FlockCamera(350, 476),
        FlockCamera(529, 555),

        // Bottom street
        FlockCamera(89, 690),
        FlockCamera(355, 690),
        FlockCamera(622, 690),
        FlockCamera(892, 690)
    };
    
    // Vehicle car1 = Vehicle(200,175);
    Vehicle car1(200, 355, "Toyota", "Green");
    car1.setSpeed(1,0);
    cout << car1.getCarMake() << " " << car1.getCarColor() << " " << car1.getLicensePlate() << endl;


    while (!WindowShouldClose()) {  //while window's opening
        BeginDrawing(); // start drawing anim

        Rectangle source = { 0, 0, (float)Map.width, (float)Map.height }; // map
        Rectangle dest   = { 0, 0, 1500, 750 }; // map dimensions


       DrawTexturePro(Map, source, dest, {0, 0}, 0.0f, WHITE); // load map

       Vector2 mouse = GetMousePosition(); //temp mouse position

       DrawText(TextFormat("X: %.0f, Y: %.0f", mouse.x, mouse.y), 25,20, 20, BLACK); //temp draw text to help us identify coords better


        // draw the flock cameras and vehicles and give them behavior
        // Draw the vehicle
        car1.drawVehicle();
        DrawRectangleLinesEx(car1.getHitBox(), 2, RED);

        // Update the vehicle
        car1.moveVehicle();
        car1.applyCorrection();

        // Draw cameras and check collisions
        bool collision = false;

        for (FlockCamera& camera : cameras) {
            camera.drawCamera();

            if (camera.isVehicleInRange(car1)) {
                collision = true;
            }
        }

        if (collision) {
            DrawText("COLLISION!", 50, 50, 30, RED);
        }

       EndDrawing(); // end drawing anim
    }

    UnloadTexture(Map);
    UnloadTexture(CarGreen);
    UnloadTexture(CarBlue);
    UnloadTexture(CarRed);
    CloseWindow();
    return 0;
}