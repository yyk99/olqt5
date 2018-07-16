#ifndef OL_ROTATIONCONSTRAINT_H
#define OL_ROTATIONCONSTRAINT_H

///**
// * @module ol/rotationconstraint
// */
//import {toRadians} from './math.js';
#include "math.h"
#include "jsport.h"
#include "optional.h"

#include "dll_export.h"

namespace ol {
namespace rotationconstraint {
//
//
/**
 * @typedef {function((number|undefined), number): (number|undefined)} Type
 */
class Type {
public:
    virtual optional<number_t> operator() (optional<number_t> rotation, number_t delta) const = 0;
};
 
//
///**
// * @param {number|undefined} rotation Rotation.
// * @param {number} delta Delta.
// * @return {number|undefined} Rotation.
// */
//export function disable(rotation, delta) {
//  if (rotation !== undefined) {
//    return 0;
//  } else {
//    return undefined;
//  }
//}

class OLQT_EXPORT disable : public Type {
public:
    // Inherited via Type
    virtual optional<number_t> operator()(optional<number_t>, number_t) const override;
};
//
//
///**
// * @param {number|undefined} rotation Rotation.
// * @param {number} delta Delta.
// * @return {number|undefined} Rotation.
// */
//export function none(rotation, delta) {
//  if (rotation !== undefined) {
//    return rotation + delta;
//  } else {
//    return undefined;
//  }
//}
//
//
///**
// * @param {number} n N.
// * @return {module:ol/rotationconstraint~Type} Rotation constraint.
// */
//export function createSnapToN(n) {
//  const theta = 2 * Math.PI / n;
//  return (
//    /**
//     * @param {number|undefined} rotation Rotation.
//     * @param {number} delta Delta.
//     * @return {number|undefined} Rotation.
//     */
//    function(rotation, delta) {
//      if (rotation !== undefined) {
//        rotation = Math.floor((rotation + delta) / theta + 0.5) * theta;
//        return rotation;
//      } else {
//        return undefined;
//      }
//    });
//}
//
//

class OLQT_EXPORT snapToZero : public Type {
    ol::number_t tolerance;
public:
    snapToZero(number_t tolerance) : tolerance(tolerance) {}

    virtual optional<number_t> operator()(optional<number_t> rotation, number_t delta) const override
    {
        if (rotation.has_value()) {
            if (std::abs(rotation.value() + delta) <= tolerance) {
                return 0;
            }
            return rotation.value() + delta;
        }
        return optional<number_t>();
    }
};

/**
 * @param {number=} opt_tolerance Tolerance.
 * @return {module:ol/rotationconstraint~Type} Rotation constraint.
 */
inline snapToZero createSnapToZero(optional<number_t> opt_tolerance = optional<number_t>()) {
//  const tolerance = opt_tolerance || toRadians(5);
//  return (
//    /**
//     * @param {number|undefined} rotation Rotation.
//     * @param {number} delta Delta.
//     * @return {number|undefined} Rotation.
//     */
//    function(rotation, delta) {
//      if (rotation !== undefined) {
//        if (Math.abs(rotation + delta) <= tolerance) {
//          return 0;
//        } else {
//          return rotation + delta;
//        }
//      } else {
//        return undefined;
//      }
//    });
    return snapToZero(opt_tolerance.has_value() ? opt_tolerance.value() : math::toRadians(5));
}
} // namespce rotationconstraint
} // ol
#endif // OL_ROTATIONCONSTRAINT_H