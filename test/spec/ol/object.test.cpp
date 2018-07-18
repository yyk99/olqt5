#include <gtest/gtest.h>
//import BaseObject from '../../../src/ol/Object.js';
#include "../../../src/ol/Object.h"
//import {listen} from '../../../src/ol/events.js';
#include "../../../src/ol/events.h"
//

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

using namespace ol;
using namespace events;

class ol_Object : public ::testing::Test {
public:
    BaseObject o;
    ol_Object() : o() {

    }
};

//describe('ol.Object', function() {
//
//  let o;
//  beforeEach(function() {
//    o = new BaseObject();
//  });
//
//  describe('get, set and unset', function() {
//
//    describe('get an unset property', function() {
TEST_F(ol_Object, t1)
{
    auto v = o.get("k");

    EXPECT_FALSE(v.has_value());
}

//    describe('get a set property', function() {
TEST_F(ol_Object, t2)
{
    //      let v;
    //      beforeEach(function() {
    //        o.set('k', 1);
    o.set("k", 1);
    //        v = o.get('k');
    auto v = o.get("k");
    //      });
    //
    //      it('returns expected value', function() {
    //        expect(v).to.eql(1);
    EXPECT_EQ(1, v.value().to_number());
    //      });
    //    });
}

//    describe('unset a set property', function() {
TEST_F(ol_Object, t3)
{
    //      beforeEach(function() {
    //        o.set('k', 1);
    o.set("k", 1);
    //      });
    //
    //      it('returns undefined', function() {
    //        const v = o.unset('k');
    o.unset("k");
    //        expect(v).to.be(undefined);
    auto v = o.get("k");
    EXPECT_FALSE(v.has_value());
    //      });
    //    });
}
//
//  describe('#get()', function() {
TEST_F(ol_Object, t4)
{
    //
    //    it('does not return values that are not explicitly set', function() {
    //      const o = new BaseObject();
    //      expect(o.get('constructor')).to.be(undefined);
    EXPECT_FALSE(o.get("constructor").has_value());
    //      expect(o.get('hasOwnProperty')).to.be(undefined);
    EXPECT_FALSE(o.get("hasOwnProperty").has_value());
    //      expect(o.get('isPrototypeOf')).to.be(undefined);
    EXPECT_FALSE(o.get("isPrototypeOf").has_value());
    //      expect(o.get('propertyIsEnumerable')).to.be(undefined);
    EXPECT_FALSE(o.get("propertyIsEnumerable").has_value());
    //      expect(o.get('toLocaleString')).to.be(undefined);
    EXPECT_FALSE(o.get("toLocaleString").has_value());
    //      expect(o.get('toString')).to.be(undefined);
    EXPECT_FALSE(o.get("toString").has_value());
    //      expect(o.get('valueOf')).to.be(undefined);
    EXPECT_FALSE(o.get("valueOf").has_value());
    //    });
    //
    //  });
}
//
//  describe('#set()', function() {
TEST_F(ol_Object, set)
{
    //    it('can be used with arbitrary names', function() {
    //      const o = new BaseObject();
    //
    //      o.set('set', 'sat');
    o.set("set", "sat");
    //      expect(o.get('set')).to.be('sat');
    EXPECT_EQ("sat", o.get("set").value().to_string());
    //
    //      o.set('get', 'got');
    o.set("get", "got");
    //      expect(o.get('get')).to.be('got');
    EXPECT_EQ("got", o.get("get").value().to_string());
    //
    //      o.set('toString', 'string');
    o.set("toString", "string");
    //      expect(o.get('toString')).to.be('string');
    EXPECT_EQ("string", o.get("toString").value().to_string());
    //      expect(typeof o.toString).to.be('function');
    //    });
    //  });
}

//  describe('#getKeys()', function() {
TEST_F(ol_Object, getKeys)
{
    //
    //    it('returns property names set at construction', function() {
    {
        //      const o = new BaseObject({
        //        prop1: 'val1',
        //        prop2: 'val2',
        //        toString: 'string',
        //        get: 'foo'
        //      });

        auto props = BaseObject::Options({
            {"prop1", "val1"},
            {"prop2", "val2"},
            {"toString", "string"},
            {"get", "foo"}
            });

        auto o = BaseObject(props);
        //
        //      const keys = o.getKeys();
        auto keys = o.getKeys();
        //      expect(keys.length).to.be(4);
        ASSERT_EQ(4, keys.size());
        std::sort(keys.begin(), keys.end());
        //      expect(keys.sort()).to.eql(['get', 'prop1', 'prop2', 'toString']);
        EXPECT_EQ("get", keys[0]);
        EXPECT_EQ("prop1", keys[1]);
        EXPECT_EQ("prop2", keys[2]);
        EXPECT_EQ("toString", keys[3]);
    }
    //    });
    //
    //  });
}

//  describe('setProperties', function() {
TEST_F(ol_Object, setProperties)
{
    //
    //    it('sets multiple values at once', function() {
    //      o.setProperties({
    //        k1: 1,
    //        k2: 2
    //      });
    auto props = BaseObject::Options({
        { "k1", 1 },
        { "k2", 2 } 
    });
    o.setProperties(props);

    //      expect(o.get('k1')).to.eql(1);
    EXPECT_EQ(1, o.get("k1").value().to_number());
    //      expect(o.get('k2')).to.eql(2);
    EXPECT_EQ(2, o.get("k2").value().to_number());
    //
    //      const keys = o.getKeys().sort();
    auto keys = o.getKeys(); std::sort(keys.begin(), keys.end());
    //      expect(keys).to.eql(['k1', 'k2']);
    ASSERT_EQ(2, keys.size());
    EXPECT_EQ("k1", keys[0]);
    EXPECT_EQ("k2", keys[1]);
    //    });
    //  });
}

