///**
// * @module ol/uri
// */
//
//

#ifndef OLQT5_URI_H
#define OLQT5_URI_H

#include <string>
#include <vector>
#include <tuple>

#include "dll_export.h"

namespace ol {

/**
 * Appends query parameters to a URI.
 *
 * @param {string} uri The original URI, which may already have query data.
 * @param {!Object} params An object where keys are URI-encoded parameter keys,
 *     and the values are arbitrary types or arrays.
 * @return {string} The new URI.
 */

std::string OLQT_EXPORT appendParams(std::string uri, std::vector<std::tuple<std::string, std::string>> const &params);

} //
#endif // OLQT5_URI_H
