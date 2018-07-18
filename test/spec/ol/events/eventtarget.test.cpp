#include <gtest/gtest.h>
#include <typeinfo>

//
//import Disposable from '../../../../src/ol/Disposable.js';
#include "../../../../src/ol/Disposable.h"
//import {listen} from '../../../../src/ol/events.js';
#include "../../../../src/ol/events.h"
//import Event from '../../../../src/ol/events/Event.js';
#include "../../../../src/ol/events/Event.h"
//import EventTarget from '../../../../src/ol/events/EventTarget.js';
#include "../../../../src/ol/events/EventTarget.h"

using namespace ol::events;
using namespace ol;

class sinon {
public:
    class spy : public ol::events::ListenerFunction {
    public:
        spy() : called(0)
        {

        }

        virtual bool operator () (ol::events::Event &evt) override
        {
            return true;
        };

        size_t called;
        bool calledOnce() {
            return called == 1;
        }
    };
};

class Spy : public ol::events::ListenerFunction {
public:
    int id;
    std::vector<int> &called;
    std::vector<ol::events::Event> &events;

    Spy(int id, std::vector<int> &called, std::vector<ol::events::Event> &events) 
        : id(id), called(called), events(events) {}

    ~Spy()
    {
        std::cout << "Spy(): " << (void *)this << std::endl;
    }

    virtual bool operator () (ol::events::EventTarget *t, ol::events::Event &evt) override
    {
        called.push_back(id);
        events.push_back(evt);

        return true;
    };
};

//describe('ol.events.EventTarget', function() {

class ol_events_EventTarget : public ::testing::Test {
public:
    //  let called, events, eventTarget, spy1, spy2, spy3;
    EventTarget eventTarget;
    std::vector<int> called;
    std::vector<ol::events::Event> events;
    std::shared_ptr<Spy> spy1, spy2, spy3;

    ol_events_EventTarget() 
        : spy1(new Spy(1, called, events)) 
        , spy2(new Spy(2, called, events))
        , spy3(new Spy(3, called, events))
    {
        //
        //  beforeEach(function() {
        //    called = [];
        //    events = [];
        //    function spy(evt) {
        //      called.push(this.id);
        //      events.push(evt);
        //    }
        //    spy1 = spy.bind({id: 1});
        //    spy2 = spy.bind({id: 2});
        //    spy3 = spy.bind({id: 3});
        //    eventTarget = new EventTarget();
        //  });
        //
    }
};

TEST_F(ol_events_EventTarget, constructor)
{
    //  describe('constructor', function() {
    //    it('creates an instance', function() {
    {
        //      expect(eventTarget).to.be.a(EventTarget);
        EXPECT_TRUE(dynamic_cast<EventTarget *>(&eventTarget) != 0);
        //      expect(eventTarget).to.be.a(Disposable);
        EXPECT_TRUE(dynamic_cast<Disposable *>(&eventTarget) != 0);
    }
    //    });
    //    it('creates an empty listeners_ object', function() {
    {
        //      expect(Object.keys(eventTarget.listeners_)).to.have.length(0);
        EXPECT_EQ(0, eventTarget.listeners_.size());
    }
    //    });
    //  });
}

//  describe('#hasListener', function() {
TEST_F(ol_events_EventTarget, hasListener) 
{
    //    it('reports any listeners when called without argument', function() {
    {
        //      expect(eventTarget.hasListener()).to.be(false);
        EXPECT_FALSE(eventTarget.hasListener());
        //      eventTarget.listeners_['foo'] = [function() {}];
        eventTarget.listeners_["foo"] = { ol::events::ListenerF() };
        //      expect(eventTarget.hasListener()).to.be(true);
        EXPECT_TRUE(eventTarget.hasListener());
    }
    //    });
    //    it('reports listeners for the type passed as argument', function() {
    {
        //      eventTarget.listeners_['foo'] = [function() {}];
        eventTarget.listeners_["foo"] = { ol::events::ListenerF() };
        //      expect(eventTarget.hasListener('foo')).to.be(true);
        EXPECT_TRUE(eventTarget.hasListener("foo"));
        //      expect(eventTarget.hasListener('bar')).to.be(false);
        EXPECT_FALSE(eventTarget.hasListener("bar"));
    }
    //    });
    //  });
}

