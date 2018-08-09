#ifndef OL_UTIL_H
#define OL_UTIL_H

#include "dll_export.h"

#include <string>
#include <memory>
#include <stdint.h>

namespace ol {
namespace util {
/**
 * @module ol/util
 */

 /**
  * Inherit the prototype methods from one constructor into another.
  *
  * Usage:
  *
  *     function ParentClass(a, b) { }
  *     ParentClass.prototype.foo = function(a) { }
  *
  *     function ChildClass(a, b, c) {
  *       // Call parent constructor
  *       ParentClass.call(this, a, b);
  *     }
  *     inherits(ChildClass, ParentClass);
  *
  *     var child = new ChildClass('a', 'b', 'see');
  *     child.foo(); // This works.
  *
  * @param {!Function} childCtor Child constructor.
  * @param {!Function} parentCtor Parent constructor.
  * @function module:ol.inherits
  * @api
  */

//export function inherits(childCtor, parentCtor) {
//  childCtor.prototype = Object.create(parentCtor.prototype);
//  childCtor.prototype.constructor = childCtor;
//}

class OLQT_EXPORT Uid {
public:
    /**
     * Counter for getUid.
     * @type {number}
     * @private
     */
    static uint64_t uidCounter_ /*= 0*/;

    uint64_t ol_uid;
    Uid() : ol_uid() {}
};
  
/**
* Gets a unique ID for an object. This mutates the object so that further calls
* with the same object as a parameter returns the same value. Unique IDs are generated
* as a strictly increasing sequence. Adapted from goog.getUid.
*
* @param {Object} obj The object to get the unique ID for.
* @return {number} The unique ID for the object.
*/
inline uint64_t getUid(Uid &obj) 
{
    if (obj.ol_uid == 0)
        obj.ol_uid = ++Uid::uidCounter_;
    return obj.ol_uid;
}

inline uint64_t getUid(Uid *obj)
{
    return getUid(*obj);
}

inline uint64_t getUid(std::shared_ptr<Uid> obj)
{
    return getUid(obj.get());
}

/**
* OpenLayers version.
* @type {string}
*/
//export const VERSION = '5.0.1';

extern OLQT_EXPORT std::string VERSION;

} // namespace util
}
#endif // OL_UTIL_H
