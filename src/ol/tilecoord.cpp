/*
 * Copyright (C) 2018
 * All rights reserved.
 *
 */

#include "tilecoord.h"
#include "./string.h"
#include "tilegrid/TileGrid.h"

 /**
 * Get a tile coord given a key.
 * @param {string} key The tile coord key.
 * @return {module:ol/tilecoord~TileCoord} The tile coord.
 */
ol::tilecoord::TileCoord ol::tilecoord::fromKey(std::string const & key)
{
    TileCoord r;

    for (auto &s : ol::string::split(key, "/"))
        r.push_back(strtol(s.c_str(), 0, 10));

    return r;
}

std::string ol::tilecoord::quadKey(ol::tilecoord::TileCoord const &tileCoord)
{
    unsigned int z = (unsigned int)tileCoord[0];
    std::string digits = "";
    unsigned int mask = 1 << (z - 1);
    for (unsigned int i = 0; i < z; ++i) {
        // 48 is charCode for 0 - '0'.charCodeAt(0)
        char charCode = '0';
        if ((unsigned int)tileCoord[1] & mask) {
            charCode += 1;
        }
        if ((unsigned int)tileCoord[2] & mask) {
            charCode += 2;
        }
        digits += charCode;
        mask >>= 1;
    }
    return digits;
}

/**
* @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
* @param {!module:ol/tilegrid/TileGrid} tileGrid Tile grid.
* @return {boolean} Tile coordinate is within extent and zoom level range.
*/
bool ol::tilecoord::withinExtentAndZ(ol::tilecoord::TileCoord const & tileCoord, ol::tilegrid::TileGrid const & tileGrid)
{
    auto z = tileCoord[0];
    auto x = tileCoord[1];
    auto y = tileCoord[2];

    if (tileGrid.getMinZoom() > z || z > tileGrid.getMaxZoom()) {
        return false;
    }
    auto extent = tileGrid.getExtent();
    ol::TileRange tileRange;
    if (!extent.size()) {
        tileRange = tileGrid.getFullTileRange(z);
    } else {
        tileRange = tileGrid.getTileRangeForExtentAndZ(extent, z);
    }
    if (tileRange.empty()) {
        return true;
    } else {
        return tileRange.containsXY(x, y);
    }
}