//  describe('#getListeners', function() {
TEST_F(ol_events_EventTarget, getListeners)
{
    //    it('returns listeners for a type or undefined if none', function() {
    {
        //      expect(eventTarget.getListeners('foo')).to.be(undefined);
        EXPECT_EQ(0, eventTarget.getListeners("foo").size());
        //      const listeners = [function() {}];
        std::vector<ol::events::ListenerF> listeners = { ol::events::ListenerF() };
        eventTarget.listeners_["foo"] = listeners;
        //      expect(eventTarget.getListeners('foo')).to.equal(listeners);
        EXPECT_EQ(listeners, eventTarget.getListeners("foo"));
    }
    //    });
    //  });
}

//  describe('#addEventListener()', function() {
TEST_F(ol_events_EventTarget, addEventListener)
{
    //    it('has listeners for each registered type', function() {
    {
        //      eventTarget.addEventListener('foo', spy1);
        eventTarget.addEventListener("foo", spy1);
        //      eventTarget.addEventListener('bar', spy2);
        eventTarget.addEventListener("bar", spy2);
        //      expect(eventTarget.hasListener('foo')).to.be(true);
        EXPECT_TRUE(eventTarget.hasListener("foo"));
        //      expect(eventTarget.hasListener('bar')).to.be(true);
        EXPECT_TRUE(eventTarget.hasListener("bar"));
    }
    //    });
    //  });
}

//  describe('#removeEventListener()', function() {
TEST_F(ol_events_EventTarget, removeEventListener)
{
    //    it('keeps the listeners registry clean', function() {
    {
        eventTarget.addEventListener("foo", spy1);
        eventTarget.removeEventListener("foo", spy1);
        EXPECT_EQ(false, eventTarget.hasListener("foo"));
    }
    //    });
    //    it('removes added listeners from the listeners registry', function() {
    {
        eventTarget.addEventListener("foo", spy1);
        eventTarget.addEventListener("foo", spy2);
        eventTarget.removeEventListener("foo", spy1);
        EXPECT_EQ(1, eventTarget.getListeners("foo").size());
    }
    //    });
    //  });
}

//  describe('#dispatchEvent()', function() {
TEST_F(ol_events_EventTarget, dispatchEvent)
{
    //    it('calls listeners in the correct order', function() {
    {
        eventTarget.addEventListener("foo", spy1);
        eventTarget.addEventListener("foo", spy2);
        eventTarget.dispatchEvent("foo");
        //      expect(called).to.eql([1, 2]);
        ASSERT_EQ(2, called.size());
        EXPECT_EQ(1, called[0]);
        EXPECT_EQ(2, called[1]);
    }
}

class Spy2 : public ol::events::ListenerFunction {
public:
    ol::events::ListenerF prev;
    Spy2(ol::events::ListenerF prev) : prev(prev) {}

    virtual bool operator () (ol::events::EventTarget *that, ol::events::Event &evt) { 
        prev->operator()(that, evt);
        return false; 
    };
};

TEST_F(ol_events_EventTarget, dispatchEvent2)
{
    //    it('stops propagation when listeners return false', function() {
    {
        eventTarget.addEventListener("foo", spy1);
        eventTarget.addEventListener("foo", ListenerF(new Spy2(spy2)));
        eventTarget.addEventListener("foo", spy3);
        eventTarget.dispatchEvent("foo");
        EXPECT_EQ(std::vector<int>({ 1, 2 }), called);
    }
}

class Spy3 : public ol::events::ListenerFunction {
public:
    ol::events::ListenerF prev;
    Spy3(ol::events::ListenerF prev) : prev(prev) {}

    virtual bool operator () (ol::events::EventTarget *that, ol::events::Event &evt) 
    {
        prev->operator()(that, evt);
        evt.preventDefault();
        return true;
    };
};

TEST_F(ol_events_EventTarget, dispatchEvent3)
{
    //    it('stops propagation when listeners call preventDefault()', function() {
    eventTarget.addEventListener("foo", ListenerF(new Spy3(spy2)));
    eventTarget.addEventListener("foo", spy1);
    eventTarget.dispatchEvent("foo");
    EXPECT_EQ(1, called.size());
    EXPECT_EQ(2, called[0]);
}

TEST_F(ol_events_EventTarget, dispatchEvent4)
{
    //    it('passes a default ol.events.Event object to listeners', function() {
    eventTarget.addEventListener("foo", spy1);
    eventTarget.dispatchEvent("foo");

    ASSERT_EQ(1, events.size());
    EXPECT_EQ(typeid(Event), typeid(events[0]));
    EXPECT_EQ("foo", events[0].type);
    EXPECT_EQ(&eventTarget, events[0].target);
    //    });
}

