#ifndef OL_TILECOORD_H
#define OL_TILECOORD_H

/**
 * @module ol/tilecoord
 */


#include "jsport.h"

#include <vector>
#include <string>

#include "dll_export.h"

namespace ol {

namespace tilegrid {
class TileGrid;
}

namespace tilecoord {

/**
 * An array of three numbers representing the location of a tile in a tile
 * grid. The order is `z`, `x`, and `y`. `z` is the zoom level.
 * @typedef {Array.<number>} TileCoord
 * @api
 */

typedef int tilecoord_t;
typedef std::vector<tilecoord_t> TileCoord;


/**
 * @param {number} z Z.
 * @param {number} x X.
 * @param {number} y Y.
 * @param {module:ol/tilecoord~TileCoord=} opt_tileCoord Tile coordinate.
 * @return {module:ol/tilecoord~TileCoord} Tile coordinate.
 */
inline TileCoord createOrUpdate(tilecoord_t z, tilecoord_t x, tilecoord_t y)
{
    return TileCoord({ z, x, y });
}

inline TileCoord &createOrUpdate(tilecoord_t z, tilecoord_t x, tilecoord_t y, TileCoord &opt_tileCoord)
{
    opt_tileCoord[0] = z;
    opt_tileCoord[1] = x;
    opt_tileCoord[2] = y;

    return opt_tileCoord;
}

/**
 * @param {number} z Z.
 * @param {number} x X.
 * @param {number} y Y.
 * @return {string} Key.
 */
inline std::string getKeyZXY(tilecoord_t z, tilecoord_t x, tilecoord_t y)
{
    return std::to_string(z) + '/' + std::to_string(x) + '/' + std::to_string(y);
}

/**
 * Get the key for a tile coord.
 * @param {module:ol/tilecoord~TileCoord} tileCoord The tile coord.
 * @return {string} Key.
 */
inline std::string getKey(TileCoord const &tileCoord)
{
    return getKeyZXY(tileCoord[0], tileCoord[1], tileCoord[2]);
}


/**
 * Get a tile coord given a key.
 * @param {string} key The tile coord key.
 * @return {module:ol/tilecoord~TileCoord} The tile coord.
 */
OLQT_EXPORT TileCoord fromKey(std::string const &key);

/**
 * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coord.
 * @return {number} Hash.
 */
inline ol::number_t hash(TileCoord const &tileCoord) 
{
    return (int(tileCoord[1]) << int(tileCoord[0])) + tileCoord[2];
}


/**
 * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coord.
 * @return {string} Quad key.
 */
OLQT_EXPORT std::string  quadKey(TileCoord const &tileCoord);

/**
 * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
 * @param {!module:ol/tilegrid/TileGrid} tileGrid Tile grid.
 * @return {boolean} Tile coordinate is within extent and zoom level range.
 */
OLQT_EXPORT bool withinExtentAndZ(TileCoord const &tileCoord, ol::tilegrid::TileGrid const &tileGrid);

}
}
#endif
