#include <gtest/gtest.h>

//import {
//  quadKey,
//  getKey,
//  fromKey,
//  hash,
//  withinExtentAndZ
//} from '../../../src/ol/tilecoord.js';
#include "../../../src/ol/tilecoord.h"
//import TileGrid from '../../../src/ol/tilegrid/TileGrid.js';
#include "../../../src/ol/tilegrid/TileGrid.h"
//

using namespace ol::tilecoord;

//describe('ol.TileCoord', function() {
//  describe('create', function() {
TEST(ol_TileCoord, create)
{
    //    it('sets x y z properties as expected', function() {
    {
        TileCoord tileCoord = { 1, 2, 3 };
        ASSERT_EQ(3, tileCoord.size());
        EXPECT_EQ(1, tileCoord[0]);
        EXPECT_EQ(2, tileCoord[1]);
        EXPECT_EQ(3, tileCoord[2]);
    }
}
    //    });
    //  });
    //
    //  describe('call quadKey', function() {
TEST(ol_TileCoord, quadKey)
{
    //    it('returns expected string', function() {
    TileCoord tileCoord = { 3, 3, 5 };
    //      const s = quadKey(tileCoord);
    std::string s = quadKey(tileCoord);
    //      expect(s).to.eql('213');
    EXPECT_EQ("213", s);
    //    });
}

//  });

//  describe('getKey()', function() {
TEST(ol_TileCoord, getKey)
{
    //    it('returns a key for a tile coord', function() {
    auto key = getKey({ 1, 2, 3 });
    //      expect(key).to.eql('1/2/3');
    EXPECT_EQ("1/2/3", key);
    //    });
    //  });
}

//  describe('fromKey()', function() {
TEST(ol_TileCoord, fromKey)
{
    //    it('returns a tile coord given a key', function() {
    TileCoord tileCoord = { 1, 2, 3 };
    auto key = getKey(tileCoord);
//
//      const returned = fromKey(key);
    auto actual = fromKey(key);
//      expect(returned).to.eql(tileCoord);
    EXPECT_EQ(tileCoord, actual);
//    });
//  });
}

//  describe('hash', function() {
TEST(ol_TileCoord, hash)
{
    //    it('produces different hashes for different tile coords', function() {
    //      const tileCoord1 = [3, 2, 1];
    TileCoord tileCoord1 = { 3, 2, 1 };
    //      const tileCoord2 = [3, 1, 1];
    TileCoord tileCoord2 = { 3, 1, 1 };

    auto h1 = hash(tileCoord1);
    auto h2 = hash(tileCoord2);
    //      expect(hash(tileCoord1)).not.to.eql(
    //        hash(tileCoord2));
    EXPECT_TRUE(h1 != h2);
    //    });
    //  });
}

