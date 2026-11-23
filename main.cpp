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

void updateDataset(vector<FlockRecord>& dataset, VehicleInfo attributes) {

    // searches for an existing license plate
    for (int i = 0; i < dataset.size(); i++) {

        if (dataset[i].vehicle.licensePlate == attributes.licensePlate) {

            // upd the existing record
            dataset[i].vehicle = attributes;
            dataset[i].lastDetected = GetTime();
            dataset[i].detectionCount++;

            return;
        }
    }

    // create  a  new record  if  there's no plate
    FlockRecord record;

    record.vehicle = attributes;
    record.lastDetected = GetTime();
    record.detectionCount = 1;

    dataset.push_back(record);
}


void printDataset(vector<FlockRecord>& dataset, string title) {
    cout << title << endl;

    if (dataset.empty()) {
        cout << "No vehicles recorded." << endl;
    }

    for (int i = 0; i < dataset.size(); i++) {
        cout << "Plate: " << dataset[i].vehicle.licensePlate << endl;
        cout << "Make: " << dataset[i].vehicle.make << endl;
        cout << "Color: " << dataset[i].vehicle.color << endl;
        cout << "Speed: " << dataset[i].vehicle.speed << endl;
        cout << "Last Detected: " << dataset[i].lastDetected << endl;
        cout << "Detections: " << dataset[i].detectionCount << endl;
    }
}

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


    while (!WindowShouldClose()) {  //while window's open
        BeginDrawing(); // start drawing anim

        Rectangle source = { 0, 0, (float)Map.width, (float)Map.height }; // map
        Rectangle dest   = { 0, 0, 1500, 750 }; // map dimensions


       DrawTexturePro(Map, source, dest, {0, 0}, 0.0f, WHITE); // load map

       Vector2 mouse = GetMousePosition(); //temp mouse position


        // draw the flock cameras and vehicles and give them behavior
        // Draw the vehicle
        car1.drawVehicle();

        // Update the vehicle
        car1.moveVehicle();
        car1.applyCorrection();

        // Draw cameras and check collisions
        bool collision = false;

        for (FlockCamera& camera : cameras) {
            camera.resetColor();
            
            if (camera.scanVehicle(car1)) {
                VehicleInfo info = car1.getVehicleInfo();

                updateDataset(allVehicles, info);

                if (info.speed > SPEED_LIMIT) {
                    updateDataset(speedingVehicles, info);
                }

                printDataset(allVehicles, "ALL VEHICLES");
                printDataset(speedingVehicles, "SPEEDING VEHICLES");
            }

            camera.drawCamera();

            if (camera.isVehicleInRange(car1)) {
                collision = true;
            }
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