#ifndef OL_TILEGRID_TILEGRID_H
#define OL_TILEGRID_TILEGRID_H

#include "../dll_export.h"
#include "../optional.h"
#include "../coordinate.h"

///**
// * @module ol/tilegrid/TileGrid
// */
//import {DEFAULT_TILE_SIZE} from './common.js';
#include "common.h"
//import {assert} from '../asserts.js';
#include "../asserts.h"
//import TileRange, {createOrUpdate as createOrUpdateTileRange} from '../TileRange.js';
#include "../TileRange.h"
//import {isSorted, linearFindNearest} from '../array.js';
#include "../array.h"
//import {createOrUpdate, getTopLeft} from '../extent.js';
#include "../extent.h"
//import {clamp} from '../math.js';
#include "../math.h"
//import {toSize} from '../size.js';
#include "../size.h"
//import {createOrUpdate as createOrUpdateTileCoord} from '../tilecoord.js';
#include "../tilecoord.h"

#include <algorithm>

namespace ol {
namespace tilegrid {

/**
 * @typedef {Object} Options
 * @property {module:ol/extent~Extent} [extent] Extent for the tile grid. No tiles outside this
 * extent will be requested by {@link module:ol/source/Tile} sources. When no `origin` or
 * `origins` are configured, the `origin` will be set to the top-left corner of the extent.
 * @property {number} [minZoom=0] Minimum zoom.
 * @property {module:ol/coordinate~Coordinate} [origin] The tile grid origin, i.e. where the `x`
 * and `y` axes meet (`[z, 0, 0]`). Tile coordinates increase left to right and upwards. If not
 * specified, `extent` or `origins` must be provided.
 * @property {Array.<module:ol/coordinate~Coordinate>} [origins] Tile grid origins, i.e. where
 * the `x` and `y` axes meet (`[z, 0, 0]`), for each zoom level. If given, the array length
 * should match the length of the `resolutions` array, i.e. each resolution can have a different
 * origin. Tile coordinates increase left to right and upwards. If not specified, `extent` or
 * `origin` must be provided.
 * @property {!Array.<number>} resolutions Resolutions. The array index of each resolution needs
 * to match the zoom level. This means that even if a `minZoom` is configured, the resolutions
 * array will have a length of `maxZoom + 1`.
 * @property {Array.<module:ol/size~Size>} [sizes] Sizes.
 * @property {number|module:ol/size~Size} [tileSize] Tile size.
 * Default is `[256, 256]`.
 * @property {Array.<module:ol/size~Size>} [tileSizes] Tile sizes. If given, the array length
 * should match the length of the `resolutions` array, i.e. each resolution can have a different
 * tile size.
 */


 /**
  * @classdesc
  * Base class for setting the grid pattern for sources accessing tiled-image
  * servers.
  *
  * @constructor
  * @param {module:ol/tilegrid/TileGrid~Options} options Tile grid options.
  * @struct
  * @api
  */

class OLQT_EXPORT TileGrid
{
private:
    ol::extent::Extent extent_;
    std::vector<number_t> resolutions_;
    ol::optional<number_t> zoomFactor_;
    ol::coordinate::Coordinate origin_;
    std::vector<ol::coordinate::Coordinate> origins_;
    std::vector<ol::size::Size> tileSizes_;
    ol::size::Size tileSize_;
    std::vector<ol::TileRange> fullTileRanges_;
protected:
    int minZoom;
    int maxZoom;
public:
    struct Options
    {
        optional<int> minZoom;
        std::vector<number_t> resolutions;
        std::vector<number_t> origin;
        std::vector<ol::coordinate::Coordinate> origins;
        ol::extent::Extent extent;
        ol::size::Size tileSize;
        std::vector<ol::size::Size> sizes;
        std::vector<ol::size::Size> tileSizes;
    };

