#ifndef OL_TILERANGE_H
#define OL_TILERANGE_H

#include "jsport.h"
#include "tilecoord.h"
#include "size.h"

#include "dll_export.h"

namespace ol {

/**
 * @module ol/TileRange
 */
/**
 * A representation of a contiguous block of tiles.  A tile range is specified
 * by its min/max tile coordinates and is inclusive of coordinates.
 *
 * @constructor
 * @param {number} minX Minimum X.
 * @param {number} maxX Maximum X.
 * @param {number} minY Minimum Y.
 * @param {number} maxY Maximum Y.
 * @struct
 */
class OLQT_EXPORT TileRange {
public:
    number_t minX;
    number_t maxX;
    number_t minY;
    number_t maxY;

    TileRange(number_t minX, number_t maxX, number_t minY, number_t maxY)
        : minX(minX), maxX(maxX), minY(minY), maxY(maxY)
    {
    }
    
    
    /**
     * @param {number} minX Minimum X.
     * @param {number} maxX Maximum X.
     * @param {number} minY Minimum Y.
     * @param {number} maxY Maximum Y.
     * @param {module:ol/TileRange=} tileRange TileRange.
     * @return {module:ol/TileRange} Tile range.
     */
    //export function createOrUpdate(minX, maxX, minY, maxY, tileRange) {
    //  if (tileRange !== undefined) {
    //    tileRange.minX = minX;
    //    tileRange.maxX = maxX;
    //    tileRange.minY = minY;
    //    tileRange.maxY = maxY;
    //    return tileRange;
    //  } else {
    //    return new TileRange(minX, maxX, minY, maxY);
    //  }
    //}
    static TileRange createOrUpdate(number_t minX, number_t maxX, number_t minY, number_t maxY)
    {
        return TileRange(minX, maxX, minY, maxY);
    }

    static TileRange &createOrUpdate(number_t minX, number_t maxX, number_t minY, number_t maxY, TileRange &tileRange)
    {
        tileRange.minX = minX;
        tileRange.maxX = maxX;
        tileRange.minY = minY;
        tileRange.maxY = maxY;
        return tileRange;
    }
    
    
    /**
     * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
     * @return {boolean} Contains tile coordinate.
     */
    bool contains(ol::tilecoord::TileCoord const &tileCoord) const
    {
        return containsXY(tileCoord[1], tileCoord[2]);
    };
    
    
    /**
     * @param {module:ol/TileRange} tileRange Tile range.
     * @return {boolean} Contains.
     */
    bool containsTileRange (TileRange const &tileRange) const
    {
      return minX <= tileRange.minX && tileRange.maxX <= maxX &&
          minY <= tileRange.minY && tileRange.maxY <= maxY;
    };
    
    
    /**
     * @param {number} x Tile coordinate x.
     * @param {number} y Tile coordinate y.
     * @return {boolean} Contains coordinate.
     */
    bool containsXY (number_t x, number_t y) const
    {
      return minX <= x && x <= maxX && minY <= y && y <= maxY;
    };
    
    
    /**
     * @param {module:ol/TileRange} tileRange Tile range.
     * @return {boolean} Equals.
     */
    bool equals(TileRange const &tileRange) const
    {
        return minX == tileRange.minX && minY == tileRange.minY &&
            maxX == tileRange.maxX && maxY == tileRange.maxY;
    }
    
    
    /**
     * @param {module:ol/TileRange} tileRange Tile range.
     */
    void extend(TileRange const &tileRange) {
        if (tileRange.minX < minX) {
            minX = tileRange.minX;
        }
        if (tileRange.maxX > maxX) {
            maxX = tileRange.maxX;
        }
        if (tileRange.minY < minY) {
            minY = tileRange.minY;
        }
        if (tileRange.maxY > maxY) {
            maxY = tileRange.maxY;
        }
    }
    
    
    /**
     * @return {number} Height.
     */
    number_t getHeight() const
    {
        return maxY - minY + 1;
    }

    /**
     * @return {module:ol/size~Size} Size.
     */
    ol::size::Size getSize ()
    {
        return ol::size::Size({ getWidth(), getHeight() });
    }

    /**
     * @return {number} Width.
     */
    number_t getWidth() const 
    {
        return maxX - minX + 1;
    }
    
    
    /**
     * @param {module:ol/TileRange} tileRange Tile range.
     * @return {boolean} Intersects.
     */
    bool intersects(TileRange const &tileRange) const
    {
        return minX <= tileRange.maxX &&
            maxX >= tileRange.minX &&
            minY <= tileRange.maxY &&
            maxY >= tileRange.minY;
    }
};
//export default TileRange;
}
#endif // OL_TILERANGE_H
