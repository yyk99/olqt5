/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "Units.h"
#include <math.h>

std::string
ol::proj::Units::DEGREES = "degrees",
ol::proj::Units::FEET = "ft",
ol::proj::Units::METERS = "m",
ol::proj::Units::PIXELS = "pixels",
ol::proj::Units::TILE_PIXELS = "tile-pixels",
ol::proj::Units::USFEET = "us-ft";

#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif

// use the radius of the Normal sphere
//METERS_PER_UNIT[Units.DEGREES] = 2 * Math.PI * 6370997 / 360;
//METERS_PER_UNIT[Units.FEET] = 0.3048;
//METERS_PER_UNIT[Units.METERS] = 1;
//METERS_PER_UNIT[Units.USFEET] = 1200 / 3937;
//

std::map<std::string, double> 
ol::proj::METERS_PER_UNIT = {
    { "degrees" , 2.0 * M_PI * 6370997.0 / 360.0 },
    {"ft", 0.3048 },
    {"m", 1},
    {"us-ft", 1200.0 / 3937.0 }
};
