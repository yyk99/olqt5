#include <gtest/gtest.h>
//import TileRange from '../../../src/ol/TileRange.js';
#include "../../../src/ol/TileRange.h"

using namespace ol;

//
//describe('ol.TileRange', function() {
//
TEST(ol_TileRange, constructor)
{
    //  describe('constructor', function() {
    //    it('creates a range', function() {
    {
        auto range = TileRange(1, 3, 2, 4);
        //      expect(range).to.be.a(TileRange);
    }
    //    });
    //
    //    it('can represent a range of one tile', function() {
    {
        auto range = TileRange(2, 2, 3, 3);
        EXPECT_EQ(1, range.getHeight());
        EXPECT_EQ(1, range.getWidth());
        //    });
    }
    //  });
}

TEST(ol_TileRange, contains) 
{
    //  describe('contains', function() {
    //    it('returns the expected value', function() {
    {
        auto tileRange = TileRange(1, 3, 1, 3);
        //      expect(tileRange.contains([0, 0, 0])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 0, 0 })));
        //      expect(tileRange.contains([0, 0, 1])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 0, 1 })));
        //      expect(tileRange.contains([0, 0, 2])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 0, 2 })));
        //      expect(tileRange.contains([0, 0, 3])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 0, 3 })));
        //      expect(tileRange.contains([0, 0, 4])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 0, 4 })));
        //      expect(tileRange.contains([0, 1, 0])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 1, 0 })));

        //      expect(tileRange.contains([0, 1, 1])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 1, 1 })));
        //      expect(tileRange.contains([0, 1, 2])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 1, 1 })));
        //      expect(tileRange.contains([0, 1, 3])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 1, 3 })));
        //      expect(tileRange.contains([0, 1, 4])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 1, 4 })));
        //      expect(tileRange.contains([0, 2, 0])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 2, 0 })));
        //      expect(tileRange.contains([0, 2, 1])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 2, 1 })));
        //      expect(tileRange.contains([0, 2, 2])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 2, 2 })));
        //      expect(tileRange.contains([0, 2, 3])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 2, 3 })));
        //      expect(tileRange.contains([0, 2, 4])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 2, 4 })));
        //      expect(tileRange.contains([0, 3, 0])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 3, 0 })));
        //      expect(tileRange.contains([0, 3, 1])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 3, 1 })));
        //      expect(tileRange.contains([0, 3, 2])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 3, 2 })));
        //      expect(tileRange.contains([0, 3, 3])).to.be.ok();
        EXPECT_TRUE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 3, 3 })));

        //      expect(tileRange.contains([0, 3, 4])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 3, 4 })));
        //      expect(tileRange.contains([0, 4, 0])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 4, 0 })));
        //      expect(tileRange.contains([0, 4, 1])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 4, 1 })));
        //      expect(tileRange.contains([0, 4, 2])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 4, 2 })));
        //      expect(tileRange.contains([0, 4, 3])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 4, 3 })));
        //      expect(tileRange.contains([0, 4, 4])).to.not.be();
        EXPECT_FALSE(tileRange.contains(ol::tilecoord::TileCoord({ 0, 4, 4 })));
    }
    //    });
    //  });
}

TEST(ol_TileRange, equals)
{
    //  describe('equals', function() {
    //    it('determines equivalence of two ranges', function() {
    {
        auto one = TileRange(0, 2, 1, 4);
        auto same = TileRange(0, 2, 1, 4);
        auto diff1 = TileRange(0, 2, 1, 5);
        auto diff2 = TileRange(0, 3, 1, 4);
        auto diff3 = TileRange(0, 2, 2, 4);
        auto diff4 = TileRange(1, 2, 1, 4);
        //      expect(one.equals(same)).to.be(true);
        EXPECT_TRUE(one.equals(same));
        //      expect(one.equals(diff1)).to.be(false);
        EXPECT_FALSE(one.equals(diff1));
        //      expect(one.equals(diff2)).to.be(false);
        EXPECT_FALSE(one.equals(diff2));
        //      expect(one.equals(diff3)).to.be(false);
        EXPECT_FALSE(one.equals(diff3));
        //      expect(one.equals(diff4)).to.be(false);
        EXPECT_FALSE(one.equals(diff4));
    }
    //    });
    //  });
}

TEST(ol_TileRange, extent)
{
    //
    //  describe('extent', function() {
    //    it('modifies range so it includes another', function() {
    {
        auto one = TileRange(0, 2, 1, 4);
        auto other = TileRange(-1, -3, 10, 12);
        one.extend(other);
        //
        EXPECT_EQ(-1, one.minX);
        EXPECT_EQ(2, one.maxX);
        EXPECT_EQ(1, one.minY);
        EXPECT_EQ(12, one.maxY);
    }
    //    });
    //  });
}

TEST(ol_TileRange, getSize) 
{
    //
    //  describe('getSize', function() {
    //    it('returns the expected size', function() {
    {
        auto tileRange = TileRange(0, 2, 1, 4);
        auto size = tileRange.getSize();
        //      expect(size).to.eql([3, 4]);
        ASSERT_EQ(2, size.size());
        EXPECT_EQ(3, size[0]);
        EXPECT_EQ(4, size[1]);
    }
    //    });
    //  });
}

TEST(ol_TileRange, intersects) 
{
    //
    //  describe('intersects', function() {
    //    it('determines if two ranges overlap', function() {
    {
        auto one = TileRange(0, 2, 1, 4);
        auto  overlapsRight = TileRange(2, 4, 1, 4);
        auto overlapsLeft = TileRange(-3, 0, 1, 4);
        auto overlapsTop = TileRange(0, 2, 4, 5);
        auto overlapsBottom = TileRange(0, 2, -3, 1);

        EXPECT_TRUE(one.intersects(overlapsLeft));
        EXPECT_TRUE(one.intersects(overlapsRight));
        EXPECT_TRUE(one.intersects(overlapsTop));
        EXPECT_TRUE(one.intersects(overlapsBottom));
        
        auto right = TileRange(3, 5, 1, 4);
        auto left = TileRange(-3, -1, 1, 4);
        auto above = TileRange(0, 2, 5, 6);
        auto below = TileRange(0, 2, -3, 0);

        EXPECT_FALSE(one.intersects(right));
        EXPECT_FALSE(one.intersects(left));
        EXPECT_FALSE(one.intersects(above));
        EXPECT_FALSE(one.intersects(below));
    }
    //    });
    //  });
}
//});
