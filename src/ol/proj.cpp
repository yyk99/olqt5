//
//
//

#include "proj.h"

//import {toEPSG4326, fromEPSG4326, PROJECTIONS as EPSG3857_PROJECTIONS} from './proj/epsg3857.js';"
#include "./proj/epsg3857.h"
//import {PROJECTIONS as EPSG4326_PROJECTIONS} from './proj/epsg4326.js';
#include "./proj/epsg4326.h"

static ol::proj::once  _once;


/**
* @param {Array.<number>} input Input coordinate array.
* @param {Array.<number>=} opt_output Output array of coordinate values.
* @param {number=} opt_dimension Dimension.
* @return {Array.<number>} Output coordinate array (new array, same coordinate
*     values).
*/
std::vector<ol::number_t> &ol::proj::cloneTransform(std::vector<ol::number_t> const & input, std::vector<ol::number_t>& opt_output, number_t opt_dimension)
{
    //let output;
    //if (opt_output != = undefined) {
    //    for (let i = 0, ii = input.length; i < ii; ++i) {
    //        opt_output[i] = input[i];
    //    }
    //    output = opt_output;
    //} else {
    //    output = input.slice();
    //}
    return opt_output;
}

/**
* Add a Projection object to the list of supported projections that can be
* looked up by their code.
*
* @param {module:ol/proj/Projection} projection Projection instance.
* @api
*/
void ol::proj::addProjection(ProjectionP projection)
{
    projections::add(projection->getCode(), projection);
    ol::proj::transforms::add/*TransformFunc*/(projection, projection, cloneTransform);
}

/**
* @param {Array.<module:ol/proj/Projection>} projections Projections.
*/
void ol::proj::addProjections(std::vector<ProjectionP> const & projections)
{
    //projections.forEach(addProjection);
    for (auto p : projections)
        addProjection(p);
}

/**
* Add transforms to and from EPSG:4326 and EPSG:3857.  This function is called
* by when this module is executed and should only need to be called again after
* `clearAllProjections()` is called (e.g. in tests).
*/
void ol::proj::addCommon() {
    // Add transformations that don't alter coordinates to convert within set of
    // projections with equal meaning.
    addEquivalentProjections(ol::proj::epsg3857::PROJECTIONS /*EPSG3857_PROJECTIONS*/);
    addEquivalentProjections(ol::proj::epsg4326::PROJECTIONS /*EPSG4326_PROJECTIONS*/);
    // Add transformations to convert EPSG:4326 like coordinates to EPSG:3857 like
    // coordinates and back.
    addEquivalentTransforms(ol::proj::epsg4326::PROJECTIONS, ol::proj::epsg3857::PROJECTIONS, 0 /*fromEPSG4326*/, 0 /*toEPSG4326*/);
}
