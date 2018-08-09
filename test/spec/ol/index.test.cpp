#include <gtest/gtest.h>

//import {getUid} from '../../../src/ol/index.js';
#include "../../../src/ol/index.h"

TEST(ol_index, getUid)
{
    //describe('getUid()', function() {
    //  it('is constant once generated', function() {
    {
        //    const a = {};
        ol::util::Uid a;
        EXPECT_EQ(getUid(a), getUid(a));
    }
    //  });
    //
    //  it('generates a strictly increasing sequence', function() {
    {
        //    const a = {};
        ol::util::Uid a;
        //    const b = {};
        ol::util::Uid b;
        //    const c = {};
        ol::util::Uid c;
        getUid(a);
        getUid(c);
        getUid(b);
        //
        //    //uid order should be a < c < b
        EXPECT_TRUE(getUid(a) < getUid(c));
        EXPECT_TRUE(getUid(c) < getUid(b));
        EXPECT_TRUE(getUid(a) < getUid(b));
    }
}