    //const TileGrid = function(options) {
    TileGrid(Options const &options)
        : resolutions_(options.resolutions)
        , tmpTileCoord({0, 0, 0})
    {
        //
        //  /**
        //   * @protected
        //   * @type {number}
        //   */
        //  this.minZoom = options.minZoom !== undefined ? options.minZoom : 0;
        minZoom = options.minZoom.value_or(0);
        //
        //  /**
        //   * @private
        //   * @type {!Array.<number>}
        //   */
        //  this.resolutions_ = options.resolutions;
        //  assert(isSorted(this.resolutions_, function(a, b) {
        //    return b - a;
        //  }, true), 17); // `resolutions` must be sorted in descending order
        ol::asserts::Assert(ol::array::isSorted(resolutions_, [](auto a, auto b) { return b - a; }, true), 17);

        // check if we've got a consistent zoom factor and origin
        optional<ol::number_t> zoomFactor;
        if (options.origins.size() == 0) {
            for (int i = 0, ii = int(resolutions_.size() - 1); i < ii; ++i) {
                if (!zoomFactor.has_value()) {
                    zoomFactor = resolutions_[i] / resolutions_[i + 1];
                } else {
                    if (resolutions_[i] / resolutions_[i + 1] != zoomFactor.value()) {
                        zoomFactor.reset(); // = undefined;
                        break;
                    }
                }
            }
        }

        /**
         * @private
         * @type {number|undefined}
         */
        zoomFactor_ = zoomFactor;

        /**
         * @protected
         * @type {number}
         */
        maxZoom = int(resolutions_.size() - 1);

        /**
         * @private
         * @type {module:ol/coordinate~Coordinate}
         */
        origin_ = options.origin; // != = undefined ? options.origin : null;
        
        /**
        * @private
        * @type {Array.<module:ol/coordinate~Coordinate>}
        */
        //origins_ = null;
        if (options.origins.size() != 0) {
            origins_ = options.origins;
            ol::asserts::Assert(origins_.size() == resolutions_.size(),
                20); // Number of `origins` and `resolutions` must be equal
        }
        
        auto extent = options.extent;
        
        if (extent.size() &&
            !origin_.size() && !origins_.size()) {
            origin_ = ol::extent::getTopLeft(extent);
        }
        
        ol::asserts::Assert(
            (!origin_.size() && origins_.size()) || (origin_.size() && !origins_.size()),
            18); // Either `origin` or `origins` must be configured, never both
        
        /**
        * @private
        * @type {Array.<number|module:ol/size~Size>}
        */
        // this.tileSizes_ = null;
        if (options.tileSizes.size() /*!== undefined*/) {
            tileSizes_ = options.tileSizes;
            ol::asserts::Assert(tileSizes_.size() == resolutions_.size(),
                19); // Number of `tileSizes` and `resolutions` must be equal
        }

        /**
         * @private
         * @type {number|module:ol/size~Size}
         */
        tileSize_ = options.tileSize.size() /*!== undefined*/ ?
            options.tileSize :
            !tileSizes_.size() 
            ? ol::size::Size({ol::number_t(DEFAULT_TILE_SIZE), ol::number_t(DEFAULT_TILE_SIZE)}) 
            : ol::size::Size();
        ol::asserts::Assert(
            (!tileSize_.size() && tileSizes_.size()) ||
            (tileSize_.size() && !tileSizes_.size()),
            22); // Either `tileSize` or `tileSizes` must be configured, never both
        
        /**
        * @private
        * @type {module:ol/extent~Extent}
        */
        extent_ = extent;
        
        
        /**
        * @private
        * @type {Array.<module:ol/TileRange>}
        */
        // fullTileRanges_ = null;
        
        /**
        * @private
        * @type {module:ol/size~Size}
        */
        ol::size::Size tmpSize_ = { 0, 0 };
        
        if (options.sizes.size()) {
            //fullTileRanges_ = options.sizes.map(function(size, z) {
            //    const tileRange = new TileRange(
            //        Math.min(0, size[0]), Math.max(size[0] - 1, -1),
            //        Math.min(0, size[1]), Math.max(size[1] - 1, -1));
            //    return tileRange;
            //}, this);
            for (auto size : options.sizes)
                fullTileRanges_.push_back(TileRange(
                    std::min<number_t>(0, size[0]), std::max<number_t>(size[0] - 1, -1),
                    std::min<number_t>(0, size[1]), std::max<number_t>(size[1] - 1, -1)));
        } else if (extent.size()) {
            calculateTileRanges_(extent);
        }
    }
    
