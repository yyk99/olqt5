#ifndef OL_PROJ_TRANSFORM_H
#define OL_PROJ_TRANSFORM_H

#include "../dll_export.h"
#include "../proj.h"

#include "projections.h"

#include <map>

///**
// * @module ol/proj/transforms
// */
//import {isEmpty} from '../obj.js';
#include "../obj.h"

namespace ol {
namespace proj {
struct OLQT_EXPORT transforms {
    /**
     * @private
     * @type {!Object.<string, Object.<string, module:ol/proj~TransformFunction>>}
     */
    static std::map<std::string, ol::proj::TransformFunction> transforms_cache;

    /**
     * Clear the transform cache.
     */
    static void clear()
    {
        transforms_cache.clear();
    }


    /**
     * Registers a conversion function to convert coordinates from the source
     * projection to the destination projection.
     *
     * @param {module:ol/proj/Projection} source Source.
     * @param {module:ol/proj/Projection} destination Destination.
     * @param {module:ol/proj~TransformFunction} transformFn Transform.
     */
    static void add(ProjectionP source, ProjectionP destination, void * transformFn)
    {
        auto sourceCode = source->getCode();
        auto destinationCode = destination->getCode();

        // TODO: implement

        //if (!(sourceCode in transforms)) {
        //    transforms[sourceCode] = {};
        //}
        //transforms[sourceCode][destinationCode] = transformFn;
    }


    /**
     * Unregisters the conversion function to convert coordinates from the source
     * projection to the destination projection.  This method is used to clean up
     * cached transforms during testing.
     *
     * @param {module:ol/proj/Projection} source Source projection.
     * @param {module:ol/proj/Projection} destination Destination projection.
     * @return {module:ol/proj~TransformFunction} transformFn The unregistered transform.
     */
    static ol::proj::TransformFunction remove(ol::proj::ProjectionP source, ol::proj::ProjectionP destination)
    {
        ol::proj::TransformFunction transform = ol::proj::TransformFunction();
        // TODO: implement
        //const sourceCode = source.getCode();
        //const destinationCode = destination.getCode();
        //transform = transforms_cache[sourceCode][destinationCode];
        //delete transforms[sourceCode][destinationCode];
        //if (isEmpty(transforms[sourceCode])) {
        //    delete transforms[sourceCode];
        //}
        return transform;
    }

    /**
    * Get a transform given a source code and a destination code.
    * @param {string} sourceCode The code for the source projection.
    * @param {string} destinationCode The code for the destination projection.
    * @return {module:ol/proj~TransformFunction|undefined} The transform function (if found).
    */
    static ol::proj::TransformFunction get(std::string const &sourceCode, std::string const &destinationCode) 
    {
        ol::proj::TransformFunction transform = ol::proj::TransformFunction();
        // TODO: implement
        //if (sourceCode in transforms && destinationCode in transforms[sourceCode]) {
        //    transform = transforms[sourceCode][destinationCode];
        //}
        return transform;
    }

    static ol::proj::TransformFunction get(ProjectionP src, ProjectionP dst)
    {
        return get(src->getCode(), dst->getCode());
    }
}; // struct
}
}
#endif
