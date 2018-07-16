#include "rotationconstraint.h"

using namespace ol;
using namespace ol::rotationconstraint;

/**
 * @param {number|undefined} rotation Rotation.
 * @param {number} delta Delta.
 * @return {number|undefined} Rotation.
 */

//export function disable(rotation, delta) {
//  if (rotation !== undefined) {
//    return 0;
//  } else {
//    return undefined;
//  }
//}

optional<number_t> disable::operator()(optional<number_t> rotation, number_t delta) const
{
    if (rotation.has_value())
        return optional<number_t>(0);
    return optional<number_t>();
}