    /**
     * @private
     * @type {module:ol/tilecoord~TileCoord}
     */
    ol::tilecoord::TileCoord tmpTileCoord /*= [0, 0, 0]*/;
    
    
    /**
     * Call a function with each tile coordinate for a given extent and zoom level.
     *
     * @param {module:ol/extent~Extent} extent Extent.
     * @param {number} zoom Integer zoom level.
     * @param {function(module:ol/tilecoord~TileCoord)} callback Function called with each tile coordinate.
     * @api
     */
    template<typename Funct>
    void forEachTileCoord(ol::extent::Extent const &extent, ol::number_t zoom, Funct callback)
    {
        const tileRange = this.getTileRangeForExtentAndZ(extent, zoom);
        for (let i = tileRange.minX, ii = tileRange.maxX; i <= ii; ++i) {
            for (let j = tileRange.minY, jj = tileRange.maxY; j <= jj; ++j) {
                callback([zoom, i, j]);
            }
        }
    }
    //
    //
    ///**
    // * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
    // * @param {function(this: T, number, module:ol/TileRange): boolean} callback Callback.
    // * @param {T=} opt_this The object to use as `this` in `callback`.
    // * @param {module:ol/TileRange=} opt_tileRange Temporary module:ol/TileRange object.
    // * @param {module:ol/extent~Extent=} opt_extent Temporary module:ol/extent~Extent object.
    // * @return {boolean} Callback succeeded.
    // * @template T
    // */
    //TileGrid.prototype.forEachTileCoordParentTileRange = function(tileCoord, callback, opt_this, opt_tileRange, opt_extent) {
    //  let tileRange, x, y;
    //  let tileCoordExtent = null;
    //  let z = tileCoord[0] - 1;
    //  if (this.zoomFactor_ === 2) {
    //    x = tileCoord[1];
    //    y = tileCoord[2];
    //  } else {
    //    tileCoordExtent = this.getTileCoordExtent(tileCoord, opt_extent);
    //  }
    //  while (z >= this.minZoom) {
    //    if (this.zoomFactor_ === 2) {
    //      x = Math.floor(x / 2);
    //      y = Math.floor(y / 2);
    //      tileRange = createOrUpdateTileRange(x, x, y, y, opt_tileRange);
    //    } else {
    //      tileRange = this.getTileRangeForExtentAndZ(tileCoordExtent, z, opt_tileRange);
    //    }
    //    if (callback.call(opt_this, z, tileRange)) {
    //      return true;
    //    }
    //    --z;
    //  }
    //  return false;
    //};


    /**
     * Get the extent for this tile grid, if it was configured.
     * @return {module:ol/extent~Extent} Extent.
     */
    ol::extent::Extent const &getExtent() const
    {
        return extent_;
    }
    
    
    /**
     * Get the maximum zoom level for the grid.
     * @return {number} Max zoom.
     * @api
     */
    int getMaxZoom() const
    {
        return maxZoom;
    }
    
    
    /**
     * Get the minimum zoom level for the grid.
     * @return {number} Min zoom.
     * @api
     */
    int getMinZoom() const
    {
        return minZoom;
    }
    
    /**
     * Get the origin for the grid at the given zoom level.
     * @param {number} z Integer zoom level.
     * @return {module:ol/coordinate~Coordinate} Origin.
     * @api
     */
    ol::coordinate::Coordinate getOrigin(int z = 0) const
    {
        if (origin_.size()) {
            return origin_;
        }
        return origins_[z];
    }
    
