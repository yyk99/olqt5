#ifndef OL_UTIL_H
#define OL_UTIL_H

#include "dll_export.h"

#include <string>

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

///**
// * Counter for getUid.
// * @type {number}
// * @private
// */
//let uidCounter_ = 0;
  
/**
* Gets a unique ID for an object. This mutates the object so that further calls
* with the same object as a parameter returns the same value. Unique IDs are generated
* as a strictly increasing sequence. Adapted from goog.getUid.
*
* @param {Object} obj The object to get the unique ID for.
* @return {number} The unique ID for the object.
*/
inline int getUid(void *obj) 
{
    throw std::runtime_error("not implemented");
//     return obj.ol_uid || (obj.ol_uid = ++uidCounter_);
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
