#include <gtest/gtest.h>

//import Event, {preventDefault, stopPropagation} from '../../../../src/ol/events/Event.js';
#include "../../../../src/ol/events/Event.h"

using namespace ol::events;

//
//describe('ol.events.Event', function() {

TEST(ol_events_Event, constructor)
{
    //  describe('constructor', function() {
    //    it('takes a type as argument', function() {
    {
        auto event = Event("foo");
        EXPECT_EQ("foo", event.type);
    }
    //    });
    //    it('does not set the propagationStopped flag', function() {
    {
        //      const event = new Event('foo');
        auto event = Event("foo");
        //      expect(event.propagationStopped).to.be(undefined);
        EXPECT_FALSE(event.propagationStopped);
    }
    //    });
    //  });
}
//  describe('#preventDefault', function() {
TEST(ol_events_Event, preventDefault)
{
    //    it('sets the propagationStopped flag', function() {
    {
        //      const event = new Event('foo');
        auto event = Event("foo");
        event.preventDefault();

        //      expect(event.propagationStopped).to.be(true);
        EXPECT_TRUE(event.propagationStopped);
        //    });
    }
    //    it('is the same as #stopPropagation', function() {
    {
        //      const event = new Event('foo');
        auto event = Event("foo");
        //      expect(event.stopPropagation).to.equal(event.preventDefault);
        //    });
    }
    //  });
}

//  describe('ol.events.Event.preventDefault', function() {
TEST(ol_events_Event, preventDefault2)
{
    //    it('calls preventDefault on the event object', function() {
    //      const event = {
    //        preventDefault: sinon.spy()
    //      };
    //      preventDefault(event);
    //      expect(event.preventDefault.called).to.be(true);
    //    });
    //  });
}

//  describe('ol.events.Event.stopPropagation', function() {
TEST(ol_events_Event, stopPropagation)
{
    //    it('calls preventDefault on the event object', function() {
    //      const event = {
    //        stopPropagation: sinon.spy()
    //      };
    //      stopPropagation(event);
    //      expect(event.stopPropagation.called).to.be(true);
    //    });
    //  });
}
//});
