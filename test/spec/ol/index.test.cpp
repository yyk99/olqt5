#include <gtest/gtest.h>

//import {getUid} from '../../../src/ol/index.js';
#include "../../../src/ol/index.h"

TEST(ol_index, getUid)
{
    return; // TODO: Implement

    //describe('getUid()', function() {
    //  it('is constant once generated', function() {
    {
        //    const a = {};
        void *a = 0;
        EXPECT_NO_THROW(ol::util::getUid(a));
        //    expect(getUid(a)).to.be(getUid(a));
    }
    //  });
    //
    //  it('generates a strictly increasing sequence', function() {
    {
        //    const a = {};
        //    const b = {};
        //    const c = {};
        //    getUid(a);
        //    getUid(c);
        //    getUid(b);
        //
        //    //uid order should be a < c < b
        //    expect(getUid(a)).to.be.lessThan(getUid(c));
        //    expect(getUid(c)).to.be.lessThan(getUid(b));
        //    expect(getUid(a)).to.be.lessThan(getUid(b));
    }
    //  });
    //});
}