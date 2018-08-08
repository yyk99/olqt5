#ifndef OL_PROJ_PROJ4_H
#define OL_PROJ_PROJ4_H

/**
 * @module ol/proj/proj4
 */
//import {addCoordinateTransforms, addProjection, addEquivalentProjections, get} from '../proj.js';
#include "../proj.h"
//import {get as getTransform} from './transforms.js';
#include "./transforms.h"
//import Projection from './Projection.js';
#include "./Projection.h"

#include "../optional.h"
#include "../dll_export.h"

namespace ol {
namespace proj {
namespace proj4 {


struct OLQT_EXPORT Proj4 {
    struct OLQT_EXPORT projection_def
    {
        std::string axis;
        std::string units;
        optional<number_t> to_meter;

        inline bool operator == (projection_def const &other) const {
            return axis == other.axis &&
                units == other.units &&
                to_meter == other.to_meter;
        }

        std::string orig_text;

        projection_def() {}
        projection_def(std::string const &text);
    };

    struct transform_def {
        void *forward;
        void *inverse;

        transform_def() : forward(), inverse() {}
    };

    struct defs_container {
        std::map<std::string, projection_def> _container;
        std::vector<std::string> keys() const
        {
            std::vector<std::string> r;
            for (auto const &p : _container)
                r.push_back(p.first);
            return r;
        }

        inline projection_def const & operator() (std::string const &key) const
        {
            return _container.at(key);
        }

        inline projection_def &operator() (std::string const &key)
        {
            return _container[key];
        }

        inline projection_def const &operator[] (std::string const &key) const
        {
            return operator()(key);
        }

        inline void erase(std::string const &key) {
            _container.erase(key);
        }

        // add definition
        inline void operator() (std::string const &key, std::string const &val)
        {
            _container[key] = val;
        }
    };

    defs_container defs;

    transform_def operator() (std::string const &c1, std::string const &c2) const
    {
        return transform_def();
    }

    /* constructor */
    Proj4();

    bool globals_done;
    /* create collection of the standard definitions */
    void globals();
};

/**
 * Make projections defined in proj4 (with `proj4.defs()`) available in
 * OpenLayers.
 *
 * This function should be called whenever changes are made to the proj4
 * registry, e.g. after calling `proj4.defs()`. Existing transforms will not be
 * modified by this function.
 *
 * @param {?} proj4 Proj4.
 * @api
 */
OLQT_EXPORT void  Register(Proj4 &proj4);

OLQT_EXPORT Proj4 proj4;

}
}
}
#endif // OL_PROJ_PROJ4_H