#include <gtest/gtest.h>
//import {hasArea, toSize, buffer as bufferSize, scale as scaleSize} from '../../../src/ol/size.js';
#include "../../../src/ol/size.h"
using namespace ol;
using namespace ol::size;
//
//
//describe('ol.size', function() {
//
//  describe('buffer()', function() {
TEST(ol_size, buffer)
{
    //
    //    it('buffers a size', function() {
    {
        Size size = { 50, 75 };
        auto bufferedSize = bufferSize(size, 20);
        //      expect(bufferedSize).to.eql([90, 115]);
        ASSERT_EQ(2, bufferedSize.size());
        EXPECT_EQ(90, bufferedSize[0]);
        EXPECT_EQ(115, bufferedSize[1]);
    }
    //    });
    //
    //    it('reuses an existing array', function() {
    {
        Size reuse = { 0, 0 };
        Size size = { 50, 50 };
        Size &bufferedSize = bufferSize(size, 20, reuse);
        //      expect(bufferedSize).to.equal(reuse);
        ASSERT_EQ(2, bufferedSize.size());
        EXPECT_EQ(reuse[0], bufferedSize[0]);
        EXPECT_EQ(reuse[1], bufferedSize[1]);
    }
    //    });
    //
    //  });
}
//  describe('hasArea()', function() {
TEST(ol_size, hasArea)
{
    //
    //    it('determines if a size has a positive area', function() {
    //      expect(hasArea([50, 75])).to.equal(true);
    EXPECT_TRUE(hasArea({ 50, 75 }));
    //      expect(hasArea([0, 75])).to.equal(false);
    EXPECT_FALSE(hasArea({ 0, 75 }));
    //      expect(hasArea([50, 0])).to.equal(false);
    EXPECT_FALSE(hasArea({ 50, 0 }));
    //      expect(hasArea([0, 0])).to.equal(false);
    EXPECT_FALSE(hasArea({ 0, 0 }));
    //      expect(hasArea([-1, 75])).to.equal(false);
    EXPECT_FALSE(hasArea({ -1, 75 }));
    //      expect(hasArea([50, -1])).to.equal(false);
    EXPECT_FALSE(hasArea({ 50, -1 }));
    //      expect(hasArea([-1, -1])).to.equal(false);
    EXPECT_FALSE(hasArea({ -1, -1 }));
    //    });
    //
    //  });
}
//  describe('scale()', function() {
TEST(ol_size, scale)
{
    //
    //    it('scales a size and rounds the result', function() {
    {
        Size size = { 50, 75 };
        Size scaledSize = scaleSize(size, 1.75);
        //      expect(scaledSize).to.eql([88, 131]);
        ASSERT_EQ(2, scaledSize.size());
        EXPECT_EQ(88, scaledSize[0]);
        EXPECT_EQ(131, scaledSize[1]);
    }
    //    });
    //
    //    it('reuses an existing array', function() {
    {
        Size reuse = { 0, 0 };
        Size size = { 50, 50 };
        Size &scaledSize = scaleSize(size, 1.75, reuse);
        //      expect(scaledSize).to.equal(reuse);
        EXPECT_EQ(reuse, scaledSize);
    }
    //    });
    //
    //  });
}
//  describe('toSize()', function() {
TEST(ol_size, toSize)
{
    //
    //    it('creates a size array from a number', function() {
    {
        auto size = toSize(512);
        //      expect(size).to.eql([512, 512]);
        ASSERT_EQ(2, size.size());
        EXPECT_EQ(512, size[0]);
        EXPECT_EQ(512, size[1]);
    }
    //    });
    //
    //    it('reuses an existing array', function() {
    {
        Size sizeArray = { 0, 0 };
        Size size = toSize(512, sizeArray);
        //      expect(size).to.equal(sizeArray);
        EXPECT_EQ(sizeArray, size);
    }
    //    });
    //
    //    it('returns a size array unaltered', function() {
    //      const sizeArray = [512, 256];
    //      let size = toSize(sizeArray);
    //      expect(size).to.equal(sizeArray);
    //      size = toSize(sizeArray, [0, 0]);
    //      expect(size).to.equal(sizeArray);
    //    });
}
//  });
//
//});
