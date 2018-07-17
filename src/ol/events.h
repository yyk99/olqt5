#ifndef OL_EVENTS_H
#define OL_EVENTS_H

///**
// * @module ol/events
// */
//import {clear} from './obj.js';
#include "obj.h"
//

#include <string>
#include <memory>
#include <vector>

#include "dll_export.h"

namespace ol {
namespace events {

class EventTarget;
class Event;


/**
 * Key to use with {@link module:ol/Observable~Observable#unByKey}.
 * @typedef {Object} EventsKey
 * @property {Object} [bindTo]
 * @property {module:ol/events~ListenerFunction} [boundListener]
 * @property {boolean} callOnce
 * @property {number} [deleteIndex]
 * @property {module:ol/events~ListenerFunction} listener
 * @property {EventTarget|module:ol/events/EventTarget} target
 * @property {string} type
 * @api
 */

class EventsKey {};


/**
 * Listener function. This function is called with an event object as argument.
 * When the function returns `false`, event propagation will stop.
 *
 * @typedef {function(module:ol/events/Event)|function(module:ol/events/Event): boolean} ListenerFunction
 * @api
 */
class ListenerFunction {
public:
    virtual bool operator () (ol::events::Event const &evt) { return true; };
};

typedef std::shared_ptr<ListenerFunction> ListenerF;

/**
 * @param {module:ol/events~EventsKey} listenerObj Listener object.
 * @return {module:ol/events~ListenerFunction} Bound listener.
 */
void  OLQT_EXPORT * bindListener(EventsKey *listenerObj);
//
//
///**
// * Finds the matching {@link module:ol/events~EventsKey} in the given listener
// * array.
// *
// * @param {!Array<!module:ol/events~EventsKey>} listeners Array of listeners.
// * @param {!Function} listener The listener function.
// * @param {Object=} opt_this The `this` value inside the listener.
// * @param {boolean=} opt_setDeleteIndex Set the deleteIndex on the matching
// *     listener, for {@link module:ol/events~unlistenByKey}.
// * @return {module:ol/events~EventsKey|undefined} The matching listener object.
// */
//export function findListener(listeners, listener, opt_this, opt_setDeleteIndex) {
//  let listenerObj;
//  for (let i = 0, ii = listeners.length; i < ii; ++i) {
//    listenerObj = listeners[i];
//    if (listenerObj.listener === listener &&
//        listenerObj.bindTo === opt_this) {
//      if (opt_setDeleteIndex) {
//        listenerObj.deleteIndex = i;
//      }
//      return listenerObj;
//    }
//  }
//  return undefined;
//}


/**
 * @param {module:ol/events/EventTarget~EventTargetLike} target Target.
 * @param {string} type Type.
 * @return {Array.<module:ol/events~EventsKey>|undefined} Listeners.
 */
std::vector<EventsKey> OLQT_EXPORT getListeners(EventTarget *target, std::string type);


/**
 * Clean up all listener objects of the given type.  All properties on the
 * listener objects will be removed, and if no listeners remain in the listener
 * map, it will be removed from the target.
 * @param {module:ol/events/EventTarget~EventTargetLike} target Target.
 * @param {string} type Type.
 */
void removeListeners(EventTarget &target, std::string type);


/**
 * Registers an event listener on an event target. Inspired by
 * {@link https://google.github.io/closure-library/api/source/closure/goog/events/events.js.src.html}
 *
 * This function efficiently binds a `listener` to a `this` object, and returns
 * a key for use with {@link module:ol/events~unlistenByKey}.
 *
 * @param {module:ol/events/EventTarget~EventTargetLike} target Event target.
 * @param {string} type Event type.
 * @param {module:ol/events~ListenerFunction} listener Listener.
 * @param {Object=} opt_this Object referenced by the `this` keyword in the
 *     listener. Default is the `target`.
 * @param {boolean=} opt_once If true, add the listener as one-off listener.
 * @return {module:ol/events~EventsKey} Unique key for the listener.
 */
EventsKey OLQT_EXPORT listen(EventTarget *target, std::string type, ListenerF listener, void *opt_this = 0, bool opt_once = false);


/**
 * Registers a one-off event listener on an event target. Inspired by
 * {@link https://google.github.io/closure-library/api/source/closure/goog/events/events.js.src.html}
 *
 * This function efficiently binds a `listener` as self-unregistering listener
 * to a `this` object, and returns a key for use with
 * {@link module:ol/events~unlistenByKey} in case the listener needs to be
 * unregistered before it is called.
 *
 * When {@link module:ol/events~listen} is called with the same arguments after this
 * function, the self-unregistering listener will be turned into a permanent
 * listener.
 *
 * @param {module:ol/events/EventTarget~EventTargetLike} target Event target.
 * @param {string} type Event type.
 * @param {module:ol/events~ListenerFunction} listener Listener.
 * @param {Object=} opt_this Object referenced by the `this` keyword in the
 *     listener. Default is the `target`.
 * @return {module:ol/events~EventsKey} Key for unlistenByKey.
 */
EventsKey OLQT_EXPORT listenOnce(EventTarget *target, std::string type, ListenerF listener, void *opt_this = 0);


/**
 * Unregisters an event listener on an event target. Inspired by
 * {@link https://google.github.io/closure-library/api/source/closure/goog/events/events.js.src.html}
 *
 * To return a listener, this function needs to be called with the exact same
 * arguments that were used for a previous {@link module:ol/events~listen} call.
 *
 * @param {module:ol/events/EventTarget~EventTargetLike} target Event target.
 * @param {string} type Event type.
 * @param {module:ol/events~ListenerFunction} listener Listener.
 * @param {Object=} opt_this Object referenced by the `this` keyword in the
 *     listener. Default is the `target`.
 */
void OLQT_EXPORT unlisten(EventTarget *target, std::string type, ListenerF listener, void *opt_this = 0);


/**
 * Unregisters event listeners on an event target. Inspired by
 * {@link https://google.github.io/closure-library/api/source/closure/goog/events/events.js.src.html}
 *
 * The argument passed to this function is the key returned from
 * {@link module:ol/events~listen} or {@link module:ol/events~listenOnce}.
 *
 * @param {module:ol/events~EventsKey} key The key.
 */
void OLQT_EXPORT unlistenByKey(EventsKey const &key);


/**
 * Unregisters all event listeners on an event target. Inspired by
 * {@link https://google.github.io/closure-library/api/source/closure/goog/events/events.js.src.html}
 *
 * @param {module:ol/events/EventTarget~EventTargetLike} target Target.
 */
void OLQT_EXPORT unlistenAll(EventTarget *target);

}
}

#endif
