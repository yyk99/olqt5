//
//
//

#ifndef OLQT_STRING_H
#define OLQT_STRING_H

///**
// * @module ol/string
// */

#include <string>

#include "optional.h"

#include "dll_export.h"

namespace ol {

typedef double number_t;

namespace string {


/**
 * @param {number} number Number to be formatted
 * @param {number} width The desired width
 * @param {number=} opt_precision Precision of the output string (i.e. number of decimal places)
 * @returns {string} Formatted string
 */
std::string OLQT_EXPORT padNumber(number_t number, int width, ol::optional<int> opt_precision = ol::optional<int>());
//
//
/**
 * Adapted from https://github.com/omichelsen/compare-versions/blob/master/index.js
 * @param {string|number} v1 First version
 * @param {string|number} v2 Second version
 * @returns {number} Value
 */
int OLQT_EXPORT compareVersions(std::string const &v1, std::string const &v2);

int OLQT_EXPORT compareVersions(ol::number_t v1, ol::number_t v2);

} // namespace string
}
#endif