//
//
//

#include "AssertionError.h"

//import {VERSION, inherits} from './util.js';
#include "./util.h"

ol::AssertionError::AssertionError(int code)
{
    //const AssertionError = function(code) {
   //
    auto path = ol::util::VERSION/*.split('-')[0]*/;
    
    /**
    * @type {string}
    */
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
