#ifndef OL_SIZE_H
#define OL_SIZE_H

/**
 * @module ol/size
 */

#include <vector>
#include "jsport.h"
#include "optional.h"
#include <cmath>

namespace ol {
namespace size {
/**
 * An array of numbers representing a size: `[width, height]`.
 * @typedef {Array.<number>} Size
 * @api
 */

typedef std::vector<number_t> Size;



/**
 * Returns a buffered size.
 * @param {module:ol/size~Size} size Size.
 * @param {number} num The amount by which to buffer.
 * @param {module:ol/size~Size=} opt_size Optional reusable size array.
 * @return {module:ol/size~Size} The buffered size.
 */
inline Size bufferSize(Size const &size, number_t num)
{
    Size opt_size = { 0, 0 };

    opt_size[0] = size[0] + 2 * num;
    opt_size[1] = size[1] + 2 * num;

    return opt_size;
}

inline Size &bufferSize(Size const &size, number_t num, Size &opt_size)
{
    opt_size[0] = size[0] + 2 * num;
    opt_size[1] = size[1] + 2 * num;

    return opt_size;
}


/**
 * Determines if a size has a positive area.
 * @param {module:ol/size~Size} size The size to test.
 * @return {boolean} The size has a positive area.
 */
inline bool hasArea(Size const &size) 
{
  return size[0] > 0 && size[1] > 0;
}


/**
 * Returns a size scaled by a ratio. The result will be an array of integers.
 * @param {module:ol/size~Size} size Size.
 * @param {number} ratio Ratio.
 * @param {module:ol/size~Size=} opt_size Optional reusable size array.
 * @return {module:ol/size~Size} The scaled size.
 */
inline Size &scaleSize(Size const &size, number_t ratio, Size &opt_size) 
{
  //if (opt_size === undefined) {
  //  opt_size = [0, 0];
  //}
    opt_size[0] = std::floor(size[0] * ratio + 0.5);
    opt_size[1] = std::floor(size[1] * ratio + 0.5);

  return opt_size;
}

inline Size scaleSize(Size const &size, number_t ratio) 
{
    Size opt_size = { 0, 0 };

    opt_size[0] = std::floor(size[0] * ratio + 0.5);
    opt_size[1] = std::floor(size[1] * ratio + 0.5);

    return opt_size;
}

/**
 * Returns an `module:ol/size~Size` array for the passed in number (meaning: square) or
 * `module:ol/size~Size` array.
 * (meaning: non-square),
 * @param {number|module:ol/size~Size} size Width and height.
 * @param {module:ol/size~Size=} opt_size Optional reusable size array.
 * @return {module:ol/size~Size} Size.
 * @api
 */

inline Size toSize(number_t size)
{
    return Size({ size, size });
}

inline Size &toSize(number_t size, Size &opt_size)
{
    opt_size = { size, size };
    return opt_size;
}

}
}
#endif // OL_SIZE_H
