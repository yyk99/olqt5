/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "TileGrid.h"

#include <cmath>

using namespace ol::tilecoord;
using namespace ol::tilegrid;

TileCoord TileGrid::getTileCoordForXYAndZ_(ol::number_t x, ol::number_t y, tilecoord_t z,
    bool reverseIntersectionPolicy) const
{
    auto origin = getOrigin(z);
    auto resolution = getResolution(z);
    auto tileSize = getTileSize(z);

    auto adjustX = reverseIntersectionPolicy ? 0.5 : 0;
    auto adjustY = reverseIntersectionPolicy ? 0 : 0.5;
    auto xFromOrigin = std::floor((x - origin[0]) / resolution + adjustX);
    auto yFromOrigin = std::floor((y - origin[1]) / resolution + adjustY);
    auto tileCoordX = xFromOrigin / tileSize[0];
    auto tileCoordY = yFromOrigin / tileSize[1];

    if (reverseIntersectionPolicy) {
        tileCoordX = std::ceil(tileCoordX) - 1;
        tileCoordY = std::ceil(tileCoordY) - 1;
    } else {
        tileCoordX = std::floor(tileCoordX);
        tileCoordY = std::floor(tileCoordY);
    }

    return ol::tilecoord::createOrUpdate(z, tilecoord_t(tileCoordX), tilecoord_t(tileCoordY));
}
