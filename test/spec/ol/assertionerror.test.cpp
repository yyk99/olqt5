//
// yyk 2018
//

#include <gtest/gtest.h>

//import {VERSION} from '../../../src/ol/index.js';

#include "../../../src/ol/index.h"

//import AssertionError from '../../../src/ol/AssertionError.js';

#include "../../../src/ol/AssertionError.h"
//

TEST(ol_AssertionError, t1)
{
    //describe('ol.AssertionError', function() {
    //  it('generates an error', function() {
    {
        EXPECT_THROW(throw ol::AssertionError(42), std::exception);
    }
    //  });
    //
    //  it('generates a message with a versioned url', function() {
    {
        auto error = ol::AssertionError(42);
        std::string path = ol::util::VERSION /*? VERSION.split('-')[0] : 'latest'*/;
        EXPECT_EQ("Assertion failed. See https://openlayers.org/en/" + path + "/doc/errors/#42 for details.", error.what());

    }
    //  });
    //
    //  it('has an error code', function() {
    {
        //    const error = new AssertionError(42);
        auto error = ol::AssertionError(42);
        //    expect(error.code).to.be(42);
        EXPECT_EQ(42, error.code());
    }
    //  });
    //
    //  it('has a name', function() {
    {
        //    const error = new AssertionError(42);
        auto error = ol::AssertionError(42);
        //    expect(error.name).to.be('AssertionError');
        EXPECT_EQ("AssertionError", error.name());
    }
    //  });
    //});
}