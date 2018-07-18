//
// ol/events/EventTarget.cpp
//

#include "EventTarget.h"

std::vector<ol::events::ListenerF>
ol::events::EventTarget::Empty = std::vector<ol::events::ListenerF>();

bool ol::events::EventTarget::dispatchEvent(ol::events::Event evt)
{
    //const evt = typeof event == = 'string' ? new Event(event) : event;
    auto type = evt.type;
    evt.target = this;

    auto pos = listeners_.find(type);
    if (pos == listeners_.end())
        return false;

    auto &listeners = pos->second;
    bool propagate = false;

    if (dispatching_.count(type) == 0) {
        dispatching_[type] = 0;
        pendingRemovals_[type] = 0;
    }
    ++dispatching_[type];
    for (auto &lp : listeners) {
        if (!lp)
            continue;
        if (lp->operator()(this, evt) == false || evt.propagationStopped) {
            propagate = false;
            break;
        }
    }
    --dispatching_[type];
    if (dispatching_[type] == 0) {
        auto pendingRemovals = pendingRemovals_[type];
        pendingRemovals_.erase(type);
        while (pendingRemovals--) {
            removeEventListener(type, ol::events::ListenerF());
        }
        dispatching_.erase(type);
    }
    return propagate;
}

void ol::events::EventTarget::removeEventListener(std::string const &type, ol::events::ListenerF listener)
{
    auto pos = listeners_.find(type);
    if (pos == listeners_.end())
        return;
    auto &listeners = pos->second;
    //const listeners = this.listeners_[type];
    //if (listeners) {
    //    const index = listeners.indexOf(listener);
    auto index = std::find(listeners.begin(), listeners.end(), listener);
    if (index == listeners.end())
        return;
    //    if (type in this.pendingRemovals_) {
    if (pendingRemovals_.count(type) != 0) {
        // make listener a no-op, and remove later in #dispatchEvent()
        *index = ol::events::ListenerF(0);
        ++pendingRemovals_[type];
    } else {
        listeners.erase(index);
        if (listeners.size() == 0)
            listeners_.erase(type);
    }
}
