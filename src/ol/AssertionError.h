//
//
//

#ifndef OL_ASSERTIONERROR_H
#define OL_ASSERTIONERROR_H

///**
// * @module ol/AssertionError
// */
//import {VERSION, inherits} from './util.js';

#include "./util.h"
#include <stdexcept>
#include <string>

namespace ol {

/**
 * Error object thrown when an assertion failed. This is an ECMA-262 Error,
 * extended with a `code` property.
 * @see {@link https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Error}
 * @constructor
 * @extends {Error}
 * @param {number} code Error code.
 */
class AssertionError : public std::exception
{
private:
    int m_code;
    std::string m_message;
    std::string m_name;
public:
    AssertionError(int code) {
        //const AssertionError = function(code) {
       //
        auto path = ol::util::VERSION/*.split('-')[0]*/;
        //
        //  /**
        //   * @type {string}
        //   */
        m_message = "Assertion failed. See https://openlayers.org/en/" + path +
            "/doc/errors/#" + std::to_string(code) + " for details.";

        /**
         * Error code. The meaning of the code can be found on
         * {@link https://openlayers.org/en/latest/doc/errors/} (replace `latest` with
         * the version found in the OpenLayers script's header comment if a version
         * other than the latest is used).
         * @type {number}
         * @api
         */
        m_code = code;
        m_name = "AssertionError";
    }

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
