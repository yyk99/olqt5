/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "extent.h"

#include <algorithm>

ol::extent::Extent & ol::extent::_boundingExtentXYs(std::vector<number_t> const &xs, std::vector<number_t> const &ys, Extent &opt_extent)
{
    number_t minX = *std::min_element(xs.begin(), xs.end());
    number_t minY = *std::min_element(ys.begin(), ys.end());
    number_t maxX = *std::max_element(xs.begin(), xs.end());
    number_t maxY = *std::max_element(ys.begin(), ys.end());

    return createOrUpdate(minX, minY, maxX, maxY, opt_extent);
}

ol::coordinate::Coordinate ol::extent::getCorner(Extent const &extent, std::string const &corner)
{
    if (corner == Corner::BOTTOM_LEFT)
        return getBottomLeft(extent);
    if (corner == Corner::BOTTOM_RIGHT)
        return getBottomRight(extent);
    if (corner == Corner::TOP_LEFT)
        return getTopLeft(extent);
    if (corner == Corner::TOP_RIGHT)
        return getTopRight(extent);

    ol::asserts::Assert(false, 13); // Invalid corner
    return ol::coordinate::Coordinate(); // never here
}

/**
* Apply a transform function to the extent.
* @param {module:ol/extent~Extent} extent Extent.
* @param {module:ol/proj~TransformFunction} transformFn Transform function.
* Called with `[minX, minY, maxX, maxY]` extent coordinates.
* @param {module:ol/extent~Extent=} opt_extent Destination extent.
* @return {module:ol/extent~Extent} Extent.
* @api
*/
OLQT_EXPORT ol::extent::Extent & ol::extent::applyTransform(Extent const & extent, ol::proj::TransformFunction transformFn, Extent & opt_extent)
{
    std::vector<ol::number_t> coordinates = {
        extent[0], extent[1],
        extent[0], extent[3],
        extent[2], extent[1],
        extent[2], extent[3]
    };
    (*transformFn)(coordinates, coordinates, 2);
    std::vector<ol::number_t>  xs = { coordinates[0], coordinates[2], coordinates[4], coordinates[6] };
    std::vector<ol::number_t> ys = { coordinates[1], coordinates[3], coordinates[5], coordinates[7] };
    return _boundingExtentXYs(xs, ys, opt_extent);
}
