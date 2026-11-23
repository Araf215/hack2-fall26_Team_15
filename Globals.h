#ifndef GLOBALS_H
#define GLOBALS_H
#include "raylib.h"
#include <string>
#include <vector>


#define FLOCK_CIRCLE_FADE Fade(BLACK, 0.3f)

const float SPEED_LIMIT = 1.5f;

class VehicleInfo {
    public:
        std::string licensePlate;
        std::string color;
        std::string make;
        float speed;


};

class FlockRecord {
    public:
        VehicleInfo vehicle;
        double lastDetected;
        int detectionCount;
};

inline std::vector<FlockRecord> allVehicles;
inline std::vector<FlockRecord> speedingVehicles;

inline Texture2D CarGreen;
inline Texture2D CarBlue;
inline Texture2D CarRed;
inline Texture2D Map; 
inline const int maxX = 1500;
inline const int maxY = 750;

#endif