#ifndef OL_PROJ_EPSG4326_H
#define OL_PROJ_EPSG4326_H

///**
// * @module ol/proj/epsg4326
// */
//import {inherits} from '../util.js';
#include "../util.h"
//import Projection from '../proj/Projection.js';
#include "../proj/Projection.h"
//import Units from '../proj/Units.js';
#include "../proj/Units.h"
//

#include "../math_pi.h"

namespace ol {
namespace proj {
namespace epsg4326 {

/**
 * Semi-major radius of the WGS84 ellipsoid.
 *
 * @const
 * @type {number}
 */
const ol::number_t RADIUS = 6378137;

/**
 * Extent of the EPSG:4326 projection which is the whole world.
 *
 * @const
 * @type {module:ol/extent~Extent}
 */
extern const ol::extent::Extent EXTENT; // = [-180, -90, 180, 90];


/**
 * @const
 * @type {number}
 */
const ol::number_t METERS_PER_UNIT = M_PI * RADIUS / 180.0;

/**
 * @classdesc
 * Projection object for WGS84 geographic coordinates (EPSG:4326).
 *
 * Note that OpenLayers does not strictly comply with the EPSG definition.
 * The EPSG registry defines 4326 as a CRS for Latitude,Longitude (y,x).
 * OpenLayers treats EPSG:4326 as a pseudo-projection, with x,y coordinates.
 *
 * @constructor
 * @extends {module:ol/proj/Projection}
 * @param {string} code Code.
 * @param {string=} opt_axisOrientation Axis orientation.
 */
class EPSG4326Projection : public Projection {
public:
    //function EPSG4326Projection(code, opt_axisOrientation) {
    //  Projection.call(this, {
    //    code: code,
    //    units: Units.DEGREES,
    //    extent: EXTENT,
    //    axisOrientation: opt_axisOrientation,
    //    global: true,
    //    metersPerUnit: METERS_PER_UNIT,
    //    worldExtent: EXTENT
    //  });
    //}

    struct Options : public Projection::Options {
        Options(std::string _code, std::string _axis)
        {
            code = _code;
            axisOrientation = _axis;
            units = Units::DEGREES;
            extent = EXTENT;
            global = true;
            metersPerUnit = METERS_PER_UNIT;
            worldExtent = EXTENT;
        }
    };

    EPSG4326Projection(std::string code, std::string opt_axisOrientation = std::string())
        : Projection(Options(code, opt_axisOrientation)) {}
    //inherits(EPSG4326Projection, Projection);
};

/**
 * Projections equal to EPSG:4326.
 *
 * @const
 * @type {Array.<module:ol/proj/Projection>}
 */
extern const std::vector<ProjectionP> PROJECTIONS;
//= [
//  new EPSG4326Projection('CRS:84'),
//  new EPSG4326Projection('EPSG:4326', 'neu'),
//  new EPSG4326Projection('urn:ogc:def:crs:EPSG::4326', 'neu'),
//  new EPSG4326Projection('urn:ogc:def:crs:EPSG:6.6:4326', 'neu'),
//  new EPSG4326Projection('urn:ogc:def:crs:OGC:1.3:CRS84'),
//  new EPSG4326Projection('urn:ogc:def:crs:OGC:2:84'),
//  new EPSG4326Projection('http://www.opengis.net/gml/srs/epsg.xml#4326', 'neu'),
//  new EPSG4326Projection('urn:x-ogc:def:crs:EPSG:4326', 'neu')
//];
}
}
}
#endif
