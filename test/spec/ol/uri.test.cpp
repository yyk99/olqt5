//
// yyk 2018
//

#include <gtest/gtest.h>

//import {appendParams} from '../../../src/ol/uri.js';

#include "../../../src/ol/uri.h"

using namespace ol;

//
//
//describe('ol.uri.appendParams()', function() {
TEST(ol_uri, appendParams)
{
    //
    //  it('should append empty STYLES with =', function() {
    {
        //    const url = appendParams('http://example.com/foo', {
        //      SERVICE: 'WMS',
        //      STYLES: ''
        //    });

        std::vector<std::tuple<std::string, std::string>> params = {
            std::make_tuple("SERVICE", "WMS"),
            std::make_tuple("STYLES", "")
        };

        std::string url = appendParams("http://example.com/foo", params);

        //    expect(url).to.equal('http://example.com/foo?SERVICE=WMS&STYLES=');
        ASSERT_STREQ("http://example.com/foo?SERVICE=WMS&STYLES=", url.c_str());
        //  });
    }
    //
    //  it('should URL encode values but not names', function() {
    {
        //    const url = appendParams('http://example.com/foo', {
        //      'k ': 'v '
        //    });
        //    expect(url).to.equal('http://example.com/foo?k =v%20');
        //  });
    }
    //
    //  it('should append to simple base URL', function() {
    {
        //    const url = appendParams('http://example.com/foo', {
        //      k: 'v'
        //    });
        //    expect(url).to.equal('http://example.com/foo?k=v');
        //  });
    }
    //
    //  it('should append to base URL with ?', function() {
    {
        //    const url = appendParams('http://example.com/foo?', {
        //      k: 'v'
        //    });
        //    expect(url).to.equal('http://example.com/foo?k=v');
        //  });
    }
    //
    //  it('should append to base URL with single existing param', function() {
    //    const url = appendParams('http://example.com/foo?bar=bam', {
    //      k: 'v'
    //    });
    //    expect(url).to.equal('http://example.com/foo?bar=bam&k=v');
    //  });
    //
    //  it('should append to base URL with single existing param and extraneous &', function() {
    //    const url = appendParams('http://example.com/foo?bar=bam&', {
    //      k: 'v'
    //    });
    //    expect(url).to.equal('http://example.com/foo?bar=bam&k=v');
    //  });
    //
    //  it('should append to base URL with two existing params', function() {
    //    const url = appendParams('http://example.com/foo?bar=bam&baz=bat', {
    //      k: 'v'
    //    });
    //    expect(url).to.equal('http://example.com/foo?bar=bam&baz=bat&k=v');
    //  });
    //
    //  it('should append to base URL with three existing params last one empty', function() {
    //    const url = appendParams('http://example.com/foo?bar=bam&baz=bat&bop=', {
    //      k: 'v'
    //    });
    //    expect(url).to.equal('http://example.com/foo?bar=bam&baz=bat&bop=&k=v');
    //  });
    //
    //  it('should not append null or undefined parameters to the url', function() {
    //    const url = appendParams('http://example.com/foo', {
    //      a: '1',
    //      b: null,
    //      c: undefined
    //    });
    //    expect(url).to.equal('http://example.com/foo?a=1');
    //  });
    //
    //});
}
