#ifndef OL_EVENTS_EVENT_H
#define OL_EVENTS_EVENT_H
/**
 * @module ol/events/Event
 */

#include "EventType.h"
#include "../dll_export.h"

namespace ol {
namespace events {

/**
 * @classdesc
 * Stripped down implementation of the W3C DOM Level 2 Event interface.
 * @see {@link https://www.w3.org/TR/DOM-Level-2-Events/events.html#Events-interface}
 *
 * This implementation only provides `type` and `target` properties, and
 * `stopPropagation` and `preventDefault` methods. It is meant as base class
 * for higher level events defined in the library, and works with
 * {@link module:ol/events/EventTarget~EventTarget}.
 *
 * @constructor
 * @param {string} type Type.
 */

class OLQT_EXPORT Event 
{
public:
    EventType::_type type;
    void *target;
    bool propagationStopped;

    Event(EventType::_type type) 
        : type(type), target(0), propagationStopped()
    {
        //const Event = function(type) {
        //
        //  /**
        //   * @type {boolean}
        //   */
        //  this.propagationStopped;
        //
        //  /**
        //   * The event type.
        //   * @type {string}
        //   * @api
        //   */
        //  this.type = type;
        //
        //  /**
        //   * The event target.
        //   * @type {Object}
        //   * @api
        //   */
        //  this.target = null;
        //
    }

    virtual ~Event();
    
    /**
     * Stop event propagation.
     * @function
     * @api
     */
    virtual void preventDefault() {}
    
      /**
       * Stop event propagation.
       * @function
       * @api
       */
    virtual void stopPropagation() 
    {
        propagationStopped = true;
    }
    
    
    /**
     * @param {Event|module:ol/events/Event} evt Event
     */
    static void stopPropagation(Event *evt) 
    {
      evt->stopPropagation();
    }
    
    /**
     * @param {Event|module:ol/events/Event} evt Event
     */
    static void preventDefault(Event *evt) 
    {
      evt->preventDefault();
    }
};

//export default Event;
}
}
#endif // OL_EVENTS_EVENT_H