TEST_F(ol_events_EventTarget, dispatchEvent5)
{
    //    it('passes a custom event object with target to listeners', function() {
    eventTarget.addEventListener("foo", spy1);
    auto event = Event("foo");

    eventTarget.dispatchEvent(event);
    EXPECT_EQ(event.type, events[0].type);
    EXPECT_EQ(&eventTarget, events[0].target);
    //    });
}

class Spy6 : public ListenerFunction {
public:
    ListenerF p1, p2, p3;
    Spy6(ListenerF p1, ListenerF p2, ListenerF p3) : p1(p1), p2(p2), p3(p3) {}

    virtual bool operator () (EventTarget *that, Event &evt) override 
    {
        that->removeEventListener(evt.type, p1);
        that->removeEventListener(evt.type, p2);
        that->removeEventListener(evt.type, p3);
        return true;
    };
};


//    it('is safe to remove listeners in listeners', function() {
TEST_F(ol_events_EventTarget, dispatchEvent6)
{

    eventTarget.addEventListener("foo", spy3);
    //      eventTarget.addEventListener('foo', function() {
    //        eventTarget.removeEventListener('foo', spy1);
    //        eventTarget.removeEventListener('foo', spy2);
    //        eventTarget.removeEventListener('foo', spy3);
    //      });
    eventTarget.addEventListener("foo", ListenerF(new Spy6(spy1, spy2, spy3)));
    eventTarget.addEventListener("foo", spy1);
    eventTarget.addEventListener("foo", spy2);
    //      expect(function() {
    //        eventTarget.dispatchEvent('foo');
    //      }).not.to.throwException();
    EXPECT_NO_THROW(eventTarget.dispatchEvent("foo"));

    //      expect(called).to.eql([3]);
    ASSERT_EQ(1, called.size());
    EXPECT_EQ(3, called[0]);
    //      expect(eventTarget.getListeners('foo')).to.have.length(1);
    EXPECT_EQ(1, eventTarget.getListeners("foo").size());
    //    });
}


class Weird : public ListenerFunction {
public:
    ListenerF p1, p2, p3;
    Weird(ListenerF p1, ListenerF p2) : p1(p1), p2(p2) {}

    virtual bool operator () (EventTarget *that, Event &evt) override
    {
        //        eventTarget.removeEventListener('foo', weird);
        //        eventTarget.removeEventListener('foo', spy1);
        //        eventTarget.dispatchEvent('foo');
        //        eventTarget.removeEventListener('foo', spy2);
        //        eventTarget.dispatchEvent('foo');
        //        evt.preventDefault();
        that->removeEventListener(evt.type, p1);
        that->removeEventListener(evt.type, p2);
        return true;
    };
};


TEST_F(ol_events_EventTarget, dispatchEvent7)
{
    return; // TODO: implement

    //    it('is safe to do weird things in listeners', function() {
    //      eventTarget.addEventListener('foo', spy2);
    eventTarget.addEventListener("foo", spy2);
    //      eventTarget.addEventListener('foo', function weird(evt) {
    //        eventTarget.removeEventListener('foo', weird);
    //        eventTarget.removeEventListener('foo', spy1);
    //        eventTarget.dispatchEvent('foo');
    //        eventTarget.removeEventListener('foo', spy2);
    //        eventTarget.dispatchEvent('foo');
    //        evt.preventDefault();
    //      });

    ListenerF weird = ListenerF(new Weird(spy1, spy2));
    eventTarget.addEventListener("foo", weird);
    //      eventTarget.addEventListener('foo', spy1);
    eventTarget.addEventListener("foo", spy1);
    //      expect(function() {
    //        eventTarget.dispatchEvent('foo');
    //      }).not.to.throwException();
    EXPECT_NO_THROW(eventTarget.dispatchEvent("foo"));
    //      expect(called).to.eql([2, 2]);
    EXPECT_EQ(std::vector<int>({ 2, 2 }), called);
    //      expect(eventTarget.getListeners('foo')).to.be(undefined);
    EXPECT_EQ(0, eventTarget.getListeners("foo").size());
    //    });
    //  });
}

//  describe('#dispose()', function() {
TEST_F(ol_events_EventTarget, dispose)
{
    return; // TODO: implement
    //    it('cleans up foreign references', function() {
    //      listen(eventTarget, 'foo', spy1, document);
    ol::events::listen(&eventTarget, "foo", spy1, 0);
    //      expect(eventTarget.hasListener('foo')).to.be(true);
    EXPECT_TRUE(eventTarget.hasListener("foo"));
    //      eventTarget.dispose();
    eventTarget.dispose();
    //      expect(eventTarget.hasListener('foo')).to.be(false);
    EXPECT_FALSE(eventTarget.hasListener("foo"));
    //    });
    //  });
    //});
}
