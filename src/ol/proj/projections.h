#ifndef OL_PROJ_PROJECTIONS_H
#define OL_PROJ_PROJECTIONS_H

/**
 * @module ol/proj/projections
 */

#include "Projection.h"

#include <map>
#include <memory>

namespace ol {
namespace proj {

struct OLQT_EXPORT projections 
{
    /**
     * @type {Object.<string, module:ol/proj/Projection>}
     */
    static std::map<std::string, ProjectionP> cache;

    /**
     * Clear the projections cache.
     */
    static void clear();


    /**
     * Get a cached projection by code.
     * @param {string} code The code for the projection.
     * @return {module:ol/proj/Projection} The projection (if cached).
     */
    static ProjectionP get(std::string const &code);


    /**
     * Add a projection to the cache.
     * @param {string} code The projection code.
     * @param {module:ol/proj/Projection} projection The projection to cache.
     */
    static void add(std::string const &code, ProjectionP projection);

};

}
}
#endif
