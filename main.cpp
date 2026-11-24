#include <iostream>
#include <string>
#include <vector>
#include "raylib.h"
#include <ctime>
#include "Globals.h"
#include "FlockCamera.h"
#include "Vehicle.h"

using namespace std;

// Car image assets sourced from Y8 Games, "Park This Car":
// https://www.y8.com/games/park_this_car
// Original assets were edited using ChatGPT for originality.
// Credit for the original artwork belongs to its respective creators.

// dataset vector is used to contain vehicle records
// attributes is used to contain the information of the vehicle detected
void updateDataset(vector<FlockRecord>& dataset, VehicleInfo attributes) {

    // searches for an existing license plate
    for (int i = 0; i < dataset.size(); i++) {

        // checks if the license plate of the current record matches the detected vehicle
        if (dataset[i].vehicle.licensePlate == attributes.licensePlate) {

            // updates the existing record with the newest information
            dataset[i].vehicle = attributes;
            dataset[i].detectionCount++;

            return; // stops function when the existing record is updated
        }
    }

    // create a new record if there is no license plate
    FlockRecord record;

    record.vehicle = attributes; // stores detected vehicle information in the new record
    record.detectionCount = 1; // sets detection count to 1 to signal first detection

    dataset.push_back(record); // appends the new record to dataset vector
}

// prints out the information stored in a dataset

void printDataset(vector<FlockRecord>& dataset, string title) {
    cout << title << endl; // title of the resepctive dataset so basically all vehicles or speeding

    cout << "Plate\t\tMake\tColor\tSpeed\tDetections" << endl; // \t = tab
    cout << "------------------------------------------------------------------------" << endl;

    for (int i = 0; i < dataset.size(); i++) {

        // Print one row for each vehicle
        cout << dataset[i].vehicle.licensePlate << "\t"
             << dataset[i].vehicle.make << "\t"
             << dataset[i].vehicle.color << "\t"
             << dataset[i].vehicle.speed << "\t"
             << dataset[i].detectionCount << endl;
    }

    if (dataset.empty()) {
        cout << "No vehicles recorded." << endl;
    }

    cout << endl;
}



int main() {

    srand(time(0)); // generates random values

    // Window size
    InitWindow(1500, 750, "FlockWatch");
    SetTargetFPS(60); // Set FPS

    CarGreen = LoadTexture("cars/car_green.png"); // Loads green car image
    CarBlue = LoadTexture("cars/car_blue.png"); // Loads blue car image
    CarRed = LoadTexture("cars/car_red.png"); // Loads red car image
    Map = LoadTexture("Map.png"); // Loads Map image
    
    // if map did not load, close window
    if (Map.id == 0) {
        CloseWindow();
        return -1;
    }

    // spawns Flock cameras all over the map
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
    
    // Car 1's position is at (200, 355) and is a Green (Color) Toyota (Make)
    Vehicle car1(200, 355, "Toyota", "Green");
    car1.setSpeed(1, 0); // sets car 1's spped
    // vector of vehicles
    vector <Vehicle> cars;
    cars.push_back(car1); // always gonna start the program with car 1
    // fill the vector with vehicles until the appropriate amount is on screen
    while ((int)cars.size()<maxCarsOnScreen) {cars.push_back(Vehicle());}
    // // prints out car 1's make, color, and license plate
    // cout << car1.getCarMake() << " " << car1.getCarColor() << " " << car1.getLicensePlate() << endl;

    double lastPrint = GetTime();

    while (!WindowShouldClose()) {  // while window is open
        BeginDrawing(); // start drawing animation

        Rectangle source = { 0, 0, (float)Map.width, (float)Map.height }; // map
        Rectangle dest   = { 0, 0, 1500, 750 }; // map dimensions

       DrawTexturePro(Map, source, dest, {0, 0}, 0.0f, WHITE); // load map

        // // the following is for testing / workflow
        // Vector2 mouse = GetMousePosition(); // Gets current position of the mouse
        // DrawText(TextFormat("X: %.0f, Y: %.0f", mouse.x, mouse.y), 25,20, 20, BLACK); //temp draw text to help us identify coords better

       if (GetTime() - lastPrint >= 10) { //print every 10 seconds

        cout << "\n\n\n\n\n\n\n\n\n\n"; // tried researching ways on how to clear out the terminal automatically, but the

        printDataset(allVehicles, "====== ALL VEHICLES ======");
        printDataset(speedingVehicles, "====== SPEEDING VEHICLES ======");

        lastPrint = GetTime();
        }

        // go through the cars on screen and apply necessary functions
        for (int i=0;i<(int)cars.size();i++) {
            cars.at(i).drawVehicle();
            cars.at(i).moveVehicle();
            if (cars.at(i).isCarOutside()) {cars.at(i) = Vehicle();continue;}
        }

        // collision is initially set to false
        bool collision = false;


        // Draw cameras and check collisions
        for (FlockCamera& camera : cameras) {
            camera.resetColor(); // resets camera color before checking a new detection
            
            // checks if car 1 is detected by the camera
            for (Vehicle& car : cars) {
                if (camera.scanVehicle(car)) { 
                    VehicleInfo info = car.getVehicleInfo(); // gets car 1's information and stores it in info

                    updateDataset(allVehicles, info); // updates allVehicles dataset with the detected vehicle

                    // checks if the detected vehicle's speed goes over the speed limit
                    if (info.speed > SPEED_LIMIT) {
                        updateDataset(speedingVehicles, info); // updates speedingVehicles dataset with this vehicle
                    }
                }
            }

            camera.drawCamera(); // draws camera onto the screen

            // checks if the vehicle is inside the camera's range
            for (Vehicle& car : cars) {
                if (camera.isVehicleInRange(car)) {
                    collision = true; // sets collision to true
                }
            }
        }

       EndDrawing(); // end drawing animation
    }

    UnloadTexture(Map);
    UnloadTexture(CarGreen);
    UnloadTexture(CarBlue);
    UnloadTexture(CarRed);
    CloseWindow();
    
    return 0;
}