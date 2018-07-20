//
//
//

#include "proj.h"

//import {toEPSG4326, fromEPSG4326, PROJECTIONS as EPSG3857_PROJECTIONS} from './proj/epsg3857.js';"
#include "./proj/epsg3857.h"
//import {PROJECTIONS as EPSG4326_PROJECTIONS} from './proj/epsg4326.js';
#include "./proj/epsg4326.h"

namespace ol {
namespace proj {

/**
* @param {Array.<number>} input Input coordinate array.
* @param {Array.<number>=} opt_output Output array of coordinate values.
* @param {number=} opt_dimension Dimension.
* @return {Array.<number>} Output coordinate array (new array, same coordinate
*     values).
*/
class OLQT_EXPORT  CloneTransform : public TransformFunctionObj {
public:
    std::vector<ol::number_t> & operator ()(
        std::vector<ol::number_t> const &input,
        std::vector<ol::number_t> &opt_output,
        size_t opt_dimension) override;
};

CloneTransform cloneTransform;

/**
* @param {Array.<number>} input Input coordinate array.
* @param {Array.<number>=} opt_output Output array of coordinate values.
* @param {number=} opt_dimension Dimension.
* @return {Array.<number>} Input coordinate array (same array as input).
*/
class OLQT_EXPORT IdentityTransform : public TransformFunctionObj {
public:
    virtual std::vector<ol::number_t> & operator () (
        std::vector<ol::number_t> const &input,
        std::vector<ol::number_t> &opt_output,
        size_t opt_dimension) override;
};

class IdentityTransform identityTransform;

}
}

