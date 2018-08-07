#ifndef OL_JSPORT_H
#define OL_JSPORT_H

#include <string>
#include <vector>

namespace ol {

typedef double number_t;

}

namespace ol {
namespace proj {

/**
* A projection as {@link module:ol/proj/Projection}, SRS identifier
* string or undefined.
* @typedef {module:ol/proj/Projection|string|undefined} ProjectionLike
* @api
*/

typedef std::string ProjectionLike;

/**
* A transform function accepts an array of input coordinate values, an optional
* output array, and an optional dimension (default should be 2).  The function
* transforms the input coordinate values, populates the output array, and
* returns the output array.
*
* @typedef {function(Array.<number>, Array.<number>=, number=): Array.<number>} TransformFunction
* @api
*/

#if 1
class TransformFunctionObj {
public:
    virtual std::vector<number_t> & operator ()(std::vector<number_t> const &, std::vector<number_t> &, size_t) = 0;
};

typedef TransformFunctionObj *TransformFunction;

#else
typedef void *TransformFunction;
#endif

}
}


#endif
