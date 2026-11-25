#ifndef GLOBALS_H
#define GLOBALS_H
#include "raylib.h"
#include <string>
#include <vector>

const float SPEED_LIMIT = 1.5f; // sets the speed limit to 1.5

// class to store vehicle information
class VehicleInfo {
    public:
        std::string licensePlate; // stores vehicle license plate
        std::string color; // stores vehicle color
        std::string make; // stores vehicle make
        float speed; // stores vehicle speed
};

// class to store vehicle detection record
class FlockRecord {
    public:
        VehicleInfo vehicle; // stores information of a detected vehicle
        int detectionCount; // stores the amount of times the vehicle was detected
};

// CITATION: GeeksForGeeks was used to help with the codelines below using inline https://www.geeksforgeeks.org/cpp/inline-functions-cpp/
inline std::vector<FlockRecord> allVehicles; // vector created to store records of all detected vehicles
inline std::vector<FlockRecord> speedingVehicles; // vector created to store records of all detected speeding vehicles
inline Texture2D CarGreen; // declaration of green car texture image
inline Texture2D CarBlue; // declaration of blue car texture image
inline Texture2D CarRed; // declaration of red car texture image
inline Texture2D Map; // declaration of Map image
inline const int maxX = 1500; // set max horizontal position the cars can travel to
inline const int maxY = 750; // set max vertical position the cars can travel to

inline const int maxCarsOnScreen = 4;

#endif