#ifndef OL_OBJECTEVENTTYPE_H
#define OL_OBJECTEVENTTYPE_H

#include <string>

namespace ol {

/**
 * @module ol/ObjectEventType
 */

 /**
  * @enum {string}
  */
struct ObjectEventType {
    /**
     * Triggered when a property is changed.
     * @event module:ol/Object~ObjectEvent#propertychange
     * @api
     */
    static std::string PROPERTYCHANGE; // : 'propertychange'
};

}
#endif // OL_OBJECTEVENTTYPE_H
