#include "coordinate.h"

#include "./string.h"
#include "./math.h"

namespace ol {
namespace coordinate {

/**
* Transforms the given {@link module:ol/coordinate~Coordinate} to a string
* using the given string template. The strings `{x}` and `{y}` in the template
* will be replaced with the first and second coordinate values respectively.
*
* Example without specifying the fractional digits:
*
*     import {format} from 'ol/coordinate';
*
*     var coord = [7.85, 47.983333];
*     var template = 'Coordinate is ({x}|{y}).';
*     var out = format(coord, template);
*     // out is now 'Coordinate is (8|48).'
*
* Example explicitly specifying the fractional digits:
*
*     import {format} from 'ol/coordinate';
*
*     var coord = [7.85, 47.983333];
*     var template = 'Coordinate is ({x}|{y}).';
*     var out = format(coord, template, 2);
*     // out is now 'Coordinate is (7.85|47.98).'
*
* @param {module:ol/coordinate~Coordinate} coordinate Coordinate.
* @param {string} template A template string with `{x}` and `{y}` placeholders
*     that will be replaced by first and second coordinate values.
* @param {number=} opt_fractionDigits The number of digits to include
*    after the decimal point. Default is `0`.
* @return {string} Formatted coordinate.
* @api
*/
OLQT_EXPORT std::string format(Coordinate const & coordinate, std::string frm, int opt_fractionDigits)
{
    if (coordinate.size() == 0)
        return std::string();

    ol::string::replaceStringInPlace(frm, "{x}", ol::string::toFixed(coordinate[0], opt_fractionDigits));
    ol::string::replaceStringInPlace(frm, "{y}", ol::string::toFixed(coordinate[1], opt_fractionDigits));

    return frm;
}


}
}