//  describe('withinExtentAndZ', function() {
TEST(ol_TileCoord, withinExtentAndZ)
{
    //
    //    it('restricts by z', function() {
    {
        //      const tileGrid = new TileGrid({
        //        extent: [10, 20, 30, 40],
        //        tileSize: 10,
        //        resolutions: [2, 1],
        //        minZoom: 1
        //      });

        ol::tilegrid::TileGrid::Options o;
        o.extent = { 10, 20, 30, 40 };
        o.tileSize = { 10, 10 };
        o.resolutions = { 2, 1 };
        o.minZoom = 1;

        ol::tilegrid::TileGrid tileGrid(o);

        //      expect(withinExtentAndZ([0, 0, -1], tileGrid)).to.be(false);
        //      expect(withinExtentAndZ([1, 0, -1], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([2, 0, -1], tileGrid)).to.be(false);
        EXPECT_FALSE(withinExtentAndZ({ 0, 0, -1 }, tileGrid));
        EXPECT_TRUE(withinExtentAndZ({ 1, 0, -1 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 2, 0, -1 }, tileGrid));
    }
    //    });
    //
    //    it('restricts by extent when extent defines tile ranges', function() {
    {
        //      const tileGrid = new TileGrid({
        //        extent: [10, 20, 30, 40],
        //        sizes: [[3, -3]],
        //        tileSize: 10,
        //        resolutions: [1]
        //      });
        ol::tilegrid::TileGrid::Options o;
        o.extent = { 10, 20, 30, 40 };
        o.sizes = { { 3, -3 } };
        o.tileSize = { 10, 10 };
        o.resolutions = { 1 };

        ol::tilegrid::TileGrid tileGrid(o);
        //      expect(withinExtentAndZ([0, 1, -2], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([0, 2, -1], tileGrid)).to.be(false);
        //      expect(withinExtentAndZ([0, 0, -3], tileGrid)).to.be(false);
        EXPECT_TRUE(withinExtentAndZ({ 0, 1, -2 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, 2, -1 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, 0, -3 }, tileGrid));
    }
    //    });
    //
    //    it('restricts by extent when sizes define tile ranges', function() {
    {
        //      const tileGrid = new TileGrid({
        //        origin: [10, 20],
        //        sizes: [[3, 3]],
        //        tileSize: 10,
        //        resolutions: [1]
        //      });
        ol::tilegrid::TileGrid::Options o;
        o.origin = { 10, 20 };
        o.sizes = { { 3, 3 } };
        o.tileSize = { 10,10 };
        o.resolutions = { 1 };
        ol::tilegrid::TileGrid tileGrid(o);
        //      expect(withinExtentAndZ([0, 0, 0], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([0, -1, 0], tileGrid)).to.be(false);
        //      expect(withinExtentAndZ([0, 0, -1], tileGrid)).to.be(false);
        //      expect(withinExtentAndZ([0, 2, 2], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([0, 3, 0], tileGrid)).to.be(false);
        //      expect(withinExtentAndZ([0, 0, 3], tileGrid)).to.be(false);
        EXPECT_TRUE(withinExtentAndZ({ 0, 0, 0 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, -1, 0 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, 0, -1 }, tileGrid));
        EXPECT_TRUE(withinExtentAndZ({ 0, 2, 2 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, 3, 0 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, 0, 3 }, tileGrid));
    }
    //    });
    //
    //    it('restricts by extent when sizes (neg y) define tile ranges', function() {
    {
        //      const tileGrid = new TileGrid({
        //        origin: [10, 40],
        //        sizes: [[3, -3]],
        //        tileSize: 10,
        //        resolutions: [1]
        //      });
        ol::tilegrid::TileGrid::Options o;
        o.origin = { 10, 40 };
        o.sizes = { { 3, -3 } };
        o.tileSize = { 10, 10 };
        o.resolutions = { 1 };
        ol::tilegrid::TileGrid tileGrid(o);
        //      expect(withinExtentAndZ([0, 0, -1], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([0, -1, -1], tileGrid)).to.be(false);
        //      expect(withinExtentAndZ([0, 0, 0], tileGrid)).to.be(false);
        //      expect(withinExtentAndZ([0, 2, -3], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([0, 3, -1], tileGrid)).to.be(false);
        //      expect(withinExtentAndZ([0, 0, -4], tileGrid)).to.be(false);
        EXPECT_TRUE(withinExtentAndZ({ 0, 0, -1 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, -1, -1 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, 0, 0 }, tileGrid));
        EXPECT_TRUE(withinExtentAndZ({ 0, 2, -3 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, 3, -1 }, tileGrid));
        EXPECT_FALSE(withinExtentAndZ({ 0, 0, -4 }, tileGrid));
    }
    //    });
    //
    //    it('does not restrict by extent with no extent or sizes', function() {
    {
        //      const tileGrid = new TileGrid({
        //        origin: [10, 20],
        //        tileSize: 10,
        //        resolutions: [1]
        //      });
        ol::tilegrid::TileGrid::Options o;
        o.origin = { 10, 20 };
        o.tileSize = { 10, 10 };
        o.resolutions = { 1 };
        ol::tilegrid::TileGrid tileGrid(o);
        //      expect(withinExtentAndZ([0, Infinity, 0], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([0, 0, Infinity], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([0, -Infinity, 0], tileGrid)).to.be(true);
        //      expect(withinExtentAndZ([0, 0, Infinity], tileGrid)).to.be(true);
        EXPECT_TRUE(withinExtentAndZ({ 0, std::numeric_limits<int>::infinity(), 0 }, tileGrid));
        EXPECT_TRUE(withinExtentAndZ({ 0, 0, -std::numeric_limits<int>::infinity() }, tileGrid));
        EXPECT_TRUE(withinExtentAndZ({ 0, -std::numeric_limits<int>::infinity(), 0 }, tileGrid));
        EXPECT_TRUE(withinExtentAndZ({ 0, 0, -std::numeric_limits<int>::infinity() }, tileGrid));
        //    });
    }
    //  });
}
//});
