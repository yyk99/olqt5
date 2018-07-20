/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "epsg3857.h"


#include "Units.h"
#include <math.h>


std::string
ol::proj::Units::DEGREES = "degrees",
ol::proj::Units::FEET = "ft",
ol::proj::Units::METERS = "m",
ol::proj::Units::PIXELS = "pixels",
ol::proj::Units::TILE_PIXELS = "tile-pixels",
ol::proj::Units::USFEET = "us-ft";

// use the radius of the Normal sphere
//METERS_PER_UNIT[Units.DEGREES] = 2 * Math.PI * 6370997 / 360;
//METERS_PER_UNIT[Units.FEET] = 0.3048;
//METERS_PER_UNIT[Units.METERS] = 1;
//METERS_PER_UNIT[Units.USFEET] = 1200 / 3937;
//

#include "../math_pi.h"

std::map<std::string, double>
ol::proj::METERS_PER_UNIT = {
    { "degrees" , 2.0 * M_PI * 6370997.0 / 360.0 },
{ "ft", 0.3048 },
{ "m", 1 },
{ "us-ft", 1200.0 / 3937.0 }
};


namespace ol {
namespace proj {
namespace epsg3857 {

const extent::Extent EXTENT = { -HALF_SIZE, -HALF_SIZE, HALF_SIZE, HALF_SIZE };

const extent::Extent WORLD_EXTENT = { -180, -85, 180, 85 };

std::vector<ol::proj::ProjectionP> PROJECTIONS = {
    ol::proj::ProjectionP(new EPSG3857Projection("EPSG:3857")),
    ol::proj::ProjectionP(new EPSG3857Projection("EPSG:102100")),
    ol::proj::ProjectionP(new EPSG3857Projection("EPSG:102113")),
    ol::proj::ProjectionP(new EPSG3857Projection("EPSG:900913")),
    ol::proj::ProjectionP(new EPSG3857Projection("urn:ogc:def:crs:EPSG:6.18:3:3857")),
    ol::proj::ProjectionP(new EPSG3857Projection("urn:ogc:def:crs:EPSG::3857")),
    ol::proj::ProjectionP(new EPSG3857Projection("http://www.opengis.net/gml/srs/epsg.xml#3857"))
};


/**
* Transformation from EPSG:4326 to EPSG:3857.
*
* @param {Array.<number>} input Input array of coordinate values.
* @param {Array.<number>=} opt_output Output array of coordinate values.
* @param {number=} opt_dimension Dimension (default is `2`).
* @return {Array.<number>} Output array of coordinate values.
*/
std::vector<number_t>& fromEPSG4326(std::vector<number_t> const & input, std::vector<number_t>& output, int opt_dimension)
{
    auto length = input.size();
    auto dimension = opt_dimension > 1 ? opt_dimension : 2;

    output.resize(length);

    auto halfSize = HALF_SIZE;
    for (int i = 0; i < length; i += dimension) {
        output[i] = halfSize * input[i] / 180;
        auto y = RADIUS * std::log(std::tan(M_PI * (input[i + 1] + 90) / 360));
        if (y > halfSize) {
            y = halfSize;
        } else if (y < -halfSize) {
            y = -halfSize;
        }
        output[i + 1] = y;
    }
    return output;
}

}
}
}

#include "epsg4326.h"

namespace ol {
namespace proj {
namespace epsg4326 {

const ol::extent::Extent EXTENT = { -180, -90, 180, 90 };

const std::vector<ProjectionP> PROJECTIONS = {
        ProjectionP(new EPSG4326Projection("CRS:84")),
        ProjectionP(new EPSG4326Projection("EPSG:4326", "neu")),
        ProjectionP(new EPSG4326Projection("urn:ogc:def:crs:EPSG::4326", "neu")),
        ProjectionP(new EPSG4326Projection("urn:ogc:def:crs:EPSG:6.6:4326", "neu")),
        ProjectionP(new EPSG4326Projection("urn:ogc:def:crs:OGC:1.3:CRS84")),
        ProjectionP(new EPSG4326Projection("urn:ogc:def:crs:OGC:2:84")),
        ProjectionP(new EPSG4326Projection("http://www.opengis.net/gml/srs/epsg.xml#4326", "neu")),
        ProjectionP(new EPSG4326Projection("urn:x-ogc:def:crs:EPSG:4326", "neu"))
};


}
}
}
