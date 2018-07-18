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

class OLQT_EXPORT Disposable 
{
private:
    /**
    * The object has already been disposed.
    * @type {boolean}
    * @private
    */
    bool disposed_;

public:
    Disposable() : disposed_(false) {}
    virtual ~Disposable();

    /**
     * Clean up.
     */
    void virtual dispose() 
    {
        if (!disposed_) 
        {
            disposed_ = true;
            disposeInternal();
        }
    }

    /**
     * Extension point for disposable objects.
     * @protected
     */
protected:
    void virtual disposeInternal()
    {
    }
};

//export default Disposable;
}
#endif // OL_DISPOSABLE
