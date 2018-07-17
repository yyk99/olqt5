#ifndef OL_OBSERVABLE_H
#define OL_OBSERVABLE_H

#include <vector>
#include <string>

#include "dll_export.h"

///**
// * @module ol/Observable
// */
//import {inherits} from './util.js';
//import {listen, unlistenByKey, unlisten, listenOnce} from './events.js';
#include "events.h"
//import EventTarget from './events/EventTarget.js';
#include "events/EventTarget.h"
//import EventType from './events/EventType.js';
#include "events/EventType.h"
//

namespace ol {

///**
// * @classdesc
// * Abstract base class; normally only used for creating subclasses and not
// * instantiated in apps.
// * An event target providing convenient methods for listener registration
// * and unregistration. A generic `change` event is always available through
// * {@link module:ol/Observable~Observable#changed}.
// *
// * @constructor
// * @extends {module:ol/events/EventTarget}
// * @fires module:ol/events/Event~Event
// * @struct
// * @api
// */

class OLQT_EXPORT Observable : public ol::events::EventTarget {
private:
    int revision_;
public:
    Observable () : revision_(0) {
    //
    //  EventTarget.call(this);
    //
    //  /**
    //   * @private
    //   * @type {number}
    //   */
    //  this.revision_ = 0;
    //
    };
    
    //inherits(Observable, EventTarget);
    
    
    /**
     * Removes an event listener using the key returned by `on()` or `once()`.
     * @param {module:ol/events~EventsKey|Array.<module:ol/events~EventsKey>} key The key returned by `on()`
     *     or `once()` (or an array of keys).
     * @api
     */
    void unByKey(std::string const &key) {
      //if (Array.isArray(key)) {
      //  for (let i = 0, ii = key.length; i < ii; ++i) {
      //    unlistenByKey(key[i]);
      //  }
      //} else {
      //  unlistenByKey(/** @type {module:ol/events~EventsKey} */ (key));
      //}
    }
    
    
    /**
     * Increases the revision counter and dispatches a 'change' event.
     * @api
     */
    void changed() 
    {
        ++revision_;
        dispatchEvent(events::EventType::CHANGE);
    }
    
    
    /**
     * Dispatches an event and calls all listeners listening for events
     * of this type. The event parameter can either be a string or an
     * Object with a `type` property.
     *
     * @param {{type: string,
     *     target: (EventTarget|module:ol/events/EventTarget|undefined)}|
     *     module:ol/events/Event|string} event Event object.
     * @function
     * @api
     */
    //Observable.prototype.dispatchEvent;
    virtual void dispatchEvent(events::EventType::_type t) {};
    virtual void dispatchEvent(events::Event const &evnt) {};
    //
    //
    /**
     * Get the version number for this object.  Each time the object is modified,
     * its version number will be incremented.
     * @return {number} Revision.
     * @api
     */
    int getRevision() const {
        return revision_;
    }
    
    
    /**
     * Listen for a certain type of event.
     * @param {string|Array.<string>} type The event type or array of event types.
     * @param {function(?): ?} listener The listener function.
     * @return {module:ol/events~EventsKey|Array.<module:ol/events~EventsKey>} Unique key for the listener. If
     *     called with an array of event types as the first argument, the return
     *     will be an array of keys.
     * @api
     */
    std::vector<events::EventsKey> on(std::vector<std::string> const &type, events::ListenerF listener)
    {
        size_t len = type.size();
        std::vector<events::EventsKey> keys (len);
        for (int i = 0; i != len; ++i) {
            keys[i] = listen(this, type[i], listener);
        }
        return keys;
    }
    
    
    ///**
    // * Listen once for a certain type of event.
    // * @param {string|Array.<string>} type The event type or array of event types.
    // * @param {function(?): ?} listener The listener function.
    // * @return {module:ol/events~EventsKey|Array.<module:ol/events~EventsKey>} Unique key for the listener. If
    // *     called with an array of event types as the first argument, the return
    // *     will be an array of keys.
    // * @api
    // */
    //Observable.prototype.once = function(type, listener) {
    //  if (Array.isArray(type)) {
    //    const len = type.length;
    //    const keys = new Array(len);
    //    for (let i = 0; i < len; ++i) {
    //      keys[i] = listenOnce(this, type[i], listener);
    //    }
    //    return keys;
    //  } else {
    //    return listenOnce(this, /** @type {string} */ (type), listener);
    //  }
    //};
    //
    //
    ///**
    // * Unlisten for a certain type of event.
    // * @param {string|Array.<string>} type The event type or array of event types.
    // * @param {function(?): ?} listener The listener function.
    // * @api
    // */
    //Observable.prototype.un = function(type, listener) {
    //  if (Array.isArray(type)) {
    //    for (let i = 0, ii = type.length; i < ii; ++i) {
    //      unlisten(this, type[i], listener);
    //    }
    //    return;
    //  } else {
    //    unlisten(this, /** @type {string} */ (type), listener);
    //  }
    //};
};
//export default Observable;
}
#endif