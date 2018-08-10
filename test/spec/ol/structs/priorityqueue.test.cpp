#include <gtest/gtest.h>

//import PriorityQueue, {DROP} from '../../../../src/ol/structs/PriorityQueue.js';
#include "../../../../src/ol/structs/PriorityQueue.h"

using namespace ol::structs;

template <typename T>
ol::number_t identity(T const &self)
{
    return ol::number_t(self);
}

template <typename T>
std::string key(T const &self)
{
    return std::to_string(self);
}

class ol_structs_PriorityQueue : public ::testing::Test 
{
public:
    ol_structs_PriorityQueue()
    {}
};

//
//
//describe('ol.structs.PriorityQueue', function() {
//
//  const identity = function(a) {
//    return a;
//  };
//
//  describe('when empty', function() {

TEST(ol_structs_PriorityQueue, t1)
{
    //
    //    let pq;
    //    beforeEach(function() {
    //      pq = new PriorityQueue(identity, identity);
    //    });
    //
    //    it('is empty', function() {
    {
        PriorityQueue<int, ol::number_t(int const &), std::string(int const &)> pq(identity<int>, key<int>);
        //      expect(pq.isEmpty()).to.be(true);
        EXPECT_TRUE(pq.isEmpty());
    }
    //    });
    //
    //    it('enqueue adds an element', function() {
    {
        PriorityQueue<int, ol::number_t(int const &), std::string(int const &)> pq(identity<int>, key<int>);

        bool added = pq.enqueue(0);
        EXPECT_TRUE(added);
        EXPECT_EQ(1, pq.elements_.size()); // .to.eql([0]);
        EXPECT_EQ(0, pq.elements_[0]);

        EXPECT_EQ(1, pq.priorities_.size());
        EXPECT_EQ(0, pq.priorities_[0]);
    }
    //    });
    //
    //    it('do not enqueue element with DROP priority', function() {
    //      const added = pq.enqueue(Infinity);
    //      expect(added).to.be(false);
    //      expect(pq.elements_).to.eql([]);
    //      expect(pq.priorities_).to.eql([]);
    //    });
    //
    //  });
}

//  describe('when populated', function() {
//
//    let elements, pq;
//    beforeEach(function() {
//      elements = [];
//      pq = new PriorityQueue(identity, identity);
//      let element, i;
//      for (i = 0; i < 32; ++i) {
//        element = Math.random();
//        pq.enqueue(element);
//        elements.push(element);
//      }
//    });
//
//    it('dequeues elements in the correct order', function() {
//      elements.sort();
//      let i;
//      for (i = 0; i < elements.length; ++i) {
//        expect(pq.dequeue()).to.be(elements[i]);
//      }
//      expect(pq.isEmpty()).to.be(true);
//    });
//
//  });
//
//  describe('with an impure priority function', function() {
//
//    let pq, target;
//    beforeEach(function() {
//      target = 0.5;
//      pq = new PriorityQueue(function(element) {
//        return Math.abs(element - target);
//      }, identity);
//      let i;
//      for (i = 0; i < 32; ++i) {
//        pq.enqueue(Math.random());
//      }
//    });
//
//    it('dequeue elements in the correct order', function() {
//      let lastDelta = 0;
//      let delta;
//      while (!pq.isEmpty()) {
//        delta = Math.abs(pq.dequeue() - target);
//        expect(lastDelta <= delta).to.be(true);
//        lastDelta = delta;
//      }
//    });
//
//    it('allows reprioritization', function() {
//      const target = 0.5;
//      pq.reprioritize();
//      let lastDelta = 0;
//      let delta;
//      while (!pq.isEmpty()) {
//        delta = Math.abs(pq.dequeue() - target);
//        expect(lastDelta <= delta).to.be(true);
//        lastDelta = delta;
//      }
//    });
//
//    it('allows dropping during reprioritization', function() {
//      const target = 0.5;
//      let i = 0;
//      pq.priorityFunction_ = function(element) {
//        if (i++ % 2 === 0) {
//          return Math.abs(element - target);
//        } else {
//          return DROP;
//        }
//      };
//      pq.reprioritize();
//      expect(pq.getCount()).to.be(16);
//      let lastDelta = 0;
//      let delta;
//      while (!pq.isEmpty()) {
//        delta = Math.abs(pq.dequeue() - target);
//        expect(lastDelta <= delta).to.be(true);
//        lastDelta = delta;
//      }
//    });
//
//  });
//
//  describe('tracks elements in the queue', function() {
//
//    let pq;
//    beforeEach(function() {
//      pq = new PriorityQueue(identity, identity);
//      pq.enqueue('a');
//      pq.enqueue('b');
//      pq.enqueue('c');
//    });
//
//    it('tracks which elements have been queued', function() {
//      expect(pq.isQueued('a')).to.be(true);
//      expect(pq.isQueued('b')).to.be(true);
//      expect(pq.isQueued('c')).to.be(true);
//    });
//
//    it('tracks which elements have not been queued', function() {
//      expect(pq.isQueued('d')).to.be(false);
//    });
//
//    it('raises an error when an queued element is re-queued', function() {
//      expect(function() {
//        pq.enqueue('a');
//      }).to.throwException();
//    });
//
//    it('tracks which elements have be dequeued', function() {
//      expect(pq.isQueued('a')).to.be(true);
//      expect(pq.isQueued('b')).to.be(true);
//      expect(pq.isQueued('c')).to.be(true);
//      expect(pq.dequeue()).to.be('a');
//      expect(pq.isQueued('a')).to.be(false);
//      expect(pq.isQueued('b')).to.be(true);
//      expect(pq.isQueued('c')).to.be(true);
//      expect(pq.dequeue()).to.be('b');
//      expect(pq.isQueued('a')).to.be(false);
//      expect(pq.isQueued('b')).to.be(false);
//      expect(pq.isQueued('c')).to.be(true);
//      expect(pq.dequeue()).to.be('c');
//      expect(pq.isQueued('a')).to.be(false);
//      expect(pq.isQueued('b')).to.be(false);
//      expect(pq.isQueued('c')).to.be(false);
//    });
//
//  });
//
//});
