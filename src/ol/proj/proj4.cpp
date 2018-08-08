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

void ol::proj::proj4::Register(Proj4 &proj4)
{
    proj4.globals();

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

#include "../../proj_wrapper/proj_wrapper.h"

static ol::pj::Proj4 ctx4;

ol::proj::proj4::Proj4::projection_def::projection_def(std::string const &text) : orig_text(text)
{
    auto def = ctx4.parse(text);
    auto props = ctx4.properties(def);

    for (auto &p : props) {
        if (p.first == "to_meter")
            to_meter = strtod(p.second.c_str(), 0);
        else if (p.first == "units")
            units = p.second;
    }
}

ol::proj::proj4::Proj4::Proj4() : globals_done(false)
{
}

void ol::proj::proj4::Proj4::globals()
{
    if (globals_done)
        return;
    defs("EPSG:4326", "+title=WGS 84 (long/lat) +proj=longlat +ellps=WGS84 +datum=WGS84 +units=degrees");
    defs("EPSG:4269", "+title=NAD83 (long/lat) +proj=longlat +a=6378137.0 +b=6356752.31414036 +ellps=GRS80 +datum=NAD83 +units=degrees");
    defs("EPSG:3857", "+title=WGS 84 / Pseudo-Mercator +proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +no_defs");

    defs("WGS84") = defs["EPSG:4326"];
    defs("EPSG:3785") = defs["EPSG:3857"]; // maintain backward compat, official code is 3857
    defs("GOOGLE") = defs["EPSG:3857"];
    defs("EPSG:900913") = defs["EPSG:3857"];
    defs("EPSG:102113") = defs["EPSG:3857"];

    globals_done = true;
}
