#ifndef OL_TILESTATE_H
#define OL_TILESTATE_H

/**
 * @module ol/TileState
 */

namespace ol {
/**
 * @enum {number}
 */
struct TileState 
{
    enum _t {
        IDLE = 0,
        LOADING = 1,
        LOADED = 2,
        ERROR = 3,
        EMPTY = 4,
        ABORT = 5
    };
};

}
#endif
