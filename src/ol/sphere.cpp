/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "sphere.h"

//import {toRadians, toDegrees} from './math.js';
#include "./math.h"

using namespace ol;

/**
* Get the great circle distance (in meters) between two geographic coordinates.
* @param {Array} c1 Starting coordinate.
* @param {Array} c2 Ending coordinate.
* @param {number=} opt_radius The sphere radius to use.  Defaults to the Earth's
*     mean radius using the WGS84 ellipsoid.
* @return {number} The great circle distance between the points (in meters).
* @api
*/
number_t ol::sphere::getDistance(std::vector<number_t> const & c1, std::vector<number_t> const & c2, number_t opt_radius)
{
    using namespace ol::math;

    auto radius = opt_radius;
    auto lat1 = toRadians(c1[1]);
    auto lat2 = toRadians(c2[1]);
    auto deltaLatBy2 = (lat2 - lat1) / 2;
    auto deltaLonBy2 = toRadians(c2[0] - c1[0]) / 2;
    number_t a = std::sin(deltaLatBy2) * std::sin(deltaLatBy2) +
        std::sin(deltaLonBy2) * std::sin(deltaLonBy2) *
        std::cos(lat1) * std::cos(lat2);
    return 2 * radius * std::atan2(std::sqrt(a), std::sqrt(1 - a));
}
