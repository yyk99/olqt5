#ifndef OL_MATH_H
#define OL_MATH_H

#include "dll_export.h"
#include "jsport.h"

#include <algorithm>
#include <vector>

/**
 * @module ol/math
 */
//import {assert} from './asserts.js';
#include "asserts.h"

namespace ol {
namespace math {
/**
 * Takes a number and clamps it to within the provided bounds.
 * @param {number} value The input number.
 * @param {number} min The minimum value to return.
 * @param {number} max The maximum value to return.
 * @return {number} The input number if it is within bounds, or the nearest
 *     number within the bounds.
 */
inline ol::number_t clamp(number_t value, number_t min, number_t max)
{
    return std::min(std::max(value, min), max);
}

/**
 * Return the hyperbolic cosine of a given number. The method will use the
 * native `Math.cosh` function if it is available, otherwise the hyperbolic
 * cosine will be calculated via the reference implementation of the Mozilla
 * developer network.
 *
 * @param {number} x X.
 * @return {number} Hyperbolic cosine of x.
 */
//export const cosh  = (function() {
//  // Wrapped in a iife, to save the overhead of checking for the native
//  // implementation on every invocation.
//  let cosh;
//  if ('cosh' in Math) {
//    // The environment supports the native Math.cosh function, use it…
//    cosh = Math.cosh;
//  } else {
//    // … else, use the reference implementation of MDN:
//    cosh = function(x) {
//      const y = Math.exp(x);
//      return (y + 1 / y) / 2;
//    };
//  }
//  return cosh;
//}());


const double LN2 = 0.69314718056;

/**
 * @param {number} x X.
 * @return {number} The smallest power of two greater than or equal to x.
 */
inline number_t roundUpToPowerOfTwo(number_t x)
{
    ol::asserts::Assert(0 < x, 29); // `x` must be greater than `0`
    return std::pow(2, std::ceil(std::log(x) / LN2));
}


/**
 * Returns the square of the closest distance between the point (x, y) and the
 * line segment (x1, y1) to (x2, y2).
 * @param {number} x X.
 * @param {number} y Y.
 * @param {number} x1 X1.
 * @param {number} y1 Y1.
 * @param {number} x2 X2.
 * @param {number} y2 Y2.
 * @return {number} Squared distance.
 */
OLQT_EXPORT number_t squaredSegmentDistance(number_t x, number_t y, number_t x1, number_t y1, number_t x2, number_t y2);

/**
 * Returns the square of the distance between the points (x1, y1) and (x2, y2).
 * @param {number} x1 X1.
 * @param {number} y1 Y1.
 * @param {number} x2 X2.
 * @param {number} y2 Y2.
 * @return {number} Squared distance.
 */
inline number_t squaredDistance(number_t x1, number_t y1, number_t x2, number_t y2)
{
    number_t dx = x2 - x1;
    number_t dy = y2 - y1;
    return dx * dx + dy * dy;
}


typedef std::vector<std::vector<number_t> > matrix_t;

/**
* Solves system of linear equations using Gaussian elimination method.
*
* @param {Array.<Array.<number>>} mat Augmented matrix (n x n + 1 column)
*                                     in row-major order.
* @return {Array.<number>} The resulting vector.
*/
OLQT_EXPORT std::vector<number_t> solveLinearSystem(matrix_t mat);

const ol::number_t PI = 3.14159265358979323846;

/**
 * Converts radians to to degrees.
 *
 * @param {number} angleInRadians Angle in radians.
 * @return {number} Angle in degrees.
 */
inline number_t toDegrees(number_t angleInRadians) 
{
  return angleInRadians * 180 / PI;
}


/**
 * Converts degrees to radians.
 *
 * @param {number} angleInDegrees Angle in degrees.
 * @return {number} Angle in radians.
 */
inline ol::number_t toRadians(ol::number_t angleInDegrees) 
{
  return angleInDegrees * PI / 180;
}

/**
 * Returns the modulo of a / b, depending on the sign of b.
 *
 * @param {number} a Dividend.
 * @param {number} b Divisor.
 * @return {number} Modulo.
 */
inline ol::number_t modulo(ol::number_t a, ol::number_t b)
{
    ol::number_t r = std::fmod(a, b);
    return r * b < 0 ? r + b : r;
}

/**
 * Calculates the linearly interpolated value of x between a and b.
 *
 * @param {number} a Number
 * @param {number} b Number
 * @param {number} x Value to be interpolated.
 * @return {number} Interpolated value.
 */
inline number_t lerp(number_t a, number_t b, number_t x)
{
    return a + x * (b - a);
}

} // math
} // namespace

#endif // OL_MATH_H