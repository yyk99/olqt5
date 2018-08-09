#ifndef OL_EVENTS_EVENTTYPE_H
#define OL_EVENTS_EVENTTYPE_H

/**
* @module ol/events/EventType
*/

#include <string>

#include "../dll_export.h"

namespace ol {
namespace events {

/**
 * @enum {string}
 * @const
 */

struct EventType {
    typedef std::string _type;
    static _type CHANGE,// = "change";
        CLEAR, // 'clear',
        CONTEXTMENU, // 'contextmenu',
        CLICK, // 'click',
        DBLCLICK, // 'dblclick',
        DRAGENTER, // 'dragenter',
        DRAGOVER, // 'dragover',
        DROP, // 'drop',
        ERROR, // 'error',
        KEYDOWN, // 'keydown',
        KEYPRESS, // 'keypress',
        LOAD, // 'load',
        MOUSEDOWN, // 'mousedown',
        MOUSEMOVE, // 'mousemove',
        MOUSEOUT, // 'mouseout',
        MOUSEUP, // 'mouseup',
        MOUSEWHEEL, // 'mousewheel',
        MSPOINTERDOWN, // 'MSPointerDown',
        RESIZE, // 'resize',
        TOUCHSTART, // 'touchstart',
        TOUCHMOVE, // 'touchmove',
        TOUCHEND, // 'touchend',
        WHEEL; // 'wheel'
};

//export default {
//  /**
//   * Generic change event. Triggered when the revision counter is increased.
//   * @event module:ol/events/Event~Event#change
//   * @api
//   */
//  CHANGE: 'change',
//
//  CLEAR: 'clear',
//  CONTEXTMENU: 'contextmenu',
//  CLICK: 'click',
//  DBLCLICK: 'dblclick',
//  DRAGENTER: 'dragenter',
//  DRAGOVER: 'dragover',
//  DROP: 'drop',
//  ERROR: 'error',
//  KEYDOWN: 'keydown',
//  KEYPRESS: 'keypress',
//  LOAD: 'load',
//  MOUSEDOWN: 'mousedown',
//  MOUSEMOVE: 'mousemove',
//  MOUSEOUT: 'mouseout',
//  MOUSEUP: 'mouseup',
//  MOUSEWHEEL: 'mousewheel',
//  MSPOINTERDOWN: 'MSPointerDown',
//  RESIZE: 'resize',
//  TOUCHSTART: 'touchstart',
//  TOUCHMOVE: 'touchmove',
//  TOUCHEND: 'touchend',
//  WHEEL: 'wheel'
//};
}
}
#endif
