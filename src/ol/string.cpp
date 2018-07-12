//
//
//

#include "string.h"

#include <iomanip>
#include <sstream>

#include <iostream>

/**
* @param {number} number Number to be formatted
* @param {number} width The desired width
* @param {number=} opt_precision Precision of the output string (i.e. number of decimal places)
* @returns {string} Formatted string
*/
std::string ol::string::padNumber(number_t number, int width, ol::optional<int> opt_precision) {
    //  const numberString = opt_precision !== undefined ? number.toFixed(opt_precision) : '' + number;
    //  let decimal = numberString.indexOf('.');
    //  decimal = decimal === -1 ? numberString.length : decimal;
    //  return decimal > width ? numberString : new Array(1 + width - decimal).join('0') + numberString;
    std::ostringstream ss;
    if (opt_precision.has_value())
        ss << std::fixed << std::setfill('0') << std::setprecision(opt_precision.value()) << number;
    else
        ss << std::setfill('0') << std::setw(width) << number;
    std::string numberString = ss.str();

    auto decimal = numberString.find('.');
    if (decimal == -1)
        decimal = numberString.size();
    return decimal > width ? numberString : std::string(width - decimal, '0') + numberString;
}

#include <vector>
#include <algorithm>

std::vector<std::string> split(std::string const &str, std::string const &delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) 
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

/**
* Adapted from https://github.com/omichelsen/compare-versions/blob/master/index.js
* @param {string|number} v1 First version
* @param {string|number} v2 Second version
* @returns {number} Value
*/
int OLQT_EXPORT ol::string::compareVersions(std::string const &v1, std::string const &v2) {
    auto s1 = split(v1, ".");
    auto s2 = split(v2, ".");
    
    for (int i = 0; i != std::max(s1.size(), s2.size()); i++) {
        int n1 = i < s1.size() ? atoi(s1[i].c_str()) : 0;
        int n2 = i < s2.size() ? atoi(s2[i].c_str()) : 0;

        if (n1 > n2) {
            return 1;
        }
        if (n2 > n1) {
            return -1;
        }
    }
    
    return 0;
}

int OLQT_EXPORT ol::string::compareVersions(ol::number_t v1, ol::number_t v2)
{
    return compareVersions(std::to_string(v1), std::to_string(v2));
}

//
