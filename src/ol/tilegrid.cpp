/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "tilegrid.h"



ol::tilegrid::TileGrid ol::tilegrid::createForExtent(ol::extent::Extent const &extent, int opt_maxZoom /*= DEFAULT_MAX_ZOOM*/, number_t opt_tileSize /*= DEFAULT_TILE_SIZE*/, std::string opt_corner /*= "top-left"*/)
{
    auto resolutions = resolutionsFromExtent(extent, opt_maxZoom, opt_tileSize);

    TileGrid::Options opt; {
        opt.extent = extent;
        opt.origin = ol::extent::getCorner(extent, opt_corner);
        opt.resolutions = resolutions;
        opt.tileSize = { opt_tileSize, opt_tileSize };
    }

    return TileGrid(opt);
}

ol::tilegrid::TileGrid ol::tilegrid::createForProjection(ol::proj::ProjectionLike projection, int opt_maxZoom /*= DEFAULT_MAX_ZOOM*/, int opt_tileSize /*= DEFAULT_TILE_SIZE*/, std::string const &opt_corner /*= ol::extent::Corner::TOP_LEFT /*"top-left"*/)
{
    auto extent = extentFromProjection(projection);
    return createForExtent(extent, opt_maxZoom, opt_tileSize, opt_corner);
}
