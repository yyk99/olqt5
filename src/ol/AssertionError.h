//
//
//

#ifndef OL_ASSERTIONERROR_H
#define OL_ASSERTIONERROR_H

/**
 * @module ol/AssertionError
 */

#pragma warning ( disable : 4275 )

#include <stdexcept>
#include <string>

#include "dll_export.h"

namespace ol {

/**
 * Error object thrown when an assertion failed. This is an ECMA-262 Error,
 * extended with a `code` property.
 * @see {@link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Error}
 * @constructor
 * @extends {Error}
 * @param {number} code Error code.
 */
class OLQT_EXPORT AssertionError : public std::exception
{
private:
    int m_code;
    std::string m_message;
    std::string m_name;
public:
    AssertionError(int code);

    virtual const char* what() const override {
        return m_message.c_str();
    }

    std::string message() const
    {
        return m_message;
    }

    int code() const {
        return m_code;
    }

    std::string name() const {
        return m_name;
    }
};
//
//inherits(AssertionError, Error);
}
//
//export default AssertionError;

#endif // OL_ASSERTIONERROR_H
