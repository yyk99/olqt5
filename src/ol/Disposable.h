///**
// * @module ol/Disposable
// */

#ifndef OL_DISPOSABLE
#define OL_DISPOSABLE

#include "dll_export.h"

//import {UNDEFINED} from './functions.js';
//

namespace ol {

///**
// * Objects that need to clean up after themselves.
// * @constructor
// */
//const Disposable = function() {};

class OLQT_EXPORT Disposable {
public:
    Disposable() {}
    virtual ~Disposable() {}

    virtual void dispose() {}
};

//
///**
// * The object has already been disposed.
// * @type {boolean}
// * @private
// */
//Disposable.prototype.disposed_ = false;
//
///**
// * Clean up.
// */
//Disposable.prototype.dispose = function() {
//  if (!this.disposed_) {
//    this.disposed_ = true;
//    this.disposeInternal();
//  }
//};
//
///**
// * Extension point for disposable objects.
// * @protected
// */
//Disposable.prototype.disposeInternal = UNDEFINED;
//export default Disposable;
}
#endif // OL_DISPOSABLE
