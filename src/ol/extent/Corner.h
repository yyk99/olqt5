#ifndef OL_EXTENT_CORNER_H
#define OL_EXTENT_CORNER_H
/**
 * @module ol/extent/Corner
 */

#include "../dll_export.h"

namespace ol {
namespace extent {

/**
 * Extent corner.
 * @enum {string}
 */
struct Corner
{
    OLQT_EXPORT static std::string BOTTOM_LEFT, // 'bottom-left',
        BOTTOM_RIGHT, // 'bottom-right',
        TOP_LEFT, // 'top-left',
        TOP_RIGHT; // 'top-right'
};

}
}
#endif
