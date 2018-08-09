#ifndef OL_TILE_H
#define OL_TILE_H

#include "dll_export.h"

///**
// * @module ol/Tile
// */

#include "tilecoord.h"

//import {inherits} from './util.js';
#include "./util.h"
//import TileState from './TileState.js';
#include "./TileState.h"
//import {easeIn} from './easing.js';
#include "./easing.h"
//import EventTarget from './events/EventTarget.js';
#include "./events/EventTarget.h"
//import EventType from './events/EventType.js';
#include "./events/EventType.h"

#include "optional.h"
#include "jsport.h"

#include <map>

namespace ol {

/**
 * A function that takes an {@link module:ol/Tile} for the tile and a
 * `{string}` for the url as arguments.
 *
 * @typedef {function(module:ol/Tile, string)} LoadFunction
 * @api
 */

/**
 * {@link module:ol/source/Tile~Tile} sources use a function of this type to get
 * the url that provides a tile for a given tile coordinate.
 *
 * This function takes an {@link module:ol/tilecoord~TileCoord} for the tile
 * coordinate, a `{number}` representing the pixel ratio and a
 * {@link module:ol/proj/Projection} for the projection  as arguments
 * and returns a `{string}` representing the tile URL, or undefined if no tile
 * should be requested for the passed tile coordinate.
 *
 * @typedef {function(module:ol/tilecoord~TileCoord, number,
 *           module:ol/proj/Projection): (string|undefined)} UrlFunction
 * @api
 */


/**
 * @typedef {Object} Options
 * @property {number} [transition=250] A duration for tile opacity
 * transitions in milliseconds. A duration of 0 disables the opacity transition.
 * @api
 */


class Tile;
typedef std::shared_ptr<Tile> TileP;

/**
 * @classdesc
 * Base class for tiles.
 *
 * @constructor
 * @abstract
 * @extends {module:ol/events/EventTarget}
 * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
 * @param {module:ol/TileState} state State.
 * @param {module:ol/Tile~Options=} opt_options Tile options.
 */

class OLQT_EXPORT Tile : public ol::events::EventTarget, public ol::util::Uid {
public: //private:
    ol::number_t transition_;
    /**
     * Lookup of start times for rendering transitions.  If the start time is
     * equal to -1, the transition is complete.
     * @type {Object.<number, number>}
     */
    std::map<ol::number_t, ol::number_t> transitionStarts_;

public: //protected:
    ol::tilecoord::TileCoord tileCoord;
    ol::TileState::_t state;
    std::string key;
    /**
    * An "interim" tile for this tile. The interim tile may be used while this
    * one is loading, for "smooth" transitions when changing params/dimensions
    * on the source.
    * @type {module:ol/Tile}
    */
    std::shared_ptr<Tile> interimTile;

public:
    struct Options {
        ol::number_t transition;

        Options() : transition(250) {}
        Options(ol::number_t t) : transition(t) {}
    };

    Tile() {}
    Tile(ol::tilecoord::TileCoord const &tileCoord,
        ol::TileState::_t state = ol::TileState::IDLE,
        ol::Tile::Options const &opt_options = ol::Tile::Options())
        : tileCoord(tileCoord)
        , state(state)
        , key("")
    {
        //const Tile = function(tileCoord, state, opt_options) {
        //  EventTarget.call(this);
        //
        //  const options = opt_options ? opt_options : {};
        //
        //  /**
        //   * @type {module:ol/tilecoord~TileCoord}
        //   */
        //  this.tileCoord = tileCoord;
        //
        //  /**
        //   * @protected
        //   * @type {module:ol/TileState}
        //   */
        //  this.state = state;
        //
        //  /**
        //   * An "interim" tile for this tile. The interim tile may be used while this
        //   * one is loading, for "smooth" transitions when changing params/dimensions
        //   * on the source.
        //   * @type {module:ol/Tile}
        //   */
        //  this.interimTile = null;
        //
        //  /**
        //   * A key assigned to the tile. This is used by the tile source to determine
        //   * if this tile can effectively be used, or if a new tile should be created
        //   * and this one be used as an interim tile for this new tile.
        //   * @type {string}
        //   */
        //  this.key = '';
        //
        //  /**
        //   * The duration for the opacity transition.
        //   * @type {number}
        //   */
        //  this.transition_ = options.transition === undefined ? 250 : options.transition;
        transition_ = opt_options.transition;
        //
        //  /**
        //   * Lookup of start times for rendering transitions.  If the start time is
        //   * equal to -1, the transition is complete.
        //   * @type {Object.<number, number>}
        //   */
        //  this.transitionStarts_ = {};
        //
        //};
    }

