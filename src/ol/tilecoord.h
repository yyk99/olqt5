#ifndef OL_TILECOORD_H
#define OL_TILECOORD_H
///**
// * @module ol/tilecoord
// */
//

#include "jsport.h"

#include <vector>
#include <string>

#include "dll_export.h"

namespace ol {
namespace tilecoord {
//
///**
// * An array of three numbers representing the location of a tile in a tile
// * grid. The order is `z`, `x`, and `y`. `z` is the zoom level.
// * @typedef {Array.<number>} TileCoord
// * @api
// */

typedef std::vector<ol::number_t> TileCoord;

//
///**
// * @param {number} z Z.
// * @param {number} x X.
// * @param {number} y Y.
// * @param {module:ol/tilecoord~TileCoord=} opt_tileCoord Tile coordinate.
// * @return {module:ol/tilecoord~TileCoord} Tile coordinate.
// */
//export function createOrUpdate(z, x, y, opt_tileCoord) {
//  if (opt_tileCoord !== undefined) {
//    opt_tileCoord[0] = z;
//    opt_tileCoord[1] = x;
//    opt_tileCoord[2] = y;
//    return opt_tileCoord;
//  } else {
//    return [z, x, y];
//  }
//}


/**
 * @param {number} z Z.
 * @param {number} x X.
 * @param {number} y Y.
 * @return {string} Key.
 */
inline std::string getKeyZXY(ol::number_t z, ol::number_t x, ol::number_t y) {
  return std::to_string(z) + '/' + std::to_string(x) + '/' + std::to_string(y);
}

/**
 * Get the key for a tile coord.
 * @param {module:ol/tilecoord~TileCoord} tileCoord The tile coord.
 * @return {string} Key.
 */
inline std::string getKey(TileCoord const &tileCoord) {
  return getKeyZXY(tileCoord[0], tileCoord[1], tileCoord[2]);
}


///**
// * Get a tile coord given a key.
// * @param {string} key The tile coord key.
// * @return {module:ol/tilecoord~TileCoord} The tile coord.
// */
//export function fromKey(key) {
//  return key.split('/').map(Number);
//}
//
//
///**
// * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coord.
// * @return {number} Hash.
// */
//export function hash(tileCoord) {
//  return (tileCoord[1] << tileCoord[0]) + tileCoord[2];
//}
//
//
///**
// * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coord.
// * @return {string} Quad key.
// */
//export function quadKey(tileCoord) {
//  const z = tileCoord[0];
//  const digits = new Array(z);
//  let mask = 1 << (z - 1);
//  let i, charCode;
//  for (i = 0; i < z; ++i) {
//    // 48 is charCode for 0 - '0'.charCodeAt(0)
//    charCode = 48;
//    if (tileCoord[1] & mask) {
//      charCode += 1;
//    }
//    if (tileCoord[2] & mask) {
//      charCode += 2;
//    }
//    digits[i] = String.fromCharCode(charCode);
//    mask >>= 1;
//  }
//  return digits.join('');
//}
//
//
///**
// * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
// * @param {!module:ol/tilegrid/TileGrid} tileGrid Tile grid.
// * @return {boolean} Tile coordinate is within extent and zoom level range.
// */
//export function withinExtentAndZ(tileCoord, tileGrid) {
//  const z = tileCoord[0];
//  const x = tileCoord[1];
//  const y = tileCoord[2];
//
//  if (tileGrid.getMinZoom() > z || z > tileGrid.getMaxZoom()) {
//    return false;
//  }
//  const extent = tileGrid.getExtent();
//  let tileRange;
//  if (!extent) {
//    tileRange = tileGrid.getFullTileRange(z);
//  } else {
//    tileRange = tileGrid.getTileRangeForExtentAndZ(extent, z);
//  }
//  if (!tileRange) {
//    return true;
//  } else {
//    return tileRange.containsXY(x, y);
//  }
//}
}
}
#endif
