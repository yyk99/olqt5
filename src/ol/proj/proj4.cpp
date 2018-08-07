/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "proj4.h"

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

void ol::proj::proj4::Register(Proj4 const & proj4)
{
    //const projCodes = Object.keys(proj4.defs);
    auto projCodes = proj4.defs.keys();
    auto len = projCodes.size();
    for (int i = 0; i < len; ++i) {
        auto code = projCodes[i];
        if (get(code) == 0) {
            auto def = proj4.defs(code);
            //addProjection(new Projection({
            //  code: code,
            //  axisOrientation: def.axis,
            //  metersPerUnit: def.to_meter,
            //  units: def.units
            //}));
            Projection::Options o;
            o.code = code;
            o.axisOrientation = def.axis;
            o.metersPerUnit = def.to_meter;
            o.units = def.units;

            addProjection(ProjectionP(new  Projection(o)));
        }
    }
    for (int i = 0; i < len; ++i) {
        auto code1 = projCodes[i];
        auto proj1 = get(code1);
        for (int j = 0; j < len; ++j) {
            auto code2 = projCodes[j];
            auto proj2 = get(code2);
            if (!getTransform(code1, code2)) {
                if (proj4.defs[code1] == proj4.defs[code2]) {
                    addEquivalentProjections({ proj1, proj2 });
                } else {
                    auto transform = proj4(code1, code2);
                    addCoordinateTransforms(proj1, proj2, transform.forward, transform.inverse);
                }
            }
        }
    }
}