//  describe('notify', function() {
TEST_F(ol_Object, notify)
{
    return; // TODO: Implement
    //
    //    let listener1, listener2;
    //
    //    beforeEach(function() {
    //      listener1 = sinon.spy();
    //      listen(o, 'change:k', listener1);
    //
    //      listener2 = sinon.spy();
    //      listen(o, 'propertychange', listener2);
    //    });
    //
    //    it('dispatches events', function() {
    {
        auto listener1 = std::shared_ptr<sinon::spy>(new sinon::spy());
        ol::events::listen(&o, "change:k", listener1);
        //      o.notify('k', 1);
        o.notify("k", 1);
        //      expect(listener1.calledOnce).to.be(true);
        EXPECT_TRUE(listener1->calledOnce());
        //      const args = listener1.firstCall.args;
        //      expect(args).to.have.length(1);
        //      const event = args[0];
        //      expect(event.key).to.be('k');
        //      expect(event.oldValue).to.be(1);
    }
    //    });
    //
    //    it('dispatches generic change events to bound objects', function() {
    {
        auto listener1 = std::shared_ptr<sinon::spy>(new sinon::spy());
        ol::events::listen(&o, "change:k", listener1);

        auto listener2 = std::shared_ptr<sinon::spy>(new sinon::spy());
        ol::events::listen(&o, "propertychange", listener2);

        //      o.notify('k', 1);
        o.notify("k", 1);
        //      expect(listener2.calledOnce).to.be(true);
        EXPECT_TRUE(listener2->calledOnce());
        //      const args = listener2.firstCall.args;
        //      expect(args).to.have.length(1);
        //      const event = args[0];
        //      expect(event.key).to.be('k');
        //      expect(event.oldValue).to.be(1);
    }
    //    });
    //  });
}
//  describe('set', function() {
TEST_F(ol_Object, set2)
{
    //
    //    let listener1, listener2;
    //
    //    beforeEach(function() {
    //      listener1 = sinon.spy();
    //      listen(o, 'change:k', listener1);
    //
    //      listener2 = sinon.spy();
    //      listen(o, 'propertychange', listener2);
    //    });
    //
    //    it('dispatches events to object', function() {
    //      o.set('k', 1);
    //      expect(listener1).to.be.called();
    //
    //      expect(o.getKeys()).to.eql(['k']);
    //    });
    //
    //    it('dispatches generic change events to object', function() {
    //      o.set('k', 1);
    //      expect(listener2.calledOnce).to.be(true);
    //      const args = listener2.firstCall.args;
    //      expect(args).to.have.length(1);
    //      const event = args[0];
    //      expect(event.key).to.be('k');
    //    });
    //
    //    it('dispatches events only if the value is different', function() {
    //      o.set('k', 1);
    //      o.set('k', 1);
    //      expect(listener1.calledOnce).to.be(true);
    //      expect(listener2.calledOnce).to.be(true);
    //    });
    //
    //  });
}

//  describe('setter', function() {
TEST_F(ol_Object, setter)
{
    //    beforeEach(function() {
    //      o.setX = function(x) {
    //        this.set('x', x);
    //      };
    //      sinon.spy(o, 'setX');
    //    });
    //
    //    it('does not call the setter', function() {
    //      o.set('x', 1);
    //      expect(o.get('x')).to.eql(1);
    //      expect(o.setX).to.not.be.called();
    //
    //      expect(o.getKeys()).to.eql(['x']);
    //    });
    //  });
}
//  describe('getter', function() {
TEST_F(ol_Object, getter)
{
    //    beforeEach(function() {
    //      o.getX = function() {
    //        return 1;
    //      };
    //      sinon.spy(o, 'getX');
    //    });
    //
    //    it('does not call the getter', function() {
    //      expect(o.get('x')).to.be(undefined);
    //      expect(o.getX).to.not.be.called();
    //    });
    //  });
}

//
//  describe('create with options', function() {
TEST_F(ol_Object, create_with_options)
{
    //    it('sets the property', function() {
    //      const o = new BaseObject({k: 1});
    //      expect(o.get('k')).to.eql(1);
    //
    //      expect(o.getKeys()).to.eql(['k']);
    //    });
    //  });
}

//  describe('case sensitivity', function() {
TEST_F(ol_Object, case_sensitivity) {
    //    let listener1, listener2;
    //
    //    beforeEach(function() {
    //      listener1 = sinon.spy();
    //      listen(o, 'change:k', listener1);
    //      listener2 = sinon.spy();
    //      listen(o, 'change:K', listener2);
    //    });
    //
    //    it('dispatches the expected event', function() {
    //      o.set('K', 1);
    //      expect(listener1).to.not.be.called();
    //      expect(listener2).to.be.called();
    //
    //      expect(o.getKeys()).to.eql(['K']);
    //    });
    //  });
}
//});
