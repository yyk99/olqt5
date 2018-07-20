#include <gtest/gtest.h>

//import {getPointResolution, transform, get as getProjection, clearAllProjections, addCommon} from '../../../../src/ol/proj.js';
#include "../../../../src/ol/proj.h"
//import {fromEPSG4326, HALF_SIZE} from '../../../../src/ol/proj/epsg3857.js';
#include "../../../../src/ol/proj/epsg3857.h"

class ol_proj_epsg3857 : public ::testing::Test {
public:
    ol_proj_epsg3857()
    {}

    virtual void SetUp() override
    {
        ol::proj::clearAllProjections();
        ol::proj::addCommon();
    }
};

//
//describe('ol/proj/epsg3857', function() {
//
//  afterEach(function() {
//    clearAllProjections();
//    addCommon();
//  });

//  describe('fromEPSG4326()', function() {
TEST_F(ol_proj_epsg3857, fromEPSG4326)
{
    using namespace ol::proj::epsg3857;
    //    it('transforms from geographic to Web Mercator', function() 
    {
        double tolerance = 1e-5;
        {
            // g: [0, 0],
            // m: [0, 0]
            ol::coordinate::Coordinate g = { 0, 0 };
            ol::coordinate::Coordinate m = { 0, 0 };
            auto transformed = fromEPSG4326(g);
            EXPECT_NEAR(m[0], transformed[0], tolerance);
        }
        {
            // g: [-180, -90],
            // m: [-HALF_SIZE, -HALF_SIZE]
            ol::coordinate::Coordinate g = { -180, -90 };
            ol::coordinate::Coordinate m = { -HALF_SIZE, -HALF_SIZE };
            auto transformed = fromEPSG4326(g);
            EXPECT_NEAR(m[0], transformed[0], tolerance);
        }
        {
            // g: [180, 90],
            // m: [HALF_SIZE, HALF_SIZE]
            ol::coordinate::Coordinate g = { 180, 90 };
            ol::coordinate::Coordinate m = { HALF_SIZE, HALF_SIZE };
            auto transformed = fromEPSG4326(g);
            EXPECT_NEAR(m[0], transformed[0], tolerance);

        }
        {
            // g: [-111.0429, 45.6770],
            // m: [-12361239.084208, 5728738.469095]
            ol::coordinate::Coordinate g = { -111.0429, 45.6770 };
            ol::coordinate::Coordinate m = { -12361239.084208, 5728738.469095 };
            auto transformed = fromEPSG4326(g);
            EXPECT_NEAR(m[0], transformed[0], tolerance);
        }
    }
}

//  describe('getPointResolution', function() {
TEST_F(ol_proj_epsg3857, getPointResolution)
{
    using namespace ol::proj;
    //
    //    it('returns the correct point scale at the equator', function() {
    {
        //      // @see http://msdn.microsoft.com/en-us/library/aa940990.aspx
        //      const epsg3857 = getProjection('EPSG:3857');
        auto epsg3857 = getProjection("EPSG:3857");
        ASSERT_TRUE(epsg3857 != 0);
        //      const resolution = 19.11;
        ol::number_t resolution = 19.11;
        //      const point = [0, 0];
        ol::coordinate::Coordinate point = { 0, 0 };
        //      expect(getPointResolution(epsg3857, resolution, point)).
        //        to.roughlyEqual(19.11, 1e-1);
        EXPECT_NEAR(19.11, getPointResolution(epsg3857, resolution, point), 1e-1);
    }
    //    });
    //
    //    it('returns the correct point scale at the latitude of Toronto',
    //      function() {
    {
        //        // @see http://msdn.microsoft.com/en-us/library/aa940990.aspx
        ProjectionP epsg3857 = getProjection("EPSG:3857");
        ASSERT_TRUE(epsg3857 != 0);
        ProjectionP epsg4326 = getProjection("EPSG:4326");
        ASSERT_TRUE(epsg4326 != 0);
        ol::number_t resolution = 19.11;
        ol::coordinate::Coordinate point = transform({ 0, 43.65 }, epsg4326, epsg3857);
        //        expect(getPointResolution(epsg3857, resolution, point)).
        //          to.roughlyEqual(19.11 * Math.cos(Math.PI * 43.65 / 180), 1e-9);
    }
    //      });
    //
    //    it('returns the correct point scale at various latitudes', function() {
    //      // @see http://msdn.microsoft.com/en-us/library/aa940990.aspx
    //      const epsg3857 = getProjection('EPSG:3857');
    //      const epsg4326 = getProjection('EPSG:4326');
    //      const resolution = 19.11;
    //      let latitude;
    //      for (latitude = 0; latitude <= 85; ++latitude) {
    //        const point = transform([0, latitude], epsg4326, epsg3857);
    //        expect(getPointResolution(epsg3857, resolution, point)).
    //          to.roughlyEqual(19.11 * Math.cos(Math.PI * latitude / 180), 1e-9);
    //      }
    //    });
    //
}
