#ifndef OL_ASSERTS_H
#define OL_ASSERTS_H

///**
// * @module ol/asserts
// */
//import AssertionError from './AssertionError.js';
#include "AssertionError.h"

#ifdef _DEBUG
#   include <iostream>
#endif

namespace ol {
namespace asserts {

/**
 * @param {*} assertion Assertion we expected to be truthy.
 * @param {number} errorCode Error code.
 */
inline void Assert(bool assertion, int errorCode) 
{
    if (!assertion) {
#ifdef _DEBUG
        std::cerr << "ol::asserts::Assert failed: " << AssertionError(errorCode).message() << std::endl;
#endif
        throw AssertionError(errorCode);
    }
}

}
}

#endif