    /**
     * Get the resolution for the given zoom level.
     * @param {number} z Integer zoom level.
     * @return {number} Resolution.
     * @api
     */
    ol::number_t getResolution(int z) const
    {
        return resolutions_[z];
    }
    
    
    /**
     * Get the list of resolutions for the tile grid.
     * @return {Array.<number>} Resolutions.
     * @api
     */
    std::vector<number_t> const &getResolutions() const
    {
        return resolutions_;
    }
    //
    //
    ///**
    // * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
    // * @param {module:ol/TileRange=} opt_tileRange Temporary module:ol/TileRange object.
    // * @param {module:ol/extent~Extent=} opt_extent Temporary module:ol/extent~Extent object.
    // * @return {module:ol/TileRange} Tile range.
    // */
    //TileGrid.prototype.getTileCoordChildTileRange = function(tileCoord, opt_tileRange, opt_extent) {
    //  if (tileCoord[0] < this.maxZoom) {
    //    if (this.zoomFactor_ === 2) {
    //      const minX = tileCoord[1] * 2;
    //      const minY = tileCoord[2] * 2;
    //      return createOrUpdateTileRange(minX, minX + 1, minY, minY + 1, opt_tileRange);
    //    }
    //    const tileCoordExtent = this.getTileCoordExtent(tileCoord, opt_extent);
    //    return this.getTileRangeForExtentAndZ(
    //      tileCoordExtent, tileCoord[0] + 1, opt_tileRange);
    //  }
    //  return null;
    //};
    //
    //
    ///**
    // * Get the extent for a tile range.
    // * @param {number} z Integer zoom level.
    // * @param {module:ol/TileRange} tileRange Tile range.
    // * @param {module:ol/extent~Extent=} opt_extent Temporary module:ol/extent~Extent object.
    // * @return {module:ol/extent~Extent} Extent.
    // */
    //TileGrid.prototype.getTileRangeExtent = function(z, tileRange, opt_extent) {
    //  const origin = this.getOrigin(z);
    //  const resolution = this.getResolution(z);
    //  const tileSize = toSize(this.getTileSize(z), this.tmpSize_);
    //  const minX = origin[0] + tileRange.minX * tileSize[0] * resolution;
    //  const maxX = origin[0] + (tileRange.maxX + 1) * tileSize[0] * resolution;
    //  const minY = origin[1] + tileRange.minY * tileSize[1] * resolution;
    //  const maxY = origin[1] + (tileRange.maxY + 1) * tileSize[1] * resolution;
    //  return createOrUpdate(minX, minY, maxX, maxY, opt_extent);
    //};
    
    
    /**
     * Get a tile range for the given extent and integer zoom level.
     * @param {module:ol/extent~Extent} extent Extent.
     * @param {number} z Integer zoom level.
     * @param {module:ol/TileRange=} opt_tileRange Temporary tile range object.
     * @return {module:ol/TileRange} Tile range.
     */
    ol::TileRange getTileRangeForExtentAndZ(ol::extent::Extent const &extent, int z/*, opt_tileRange*/) const
    {
        auto tileCoord = getTileCoordForXYAndZ_(extent[0], extent[1], z, false/*, tileCoord*/);
        auto minX = tileCoord[1];
        auto minY = tileCoord[2];
        tileCoord = getTileCoordForXYAndZ_(extent[2], extent[3], z, true/*, tileCoord*/);

        return ol::TileRange::createOrUpdate(minX, tileCoord[1], minY, tileCoord[2]/*, opt_tileRange*/);
    }
    
    
    ///**
    // * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
    // * @return {module:ol/coordinate~Coordinate} Tile center.
    // */
    //TileGrid.prototype.getTileCoordCenter = function(tileCoord) {
    //  const origin = this.getOrigin(tileCoord[0]);
    //  const resolution = this.getResolution(tileCoord[0]);
    //  const tileSize = toSize(this.getTileSize(tileCoord[0]), this.tmpSize_);
    //  return [
    //    origin[0] + (tileCoord[1] + 0.5) * tileSize[0] * resolution,
    //    origin[1] + (tileCoord[2] + 0.5) * tileSize[1] * resolution
    //  ];
    //};
    //
    //
    ///**
    // * Get the extent of a tile coordinate.
    // *
    // * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
    // * @param {module:ol/extent~Extent=} opt_extent Temporary extent object.
    // * @return {module:ol/extent~Extent} Extent.
    // * @api
    // */
    //TileGrid.prototype.getTileCoordExtent = function(tileCoord, opt_extent) {
    //  const origin = this.getOrigin(tileCoord[0]);
    //  const resolution = this.getResolution(tileCoord[0]);
    //  const tileSize = toSize(this.getTileSize(tileCoord[0]), this.tmpSize_);
    //  const minX = origin[0] + tileCoord[1] * tileSize[0] * resolution;
    //  const minY = origin[1] + tileCoord[2] * tileSize[1] * resolution;
    //  const maxX = minX + tileSize[0] * resolution;
    //  const maxY = minY + tileSize[1] * resolution;
    //  return createOrUpdate(minX, minY, maxX, maxY, opt_extent);
    //};
    //
    //
    ///**
    // * Get the tile coordinate for the given map coordinate and resolution.  This
    // * method considers that coordinates that intersect tile boundaries should be
    // * assigned the higher tile coordinate.
    // *
    // * @param {module:ol/coordinate~Coordinate} coordinate Coordinate.
    // * @param {number} resolution Resolution.
    // * @param {module:ol/tilecoord~TileCoord=} opt_tileCoord Destination module:ol/tilecoord~TileCoord object.
    // * @return {module:ol/tilecoord~TileCoord} Tile coordinate.
    // * @api
    // */
    //TileGrid.prototype.getTileCoordForCoordAndResolution = function(coordinate, resolution, opt_tileCoord) {
    //  return this.getTileCoordForXYAndResolution_(
    //    coordinate[0], coordinate[1], resolution, false, opt_tileCoord);
    //};
    //
    //
    ///**
    // * Note that this method should not be called for resolutions that correspond
    // * to an integer zoom level.  Instead call the `getTileCoordForXYAndZ_` method.
    // * @param {number} x X.
    // * @param {number} y Y.
    // * @param {number} resolution Resolution (for a non-integer zoom level).
    // * @param {boolean} reverseIntersectionPolicy Instead of letting edge
    // *     intersections go to the higher tile coordinate, let edge intersections
    // *     go to the lower tile coordinate.
    // * @param {module:ol/tilecoord~TileCoord=} opt_tileCoord Temporary module:ol/tilecoord~TileCoord object.
    // * @return {module:ol/tilecoord~TileCoord} Tile coordinate.
    // * @private
    // */
    //TileGrid.prototype.getTileCoordForXYAndResolution_ = function(
    //  x, y, resolution, reverseIntersectionPolicy, opt_tileCoord) {
    //  const z = this.getZForResolution(resolution);
    //  const scale = resolution / this.getResolution(z);
    //  const origin = this.getOrigin(z);
    //  const tileSize = toSize(this.getTileSize(z), this.tmpSize_);
    //
    //  const adjustX = reverseIntersectionPolicy ? 0.5 : 0;
    //  const adjustY = reverseIntersectionPolicy ? 0 : 0.5;
    //  const xFromOrigin = Math.floor((x - origin[0]) / resolution + adjustX);
    //  const yFromOrigin = Math.floor((y - origin[1]) / resolution + adjustY);
    //  let tileCoordX = scale * xFromOrigin / tileSize[0];
    //  let tileCoordY = scale * yFromOrigin / tileSize[1];
    //
    //  if (reverseIntersectionPolicy) {
    //    tileCoordX = Math.ceil(tileCoordX) - 1;
    //    tileCoordY = Math.ceil(tileCoordY) - 1;
    //  } else {
    //    tileCoordX = Math.floor(tileCoordX);
    //    tileCoordY = Math.floor(tileCoordY);
    //  }
    //
    //  return createOrUpdateTileCoord(z, tileCoordX, tileCoordY, opt_tileCoord);
    //};
    
    
    /**
     * Although there is repetition between this method and `getTileCoordForXYAndResolution_`,
     * they should have separate implementations.  This method is for integer zoom
     * levels.  The other method should only be called for resolutions corresponding
     * to non-integer zoom levels.
     * @param {number} x Map x coordinate.
     * @param {number} y Map y coordinate.
     * @param {number} z Integer zoom level.
     * @param {boolean} reverseIntersectionPolicy Instead of letting edge
     *     intersections go to the higher tile coordinate, let edge intersections
     *     go to the lower tile coordinate.
     * @param {module:ol/tilecoord~TileCoord=} opt_tileCoord Temporary module:ol/tilecoord~TileCoord object.
     * @return {module:ol/tilecoord~TileCoord} Tile coordinate.
     * @private
     */
ol::tilecoord::TileCoord getTileCoordForXYAndZ_(ol::number_t x, ol::number_t y, ol::tilecoord::tilecoord_t z,
    bool reverseIntersectionPolicy/*, opt_tileCoord*/) const;
    
    
    ///**
    // * Get a tile coordinate given a map coordinate and zoom level.
    // * @param {module:ol/coordinate~Coordinate} coordinate Coordinate.
    // * @param {number} z Zoom level.
    // * @param {module:ol/tilecoord~TileCoord=} opt_tileCoord Destination module:ol/tilecoord~TileCoord object.
    // * @return {module:ol/tilecoord~TileCoord} Tile coordinate.
    // * @api
    // */
    //TileGrid.prototype.getTileCoordForCoordAndZ = function(coordinate, z, opt_tileCoord) {
    //  return this.getTileCoordForXYAndZ_(
    //    coordinate[0], coordinate[1], z, false, opt_tileCoord);
    //};
    //
    //
    ///**
    // * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
    // * @return {number} Tile resolution.
    // */
    //TileGrid.prototype.getTileCoordResolution = function(tileCoord) {
    //  return this.resolutions_[tileCoord[0]];
    //};

