#include <gtest/gtest.h>
#include <vector>

//import Tile from '../../../src/ol/Tile.js';
#include "../../../src/ol/Tile.h"
//import TileCache from '../../../src/ol/TileCache.js';
#include "../../../src/ol/TileCache.h"
//import {getKey} from '../../../src/ol/tilecoord.js';
#include "../../../src/ol/tilecoord.h"

using namespace ol;

TEST(ol_TileCache, t1)
{
    return; // TODO: implement

    //describe('ol.TileCache', function() {
    //
    //  describe('#pruneExceptNewestZ()', function() {
    //    it('gets rid of all entries that are not at the newest z', function() {
    {
        //      const tiles = [
        //        new Tile([0, 0, 0]),
        //        new Tile([1, 0, 0]),
        //        new Tile([1, 1, 0]),
        //        new Tile([2, 0, 0]),
        //        new Tile([2, 1, 0]),
        //        new Tile([2, 2, 0]),
        //        new Tile([2, 3, 0]) // newest tile at z: 2
        //      ];

        std::vector<Tile> tiles = {
                    Tile({0, 0, 0}),
                    Tile({1, 0, 0}),
                    Tile({1, 1, 0}),
                    Tile({2, 0, 0}),
                    Tile({2, 1, 0}),
                    Tile({2, 2, 0}),
                    Tile({2, 3, 0}) // newest tile at z: 2
        };

        //      const cache = new TileCache();
        auto cache = ol::TileCache();
        //
        //      sinon.spy(tiles[0], 'dispose');
        //
        //      tiles.forEach(function(tile) {
        //        cache.set(getKey(tile.tileCoord), tile);
        //      });

        for (auto tile : tiles) {
            cache.set(ol::tilecoord::getKey(tile.tileCoord), tile);
        }

        //
        cache.pruneExceptNewestZ();
        //
        //      expect(cache.getKeys()).to.eql([
        //        '2/3/0',
        //        '2/2/0',
        //        '2/1/0',
        //        '2/0/0'
        //      ]);
        auto keys = cache.getKeys();
        ASSERT_EQ(4, keys.size());
        EXPECT_EQ("2/3/0", keys[0]);
        EXPECT_EQ("2/2/0", keys[1]);
        EXPECT_EQ("2/1/0", keys[2]);
        EXPECT_EQ("2/0/0", keys[3]);
        //
        //      expect(tiles[0].dispose.calledOnce).to.be(true);
        //    });
    }
    //  });
    //});
}