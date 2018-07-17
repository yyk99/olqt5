///**
// * @module ol/Object
// */

#ifndef OL_OBJECT_H
#define OL_OBJECT_H

#include "optional.h"
#include "dll_export.h"

#include <string>
#include <map>

#include "jsport.h"

//import {getUid, inherits} from './util.js';
//import ObjectEventType from './ObjectEventType.js';
#include "ObjectEventType.h"
//import Observable from './Observable.js';
#include "Observable.h"
//import Event from './events/Event.js';
#include "events/Event.h"
//import {assign} from './obj.js';
//

namespace ol {

class value_t {
    std::string value_;
public:
    value_t() {}
    value_t(number_t n) : value_(std::to_string(n)) {}
    value_t(std::string s) : value_(s) {}
    value_t(const char *s) : value_(s) {}

    number_t to_number() const {
        return strtod(value_.c_str(), 0);
    }
    
    std::string to_string() const {
        return value_;
    }

    bool operator == (value_t const &other)
    {
        return this->value_ == other.value_;
    }

    bool operator != (value_t const &other)
    {
        return this->value_ != other.value_;
    }

};

typedef std::map<std::string, value_t> properties_t;

/**
 * @classdesc
 * Events emitted by {@link module:ol/Object~BaseObject} instances are instances of
 * this type.
 *
 * @param {string} type The event type.
 * @param {string} key The property name.
 * @param {*} oldValue The old value for `key`.
 * @extends {module:ol/events/Event}
 * @constructor
 */
class ObjectEvent : public events::Event
{
public:
    std::string key;
    value_t oldValue;
    //const ObjectEvent = function(type, key, oldValue) {
    ObjectEvent(events::EventType::_type type, std::string const &key, value_t const &oldValue)
        : events::Event(type), key(key), oldValue(oldValue)
    {
        //  Event.call(this, type);
        //
        //  /**
        //   * The name of the property whose value is changing.
        //   * @type {string}
        //   * @api
        //   */
        //  this.key = key;
        //
        //  /**
        //   * The old value. To get the new value use `e.target.get(e.key)` where
        //   * `e` is the event object.
        //   * @type {*}
        //   * @api
        //   */
        //  this.oldValue = oldValue;
    }
};

//inherits(ObjectEvent, Event);


/**
 * @classdesc
 * Abstract base class; normally only used for creating subclasses and not
 * instantiated in apps.
 * Most non-trivial classes inherit from this.
 *
 * This extends {@link module:ol/Observable} with observable
 * properties, where each property is observable as well as the object as a
 * whole.
 *
 * Classes that inherit from this have pre-defined properties, to which you can
 * add your owns. The pre-defined properties are listed in this documentation as
 * 'Observable Properties', and have their own accessors; for example,
 * {@link module:ol/Map~Map} has a `target` property, accessed with
 * `getTarget()` and changed with `setTarget()`. Not all properties are however
 * settable. There are also general-purpose accessors `get()` and `set()`. For
 * example, `get('target')` is equivalent to `getTarget()`.
 *
 * The `set` accessors trigger a change event, and you can monitor this by
 * registering a listener. For example, {@link module:ol/View~View} has a
 * `center` property, so `view.on('change:center', function(evt) {...});` would
 * call the function whenever the value of the center property changes. Within
 * the function, `evt.target` would be the view, so `evt.target.getCenter()`
 * would return the new center.
 *
 * You can add your own observable properties with
 * `object.set('prop', 'value')`, and retrieve that with `object.get('prop')`.
 * You can listen for changes on that property value with
 * `object.on('change:prop', listener)`. You can get a list of all
 * properties with {@link module:ol/Object~BaseObject#getProperties}.
 *
 * Note that the observable properties are separate from standard JS properties.
 * You can, for example, give your map object a title with
 * `map.title='New title'` and with `map.set('title', 'Another title')`. The
 * first will be a `hasOwnProperty`; the second will appear in
 * `getProperties()`. Only the second is observable.
 *
 * Properties can be deleted by using the unset method. E.g.
 * object.unset('foo').
 *
 * @constructor
 * @extends {module:ol/Observable}
 * @param {Object.<string, *>=} opt_values An object with key-value pairs.
 * @fires module:ol/Object~ObjectEvent
 * @api
 */

class OLQT_EXPORT BaseObject : public Observable
{
private:
    ol::properties_t values_;
public:
    typedef std::map<std::string, value_t> Options;

