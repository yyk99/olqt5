#include <gtest/gtest.h>

//import {getUid} from '../../../src/ol/index.js';
#include "../../../src/ol/index.h"
//import ImageTile from '../../../src/ol/ImageTile.js';
#include "../../../src/ol/ImageTile.h"
//import Tile from '../../../src/ol/Tile.js';
#include "../../../src/ol/Tile.h"
//import TileState from '../../../src/ol/TileState.js';
#include "../../../src/ol/TileState.h"


//describe('ol.Tile', function() {
TEST(ol_Tile, constructor)
{
    //  describe('constructor', function()  {
    //    it('sets a default transition', function() {
    {
        ol::tilecoord::TileCoord coord = { 0, 0, 0 };
        auto tile = ol::Tile(coord, ol::TileState::IDLE);
        //      expect(tile.transition_).to.equal(250);
        EXPECT_EQ(250, tile.transition_);
    }
    //    });
    //
    //    it('allows the transition to be set', function() {
    {
        ol::tilecoord::TileCoord coord = { 0, 0, 0 };
        ol::number_t transition = 500;
        auto tile = ol::Tile(coord, ol::TileState::IDLE, ol::Tile::Options(transition));
        //      expect(tile.transition_).to.equal(transition);
        EXPECT_EQ(transition, tile.transition_);
    }
    //    });
    //  });
}

//  describe('#getAlpha()', function() {
TEST(ol_Tile, getAlpha)
{
    //    it('returns the alpha value for a tile in transition', function() {
    //      const coord = [0, 0, 0];
    ol::tilecoord::TileCoord coord = { 0,0,0 };
    //      const tile = new Tile(coord, TileState.IDLE);
    auto tile = ol::Tile(coord, ol::TileState::IDLE);
    ol::number_t id = 42; // 'test';
    ol::number_t time = 1533832490386; // Date.now();

    auto startAlpha = tile.getAlpha(id, time);
    EXPECT_TRUE(startAlpha > 0);
    EXPECT_TRUE(startAlpha < 1);

    time += tile.transition_ / 2;
    auto midAlpha = tile.getAlpha(id, time);
    EXPECT_TRUE(midAlpha > startAlpha);
    EXPECT_TRUE(midAlpha < 1);

    time += tile.transition_ / 2;
    auto endAlpha = tile.getAlpha(id, time);
    EXPECT_EQ(1, endAlpha);
}

TEST(ol_Tile, inTransition)
{
    //  describe('#inTransition()', function() {
    //    it('determines if the tile is in transition', function() {
    //      const coord = [0, 0, 0];
    //      const tile = new Tile(coord, TileState.IDLE);
    ol::tilecoord::TileCoord coord = { 0,0,0 };
    auto tile = ol::Tile(coord, ol::TileState::IDLE);
    //      const id = 'test';
    ol::number_t id = 42; // test
    //
    //      expect(tile.inTransition(id)).to.be(true);
    EXPECT_TRUE(tile.inTransition(42));
    tile.endTransition(id);
    EXPECT_FALSE(tile.inTransition(42));
}

#include <memory>

//  describe('interimChain', function() {
class ol_Tile_interimChain : public testing::Test
{
public:
    //    let head, renderTile;
    std::shared_ptr<ol::Tile> head, renderTile;
    ol::tilecoord::TileCoord tileCoord; // = [0, 0, 0];

    //    beforeEach(function() {
    //      const tileCoord = [0, 0, 0];
    //      head = new ImageTile(tileCoord, TileState.IDLE);
    //      getUid(head);
    //
    //      const addToChain = function(tile, state) {
    //        const next = new ImageTile(tileCoord, state);
    //        getUid(next);
    //        tile.interimTile = next;
    //        return next;
    //      };

    std::shared_ptr<ol::Tile> addToChain(std::shared_ptr<ol::Tile> tile, ol::TileState::_t state)
    {
        std::shared_ptr<ol::Tile> next = std::shared_ptr<ol::Tile>(new ol::ImageTile(tileCoord, state));
        ol::util::getUid(next);
        tile->interimTile = next;

        return next;
    }

    ol_Tile_interimChain()
        : tileCoord({ 0, 0, 0 })
        , head(new ol::ImageTile(tileCoord, ol::TileState::IDLE))
    {
        ol::util::getUid(head);
    }

    virtual void SetUp() override 
    {
        auto tail = addToChain(head, ol::TileState::IDLE); //discard, deprecated by head
        tail = addToChain(tail, ol::TileState::LOADING); //keep, request already going
        tail = addToChain(tail, ol::TileState::IDLE); //discard, deprecated by head
        tail = addToChain(tail, ol::TileState::LOADED); //keep, use for rendering
        renderTile = tail; //store this tile for later tests
        tail = addToChain(tail, ol::TileState::IDLE);  //rest of list outdated by tile above
        tail = addToChain(tail, ol::TileState::LOADED);
        tail = addToChain(tail, ol::TileState::LOADING);
        tail = addToChain(tail, ol::TileState::LOADED);
    }

    //      const chainLength = function(tile) {
    //        let c = 0;
    //        while (tile) {
    //          ++c;
    //          tile = tile.interimTile;
    //        }
    //        return c;
    //      };

    size_t chainLength(std::shared_ptr<ol::Tile> tile)
    {
        size_t c = 0;
        while (tile != 0) {
            std::cout << "(" << tile->ol_uid << ", state=" << tile->getState() << ") "; // DEBUG
            ++c;
            tile = tile->interimTile;
        }
        std::cout << std::endl; // DEBUG
        return c;
    }
};

//    it('shrinks tile chain correctly', function(done) {
TEST_F(ol_Tile_interimChain, t1)
{
    //      const chainLength = function(tile) {
    //        let c = 0;
    //        while (tile) {
    //          ++c;
    //          tile = tile.interimTile;
    //        }
    //        return c;
    //      };
    //
    //      expect(chainLength(head)).to.be(9);
    EXPECT_EQ(9, chainLength(head));
    head->refreshInterimChain();
    //      expect(chainLength(head)).to.be(3);
    EXPECT_EQ(3, chainLength(head));
    //      done();
}
//    });
//
//    it('gives the right tile to render', function(done) {
TEST_F(ol_Tile_interimChain, t2)
{

    //      expect(head.getInterimTile()).to.be(renderTile);
    EXPECT_EQ(renderTile, ol::Tile::getInterimTile(head));
    //      head.refreshInterimChain();
    head->refreshInterimChain();
    //      expect(head.getInterimTile()).to.be(renderTile);
    EXPECT_EQ(renderTile, ol::Tile::getInterimTile(head));
    //      done();
}
//    });
//
//    it('discards everything after the render tile', function(done) {
TEST_F(ol_Tile_interimChain, t3)
{

    head->refreshInterimChain();
    EXPECT_TRUE(renderTile->interimTile == 0); // .to.be(null);
    //      done();
}
//    });
//
//    it('preserves order of tiles', function(done) {
TEST_F(ol_Tile_interimChain, t4)
{

    head->refreshInterimChain();
    while (head->interimTile != 0) {
        //use property of ol.getUid returning increasing id's.
        EXPECT_TRUE(getUid(head) < getUid(head->interimTile));
        head = head->interimTile;
    }
    //      done();
}