    virtual ~Tile();

    //
    //inherits(Tile, EventTarget);
    
    
    /**
     * @protected
     */
    void changed()
    {
        dispatchEvent(ol::events::EventType::CHANGE);
    }
    
    
    /**
     * @return {string} Key.
     */
    std::string getKey () const {
      return key + '/' + ol::tilecoord::getKey(tileCoord);
    };
    
    /**
     * Get the interim tile most suitable for rendering using the chain of interim
     * tiles. This corresponds to the  most recent tile that has been loaded, if no
     * such tile exists, the original tile is returned.
     * @return {!module:ol/Tile} Best tile for rendering.
     */
    static TileP getInterimTile(TileP _this) 
    {
        if (_this->interimTile == 0) {
            //empty chain
            return _this;
        }
        auto tile = _this->interimTile;

        // find the first loaded tile and return it. Since the chain is sorted in
        // decreasing order of creation time, there is no need to search the remainder
        // of the list (all those tiles correspond to older requests and will be
        // cleaned up by refreshInterimChain)
        do {
            if (tile->getState() == TileState::LOADED) {
                return tile;
            }
            tile = tile->interimTile;
        } while (tile);

        // we can not find a better tile
        return _this;
    }
    
    /**
     * Goes through the chain of interim tiles and discards sections of the chain
     * that are no longer relevant.
     */
    void refreshInterimChain() 
    {
        if (interimTile == 0) {
            return;
        }

        auto tile = interimTile;
        auto prev = this;

        do {
            if (tile->getState() == TileState::LOADED) {
                //we have a loaded tile, we can discard the rest of the list
                //we would could abort any LOADING tile request
                //older than this tile (i.e. any LOADING tile following this entry in the chain)
                tile->interimTile = TileP();
                break;
            } else if (tile->getState() == TileState::LOADING) {
                //keep this LOADING tile any loaded tiles later in the chain are
                //older than this tile, so we're still interested in the request
                prev = tile.get();
            } else if (tile->getState() == TileState::IDLE) {
                //the head of the list is the most current tile, we don't need
                //to start any other requests for this chain
                prev->interimTile = tile->interimTile;
            } else {
                prev = tile.get();
            }
            tile = prev->interimTile;
        } while (tile);
    }
    
    /**
     * Get the tile coordinate for this tile.
     * @return {module:ol/tilecoord~TileCoord} The tile coordinate.
     * @api
     */
    ol::tilecoord::TileCoord const &getTileCoord() const
    {
        return tileCoord;
    }
    
    /**
     * @return {module:ol/TileState} State.
     */
    ol::TileState::_t getState() const 
    {
        return state;
    }
    
    /**
     * @param {module:ol/TileState} state State.
     */
    void setState(ol::TileState::_t state) 
    {
        this->state = state;
        this->changed();
    }
    
    /**
     * Load the image or retry if loading previously failed.
     * Loading is taken care of by the tile queue, and calling this method is
     * only needed for preloading or for reloading in case of an error.
     * @abstract
     * @api
     */
    //Tile.prototype.load = function() {};
    
    /**
     * Get the alpha value for rendering.
     * @param {number} id An id for the renderer.
     * @param {number} time The render frame time.
     * @return {number} A number between 0 and 1.
     */
    ol::number_t getAlpha(ol::number_t id, ol::number_t &time)
    {
        if (!transition_) {
            return 1;
        }

        auto start = transitionStarts_[id];
        if (!start) {
            start = time;
            transitionStarts_[id] = start;
        } else if (start == -1) {
            return 1;
        }

        ol::number_t delta = time - start + (1000.0 / 60.0); // avoid rendering at 0
        if (delta >= transition_) {
            return 1;
        }
        return ol::erasing::easeIn(delta / transition_);
    }
    
    /**
     * Determine if a tile is in an alpha transition.  A tile is considered in
     * transition if tile.getAlpha() has not yet been called or has been called
     * and returned 1.
     * @param {number} id An id for the renderer.
     * @return {boolean} The tile is in transition.
     */
    bool inTransition(ol::number_t id) const 
    {
        if (!transition_) {
            return false;
        }
        auto pos = transitionStarts_.find(id);
        return pos == transitionStarts_.end() || pos->second != -1;
    }
    
    /**
     * Mark a transition as complete.
     * @param {number} id An id for the renderer.
     */
    void endTransition(number_t id) 
    {
        if (transition_) {
            transitionStarts_[id] = -1;
        }
    }
};
//export default Tile;

}

#endif // OL_TILE_H
