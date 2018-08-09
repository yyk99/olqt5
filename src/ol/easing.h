#ifndef OL_ERASING_H
#define OL_ERASING_H

/**
 * @module ol/easing
 */

#include <cmath>

namespace ol {
namespace erasing {

/**
 * Start slow and speed up.
 * @param {number} t Input between 0 and 1.
 * @return {number} Output between 0 and 1.
 * @api
 */
inline ol::number_t easeIn(ol::number_t t) {
    return std::pow(t, 3);
}


/**
 * Start fast and slow down.
 * @param {number} t Input between 0 and 1.
 * @return {number} Output between 0 and 1.
 * @api
 */
 inline ol::number_t easeOut(number_t t) {
    return 1 - easeIn(1 - t);
}


/**
 * Start slow, speed up, and then slow down again.
 * @param {number} t Input between 0 and 1.
 * @return {number} Output between 0 and 1.
 * @api
 */
inline number_t inAndOut(number_t t) {
    return 3 * t * t - 2 * t * t * t;
}


/**
 * Maintain a constant speed over time.
 * @param {number} t Input between 0 and 1.
 * @return {number} Output between 0 and 1.
 * @api
 */
inline number_t linear(number_t t) {
    return t;
}


/**
 * Start slow, speed up, and at the very end slow down again.  This has the
 * same general behavior as {@link module:ol/easing~inAndOut}, but the final
 * slowdown is delayed.
 * @param {number} t Input between 0 and 1.
 * @return {number} Output between 0 and 1.
 * @api
 */
inline number_t upAndDown(number_t t) {
    if (t < 0.5) {
        return inAndOut(2 * t);
    } else {
        return 1 - inAndOut(2 * (t - 0.5));
    }
}


}
}
#endif
