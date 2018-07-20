#ifndef OL_PROJ_EPSG3857_H
#define OL_PROJ_EPSG3857_H

#include "../jsport.h"

/**
 * @module ol/proj/epsg3857
 */

//import {inherits} from '../util.js';
#include "../util.h"
//import {cosh} from '../math.js';
#include "../math.h"
#include "../math_pi.h"
//import Projection from '../proj/Projection.js';
#include "../proj/Projection.h"
//import Units from '../proj/Units.js';
#include "../proj/Units.h"

#include "../dll_export.h"
#include "projections.h"
#include "../extent.h"

namespace ol {
namespace proj {
namespace epsg3857 {


/**
 * Radius of WGS84 sphere
 *
 * @const
 * @type {number}
 */
const number_t RADIUS = 6378137;

/**
 * @const
 * @type {number}
 */
const number_t HALF_SIZE = M_PI * RADIUS;

/**
 * @const
 * @type {module:ol/extent~Extent}
 */
extern const extent::Extent EXTENT;
// = [
//  -HALF_SIZE, -HALF_SIZE,
//  HALF_SIZE, HALF_SIZE
//];

/**
 * @const
 * @type {module:ol/extent~Extent}
 */
extern const extent::Extent WORLD_EXTENT;
// = [-180, -85, 180, 85];

struct Options3857 : public ::ol::proj::Projection::Options {
    Options3857(std::string const &_code)
    {
        // {
        //  code: code,
        //  units : Units.METERS,
        //  extent : EXTENT,
        //  global : true,
        //  worldExtent : WORLD_EXTENT,
        //  getPointResolution : function(resolution, point) {
        //    return resolution / cosh(point[1] / RADIUS);
        //  }

        this->code = _code;
        this->units = Units::METERS;
        this->extent = EXTENT;
        this->global = true;
        this->worldExtent = WORLD_EXTENT;
    }
};

/**
 * @classdesc
 * Projection object for web/spherical Mercator (EPSG:3857).
 *
 * @constructor
 * @extends {module:ol/proj/Projection}
 * @param {string} code Code.
 */
class OLQT_EXPORT EPSG3857Projection : public Projection {
public:
    EPSG3857Projection(std::string const &code) 
        : Projection(Options3857(code))
    {
    }

    virtual optional<number_t> getPointResolution(number_t resolution, ol::coordinate::Coordinate const &point) const override
    {
        return resolution / std::cosh(point[1] / RADIUS);
    }
};
//inherits(EPSG3857Projection, Projection);

/**
 * Projections equal to EPSG:3857.
 *
 * @const
 * @type {Array.<module:ol/proj/Projection>}
 */

extern std::vector<ol::proj::ProjectionP> PROJECTIONS;
//= [
//  new EPSG3857Projection('EPSG:3857'),
//  new EPSG3857Projection('EPSG:102100'),
//  new EPSG3857Projection('EPSG:102113'),
//  new EPSG3857Projection('EPSG:900913'),
//  new EPSG3857Projection('urn:ogc:def:crs:EPSG:6.18:3:3857'),
//  new EPSG3857Projection('urn:ogc:def:crs:EPSG::3857'),
//  new EPSG3857Projection('http://www.opengis.net/gml/srs/epsg.xml#3857')
//];


/**
 * Transformation from EPSG:4326 to EPSG:3857.
 *
 * @param {Array.<number>} input Input array of coordinate values.
 * @param {Array.<number>=} opt_output Output array of coordinate values.
 * @param {number=} opt_dimension Dimension (default is `2`).
 * @return {Array.<number>} Output array of coordinate values.
 */
OLQT_EXPORT std::vector<number_t> &fromEPSG4326(std::vector<number_t> const &input, std::vector<number_t> &output, int opt_dimension = 2);

inline std::vector<number_t> fromEPSG4326(std::vector<number_t> const &input)
{
    std::vector<number_t> r;
    fromEPSG4326(input, r, 2);

    return r;
}

//
///**
// * Transformation from EPSG:3857 to EPSG:4326.
// *
// * @param {Array.<number>} input Input array of coordinate values.
// * @param {Array.<number>=} opt_output Output array of coordinate values.
// * @param {number=} opt_dimension Dimension (default is `2`).
// * @return {Array.<number>} Output array of coordinate values.
// */
//export function toEPSG4326(input, opt_output, opt_dimension) {
//  const length = input.length;
//  const dimension = opt_dimension > 1 ? opt_dimension : 2;
//  let output = opt_output;
//  if (output === undefined) {
//    if (dimension > 2) {
//      // preserve values beyond second dimension
//      output = input.slice();
//    } else {
//      output = new Array(length);
//    }
//  }
//  for (let i = 0; i < length; i += dimension) {
//    output[i] = 180 * input[i] / HALF_SIZE;
//    output[i + 1] = 360 * Math.atan(
//      Math.exp(input[i + 1] / RADIUS)) / Math.PI - 90;
//  }
//  return output;
//}
}
}
}
#endif // OL_PROJ_EPSG3857_H