    /**
     * Get the tile size for a zoom level. The type of the return value matches the
     * `tileSize` or `tileSizes` that the tile grid was configured with. To always
     * get an `module:ol/size~Size`, run the result through `module:ol/size~Size.toSize()`.
     * @param {number} z Z.
     * @return {number|module:ol/size~Size} Tile size.
     * @api
     */
    ol::size::Size const &getTileSize(int z) const
    {
        if (tileSize_.size())
            return tileSize_;

        return tileSizes_[z];

    }
    
    /**
     * @param {number} z Zoom level.
     * @return {module:ol/TileRange} Extent tile range for the specified zoom level.
     */
    ol::TileRange const &getFullTileRange(int z) const
    {
        if (!fullTileRanges_.size())
            return ol::TileRange::Empty;

        return fullTileRanges_[z];
    }
    
    
    /**
     * @param {number} resolution Resolution.
     * @param {number=} opt_direction If 0, the nearest resolution will be used.
     *     If 1, the nearest lower resolution will be used. If -1, the nearest
     *     higher resolution will be used. Default is 0.
     * @return {number} Z.
     * @api
     */
    ol::number_t getZForResolution(number_t resolution, int opt_direction = 0)
    {
        size_t z = ol::array::linearFindNearest<ol::number_t>(resolutions_, resolution, opt_direction);
        return ol::math::clamp(ol::number_t(z), minZoom, maxZoom);
    }
    
    
    /**
     * @param {!module:ol/extent~Extent} extent Extent for this tile grid.
     * @private
     */
    void calculateTileRanges_(ol::extent::Extent const &extent) 
    {
        auto length = resolutions_.size();
        std::vector<ol::TileRange> fullTileRanges (length);
        for (int z = minZoom; z < length; ++z) {
            fullTileRanges[z] = getTileRangeForExtentAndZ(extent, z);
        }
        fullTileRanges_ = fullTileRanges;
    }

    // DEBUG
    ol::optional<number_t> const &getZoomFactor() const
    {
        return zoomFactor_;
    }
};
//export default TileGrid;
}
}
#endif // OL_TILEGRID_TILEGRID_H
