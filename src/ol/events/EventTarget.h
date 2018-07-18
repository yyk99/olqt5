#ifndef OL_EVENTS_EVENTTARGTE_H
#define OL_EVENTS_EVENTTARGTE_H

#include <vector>
#include <string>
#include <map>

///**
// * @module ol/events/EventTarget
// */
//import {inherits} from '../util.js';
//import Disposable from '../Disposable.js';
#include "../Disposable.h"
//import {unlistenAll} from '../events.js';
#include "../events.h"
//import {UNDEFINED} from '../functions.js';
//import Event from '../events/Event.js';
#include "../events/Event.h"
#include "../jsport.h"

#include "../dll_export.h"

/**
 * @typedef {EventTarget|module:ol/events/EventTarget} EventTargetLike
 */


namespace ol {
namespace events {
/**
 * @classdesc
 * A simplified implementation of the W3C DOM Level 2 EventTarget interface.
 * @see {@link https://www.w3.org/TR/2000/REC-DOM-Level-2-Events-20001113/events.html#Events-EventTarget}
 *
 * There are two important simplifications compared to the specification:
 *
 * 1. The handling of `useCapture` in `addEventListener` and
 *    `removeEventListener`. There is no real capture model.
 * 2. The handling of `stopPropagation` and `preventDefault` on `dispatchEvent`.
 *    There is no event target hierarchy. When a listener calls
 *    `stopPropagation` or `preventDefault` on an event object, it means that no
 *    more listeners after this one will be called. Same as when the listener
 *    returns false.
 *
 * @constructor
 * @extends {module:ol/Disposable}
 */
class OLQT_EXPORT EventTarget : public ol::Disposable 
{
public: /* for testing and debugging */
    std::map<std::string, std::vector<ol::events::ListenerF> > listeners_;
    static std::vector<ol::events::ListenerF> Empty;
    std::map<std::string, int> pendingRemovals_;
    std::map<std::string, int> dispatching_;
public:
    //const EventTarget = function() {
    EventTarget() 
    {
        //
        //  Disposable.call(this);
        //
        //  /**
        //   * @private
        //   * @type {!Object.<string, number>}
        //   */
        //  this.pendingRemovals_ = {};
        //
        //  /**
        //   * @private
        //   * @type {!Object.<string, number>}
        //   */
        //  this.dispatching_ = {};
        //
        //  /**
        //   * @private
        //   * @type {!Object.<string, Array.<module:ol/events~ListenerFunction>>}
        //   */
        //  this.listeners_ = {};
        //
    }

    virtual ~EventTarget() {}
    //
    //inherits(EventTarget, Disposable);
    
    
    /**
     * @param {string} type Type.
     * @param {module:ol/events~ListenerFunction} listener Listener.
     */
    void addEventListener(std::string const &type, ol::events::ListenerF listener)
    {
        auto &listeners = listeners_[type];
        //if (listeners.indexOf(listener) === -1) {
        //  listeners.push(listener);
        //}
        listeners.push_back(listener); // TODO: check for duplication
    }
    
    /**
     * @param {{type: string,
     *     target: (EventTarget|module:ol/events/EventTarget|undefined)}|module:ol/events/Event|
     *     string} event Event or event type.
     * @return {boolean|undefined} `false` if anyone called preventDefault on the
     *     event object or if any of the listeners returned false.
     */
    virtual bool dispatchEvent(std::string const &s)
    {
        return dispatchEvent(ol::events::Event(s));
    }

    virtual bool dispatchEvent(ol::events::Event evt);
    
    
    /**
     * @inheritDoc
     */
    virtual void disposeInternal()
    {
        unlistenAll(this);
    }
    
    
    /**
     * Get the listeners for a specified event type. Listeners are returned in the
     * order that they will be called in.
     *
     * @param {string} type Type.
     * @return {Array.<module:ol/events~ListenerFunction>} Listeners.
     */
    std::vector<ol::events::ListenerF> const &getListeners(std::string const &type) const
    {
        if (listeners_.count(type) == 0)
            return Empty;
        return listeners_.at(type);
    }
    
    
    /**
     * @param {string=} opt_type Type. If not provided,
     *     `true` will be returned if this EventTarget has any listeners.
     * @return {boolean} Has listeners.
     */

    bool hasListener (std::string const &opt_type) const 
    {
        return listeners_.count(opt_type) > 0;
    };
    
    bool hasListener() const
    {
        return listeners_.size() > 0;
    }

    /**
     * @param {string} type Type.
     * @param {module:ol/events~ListenerFunction} listener Listener.
     */
    void removeEventListener(std::string const &type, ol::events::ListenerF listener);
};

//export default EventTarget;
} // events
} // ol
#endif // OL_EVENTS_EVENTTARGTE_H