    BaseObject() {}

    BaseObject(Options const &opt_values)
    {
        //  Observable.call(this);
        //
        //  // Call {@link module:ol~getUid} to ensure that the order of objects' ids is
        //  // the same as the order in which they were created.  This also helps to
        //  // ensure that object properties are always added in the same order, which
        //  // helps many JavaScript engines generate faster code.
        //getUid(this);
        //
        //  /**
        //   * @private
        //   * @type {!Object.<string, *>}
        //   */
        //  this.values_ = {};
        //
        //  if (opt_values !== undefined) {
        setProperties(opt_values);
        //  }
    }
    //
    //inherits(BaseObject, Observable);
    //
    //
    /**
     * @type {Object.<string, string>}
     */
    std::map<std::string, std::string> changeEventTypeCache;
        
    /**
     * @param {string} key Key name.
     * @return {string} Change name.
     */
    std::string getChangeEventType(std::string key) 
    {
      return changeEventTypeCache.count(key) ?
        changeEventTypeCache[key] :
        (changeEventTypeCache[key] = "change:" + key);
    }
    
    /**
     * Gets a value.
     * @param {string} key Key name.
     * @return {*} Value.
     * @api
     */
    optional<value_t> get(std::string const &key)
    {
        for (auto const &p : values_) {
            if (p.first == key)
                return optional<value_t>(p.second);
        }
        return optional<value_t>();
    }
    
    
    /**
     * Get a list of object property names.
     * @return {Array.<string>} List of property names.
     * @api
     */
    std::vector<std::string> getKeys()
    {
        std::vector<std::string> keys;
        for (auto const &pp : values_)
            keys.push_back(pp.first);
        return keys;
    }
    
    /**
     * Get an object of all property names and values.
     * @return {Object.<string, *>} Object.
     * @api
     */
    ol::properties_t const &getProperties() const
    {
        return values_;
    }
    
    /**
     * @param {string} key Key name.
     * @param {*} oldValue Old value.
     */
    void notify(std::string const &key, ol::value_t const &oldValue)
    {
        auto eventType = getChangeEventType(key);
        dispatchEvent(ObjectEvent(eventType, key, oldValue));
        eventType = ObjectEventType::PROPERTYCHANGE;
        dispatchEvent(ObjectEvent(eventType, key, oldValue));
    }
    

    /**
     * Sets a value.
     * @param {string} key Key name.
     * @param {*} value Value.
     * @param {boolean=} opt_silent Update without triggering an event.
     * @api
     */
    void set(std::string const &key, value_t const &value, bool opt_silent = false)
    {
        if (opt_silent) {
            values_[key] = value;
        }
        else {
            value_t oldValue = values_[key];
            values_[key] = value;
            if (oldValue !=  value) {
                notify(key, oldValue);
            }
        }
    }
    
    
    /**
     * Sets a collection of key-value pairs.  Note that this changes any existing
     * properties and adds new ones (it does not remove any existing properties).
     * @param {Object.<string, *>} values Values.
     * @param {boolean=} opt_silent Update without triggering an event.
     * @api
     */
    void setProperties(Options const &values, bool opt_silent = false) {
        for (auto const &pp : values) {
            set(pp.first, pp.second, opt_silent);
        }
    }
    
    
    /**
     * Unsets a property.
     * @param {string} key Key name.
     * @param {boolean=} opt_silent Unset without triggering an event.
     * @api
     */
    void unset(std::string const &key, bool opt_silent = false)
    {
        if (values_.count(key) != 0) {
            auto oldValue = values_[key];
            values_.erase(key);
            if (!opt_silent) {
                notify(key, oldValue);
            }
        }
    }
};
//export default BaseObject;
} // namespace

#endif // OL_OBJECT_H