/**
* @param {Array.<number>} input Input coordinate array.
* @param {Array.<number>=} opt_output Output array of coordinate values.
* @param {number=} opt_dimension Dimension.
* @return {Array.<number>} Output coordinate array (new array, same coordinate
*     values).
*/
std::vector<ol::number_t> &ol::proj::CloneTransform::operator()(std::vector<ol::number_t> const & input, std::vector<ol::number_t>& opt_output, size_t opt_dimension)
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
* @param {Array.<number>} input Input coordinate array.
* @param {Array.<number>=} opt_output Output array of coordinate values.
* @param {number=} opt_dimension Dimension.
* @return {Array.<number>} Input coordinate array (same array as input).
*/
std::vector<ol::number_t> &ol::proj::IdentityTransform::operator()(std::vector<ol::number_t> const &input, std::vector<ol::number_t> &opt_output, size_t opt_dimension)
{
    if (input != opt_output) {
        opt_output.resize(input.size());
        for (int i = 0 ; i != input.size() ; ++i) {
            opt_output[i] = input[i];
        }
    }
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
    ol::proj::transforms::add/*TransformFunc*/(projection, projection, &cloneTransform);
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
* Fetches a Projection object for the code specified.
*
* @param {module:ol/proj~ProjectionLike} projectionLike Either a code string which is
*     a combination of authority and identifier such as "EPSG:4326", or an
*     existing projection object, or undefined.
* @return {module:ol/proj/Projection} Projection object, or null if not in list.
* @api
*/
ol::proj::ProjectionP ol::proj::get(ProjectionLike projectionLike)
{
#if 0
    let projection = null;
    if (projectionLike instanceof Projection) {
        projection = projectionLike;
    } else if (typeof projectionLike == = 'string') {
        const code = projectionLike;
        projection = projections.get(code);
    }
    return projection;
#endif
    return projections::get(projectionLike);
}



/**
* Get the resolution of the point in degrees or distance units.
* For projections with degrees as the unit this will simply return the
* provided resolution. For other projections the point resolution is
* by default estimated by transforming the 'point' pixel to EPSG:4326,
* measuring its width and height on the normal sphere,
* and taking the average of the width and height.
* A custom function can be provided for a specific projection, either
* by setting the `getPointResolution` option in the
* {@link module:ol/proj/Projection~Projection} constructor or by using
* {@link module:ol/proj/Projection~Projection#setGetPointResolution} to change an existing
* projection object.
* @param {module:ol/proj~ProjectionLike} projection The projection.
* @param {number} resolution Nominal resolution in projection units.
* @param {module:ol/coordinate~Coordinate} point Point to find adjusted resolution at.
* @param {module:ol/proj/Units=} opt_units Units to get the point resolution in.
* Default is the projection's units.
* @return {number} Point resolution.
* @api
*/
ol::number_t ol::proj::getPointResolution(ProjectionP projection, number_t resolution, ol::coordinate::Coordinate const & point)
{
#if 1
    return projection->getPointResolution(resolution, point).value();
#else
    projection = get(projection);
    let pointResolution;
    const getter = projection.getPointResolutionFunc();
    if (getter) {
        pointResolution = getter(resolution, point);
    } else {
        const units = projection.getUnits();
        if (units == Units.DEGREES && !opt_units || opt_units == Units.DEGREES) {
            pointResolution = resolution;
        } else {
            // Estimate point resolution by transforming the center pixel to EPSG:4326,
            // measuring its width and height on the normal sphere, and taking the
            // average of the width and height.
            const toEPSG4326 = getTransformFromProjections(projection, get('EPSG:4326'));
            let vertices = [
                point[0] - resolution / 2, point[1],
                    point[0] + resolution / 2, point[1],
                    point[0], point[1] - resolution / 2,
                    point[0], point[1] + resolution / 2
            ];
            vertices = toEPSG4326(vertices, vertices, 2);
            const width = getDistance(vertices.slice(0, 2), vertices.slice(2, 4));
            const height = getDistance(vertices.slice(4, 6), vertices.slice(6, 8));
            pointResolution = (width + height) / 2;
            const metersPerUnit = opt_units ?
                METERS_PER_UNIT[opt_units] :
                projection.getMetersPerUnit();
            if (metersPerUnit != = undefined) {
                pointResolution /= metersPerUnit;
            }
        }
    }
    return pointResolution;
#endif
}

/**
* Registers transformation functions that don't alter coordinates. Those allow
* to transform between projections with equal meaning.
*
* @param {Array.<module:ol/proj/Projection>} projections Projections.
* @api
*/
void ol::proj::addEquivalentProjections(std::vector<ProjectionP> const & projections)
{
    addProjections(projections);
    for (auto source : projections) {
        for (auto destination : projections) {
            if (source != destination) {
                transforms::add/*addTransformFunc*/(source, destination, &cloneTransform);
            }
        }
    }
}

/**
* Registers transformation functions to convert coordinates in any projection
* in projection1 to any projection in projection2.
*
* @param {Array.<module:ol/proj/Projection>} projections1 Projections with equal
*     meaning.
* @param {Array.<module:ol/proj/Projection>} projections2 Projections with equal
*     meaning.
* @param {module:ol/proj~TransformFunction} forwardTransform Transformation from any
*   projection in projection1 to any projection in projection2.
* @param {module:ol/proj~TransformFunction} inverseTransform Transform from any projection
*   in projection2 to any projection in projection1..
*/
void ol::proj::addEquivalentTransforms(std::vector<ProjectionP> const & projections1, std::vector<ProjectionP> const & projections2, ol::proj::TransformFunction forwardTransform, ol::proj::TransformFunction inverseTransform)
{
    for (auto projection1 : projections1) {
        for (auto projection2 : projections2) {
            transforms::add(projection1, projection2, forwardTransform);
            transforms::add(projection2, projection1, inverseTransform);
        }
    }
}

/**
* Clear all cached projections and transforms.
*/
void ol::proj::clearAllProjections()
{
    projections::clear();
    transforms::clear();
}


/**
* Searches in the list of transform functions for the function for converting
* coordinates from the source projection to the destination projection.
*
* @param {module:ol/proj/Projection} sourceProjection Source Projection object.
* @param {module:ol/proj/Projection} destinationProjection Destination Projection
*     object.
* @return {module:ol/proj~TransformFunction} Transform function.
*/
ol::proj::TransformFunction ol::proj::getTransformFromProjections(ProjectionP sourceProjection, ProjectionP destinationProjection)
{
    auto sourceCode = sourceProjection->getCode();
    auto destinationCode = destinationProjection->getCode();

    TransformFunction transformFunc = transforms::get(sourceCode, destinationCode);
    if (!transformFunc) {
        transformFunc = &identityTransform;
    }

    return transformFunc;
}

ol::coordinate::Coordinate ol::proj::transform(ol::coordinate::Coordinate const &coordinate, ProjectionP source, ProjectionP destination)
{
    auto transformFunc = ol::proj::transforms::get/*Transform*/(source, destination);
    ol::coordinate::Coordinate tmp;
    (*transformFunc)(coordinate, tmp, coordinate.size());

    return tmp;
}

/**
* Add transforms to and from EPSG:4326 and EPSG:3857.  This function is called
* by when this module is executed and should only need to be called again after
* `clearAllProjections()` is called (e.g. in tests).
*/
void ol::proj::addCommon() 
{
    // Add transformations that don't alter coordinates to convert within set of
    // projections with equal meaning.
    addEquivalentProjections(ol::proj::epsg3857::PROJECTIONS /*EPSG3857_PROJECTIONS*/);
    addEquivalentProjections(ol::proj::epsg4326::PROJECTIONS /*EPSG4326_PROJECTIONS*/);
    // Add transformations to convert EPSG:4326 like coordinates to EPSG:3857 like
    // coordinates and back.
    addEquivalentTransforms(ol::proj::epsg4326::PROJECTIONS, ol::proj::epsg3857::PROJECTIONS, 0 /*fromEPSG4326*/, 0 /*toEPSG4326*/);
}
