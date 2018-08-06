#include <gtest/gtest.h>

//import Projection from '../../../../src/ol/proj/Projection.js';
#include "../../../../src/ol/proj/Projection.h"
//import * as transforms from '../../../../src/ol/proj/transforms.js';
#include "../../../../src/ol/proj/transforms.h"
//

class ol_proj_transforms : public ::testing::Test {
public:
    ol_proj_transforms()
    {}

    virtual void SetUp() override
    {
        ol::proj::clearAllProjections();
        ol::proj::addCommon();
    }

    class EquivTransform : public ol::proj::TransformFunctionObj {
    public:
        virtual std::vector<ol::number_t> & operator ()(std::vector<ol::number_t> const &v1, std::vector<ol::number_t> &v2, size_t)
        {
            v2 = v1;
            return v2;
        }
    };
};

//
//describe('transforms.remove()', function() {
TEST_F(ol_proj_transforms, remove)
{
    //
    //  const extent = [180, -90, 180, 90];
    std::vector<ol::number_t> extent = { 180, -90, 180, 90 };
    //  const units = 'degrees';
    std::string units = "degrees";
    //
    //  it('removes functions cached by transforms.add()', function() {
    {
        //    const foo = new Projection({
        //      code: 'foo',
        //      units: units,
        //      extent: extent
        //    });

        ol::proj::Projection::Options foo_opt; {
            foo_opt.code = "foo";
            foo_opt.units = units;
            foo_opt.extent = extent;
        }

        auto foo = ol::proj::ProjectionP(new ol::proj::Projection(foo_opt));

        //    const bar = new Projection({
        //      code: 'bar',
        //      units: units,
        //      extent: extent
        //    });
        ol::proj::Projection::Options bar_opt; {
            bar_opt.code = "bar";
            bar_opt.units = units;
            bar_opt.extent = extent;
        }

        auto bar = ol::proj::ProjectionP(new ol::proj::Projection(bar_opt));

        //    const transform = function(input, output, dimension) {
        //      return input;
        //    };

        EquivTransform transform;

        //    transforms.add(foo, bar, transform);
        ol::proj::transforms::add(foo, bar, &transform);

        //    expect(transforms.get('foo', 'bar')).to.be(transform);
        EXPECT_EQ(&transform, ol::proj::transforms::get("foo", "bar"));
        //
        //    const removed = transforms.remove(foo, bar);
        auto removed = ol::proj::transforms::remove(foo, bar);
        //    expect(removed).to.be(transform);
        EXPECT_EQ(&transform, removed);
        //    expect(transforms.get('foo', 'bar')).to.be(undefined);
        EXPECT_TRUE(0 == ol::proj::transforms::get("foo", "bar"));
    }
    //  });
}
//});
