/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "extent.h"

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
