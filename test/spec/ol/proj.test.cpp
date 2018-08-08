#include <gtest/gtest.h>

//import {
//  addCommon,
//  clearAllProjections,
//  equivalent,
//  get as getProjection,
//  transform,
//  transformExtent,
//  fromLonLat,
//  toLonLat,
//  getTransform,
//  getPointResolution,
//  getTransformFromProjections
//} from '../../../src/ol/proj.js';
#include "../../../src/ol/proj.h"
//import {register} from '../../../src/ol/proj/proj4.js';
#include "../../../src/ol/proj/proj4.h"
//import {HALF_SIZE} from '../../../src/ol/proj/epsg3857.js';
#include "../../../src/ol/proj/epsg3857.h"
//import {METERS_PER_UNIT} from '../../../src/ol/proj/epsg4326.js';
#include "../../../src/ol/proj/epsg4326.h"
//import Projection from '../../../src/ol/proj/Projection.js';
#include "../../../src/ol/proj/Projection.h"
//
//

class ol_proj : public ::testing::Test {
public:
    ol_proj()
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

//describe('ol.proj', function() {
//
//  afterEach(function() {
//    clearAllProjections();
//    addCommon();
//  });

using namespace ol;

//  describe('toLonLat()', function() {
TEST_F(ol_proj, toLonLat)
{
    //    const cases = [
    {
        //      from: [0, 0],
        std::vector<number_t> from({ 0, 0 });
        //      to: [0, 0]
        auto lonLat = ol::proj::toLonLat(from);
        EXPECT_EQ(0, lonLat[0]);
        EXPECT_EQ(0, lonLat[1]);
    }
    //    }, 
    {
        std::vector<number_t> from({ -12356463.478053365, 5700582.732404122 });
        //      to: [-111, 45.5]
        auto lonLat = ol::proj::toLonLat(from);
        EXPECT_NEAR(-111, lonLat[0], 1e-9);
        EXPECT_NEAR(45.5, lonLat[1], 1e-9);
    }
    {
        std::vector<number_t> from({ 2 * ol::proj::epsg3857::HALF_SIZE - 12356463.478053365, 5700582.732404122 });
        //      to: [-111, 45.5]
        auto lonLat = ol::proj::toLonLat(from);
        EXPECT_NEAR(-111, lonLat[0], 1e-9);
        EXPECT_NEAR(45.5, lonLat[1], 1e-9);
    }
    {
        std::vector<number_t> from({ -4 * ol::proj::epsg3857::HALF_SIZE - 12356463.478053365, 5700582.732404122 });
        //      to: [-111, 45.5]
        auto lonLat = ol::proj::toLonLat(from);
        EXPECT_NEAR(-111, lonLat[0], 1e-9);
        EXPECT_NEAR(45.5, lonLat[1], 1e-9);
    }

    //    cases.forEach(function(c) {
    //      it('works for ' + c.from.join(', '), function() {
    //        const lonLat = toLonLat(c.from);
    //        expect(lonLat[0]).to.roughlyEqual(c.to[0], 1e-9);
    //        expect(lonLat[1]).to.roughlyEqual(c.to[1], 1e-9);
    //      });
    //    });
}
//  });

//  describe('projection equivalence', function() {
TEST_F(ol_proj, projection_equivalence)
{
    using namespace ol::proj;

    //
    //    function _testAllEquivalent(codes) {
    //      const projections = codes.map(getProjection);
    //      projections.forEach(function(source) {
    //        projections.forEach(function(destination) {
    //          expect(equivalent(source, destination)).to.be.ok();
    //        });
    //      });
    //    }

    ASSERT_TRUE(ol::proj::getProjection("EPSG:3857") != 0);
    ASSERT_TRUE(ol::proj::getProjection("EPSG:102100") != 0);
    ASSERT_TRUE(ol::proj::getProjection("EPSG:102113") != 0);
    ASSERT_TRUE(ol::proj::getProjection("EPSG:900913") != 0);

    //        'CRS:84',
    //        'urn:ogc:def:crs:EPSG:6.6:4326',
    //        'EPSG:4326'

    ASSERT_TRUE(getProjection("CRS:84") != 0);
    ASSERT_TRUE(getProjection("urn:ogc:def:crs:EPSG:6.6:4326") != 0);
    ASSERT_TRUE(getProjection("EPSG:4326") != 0);

    //
    //    it('gives that 3857, 102100, 102113, 900913 are equivalent ', function() {
    {
        //      _testAllEquivalent([
        //        'EPSG:3857',
        //        'EPSG:102100',
        //        'EPSG:102113',
        //        'EPSG:900913'
        //      ]);
        //    });
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:3857"), ol::proj::getProjection("EPSG:3857")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:3857"), ol::proj::getProjection("EPSG:102100")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:3857"), ol::proj::getProjection("EPSG:102113")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:3857"), ol::proj::getProjection("EPSG:900913")));

        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:102100"), ol::proj::getProjection("EPSG:3857")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:102100"), ol::proj::getProjection("EPSG:102100")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:102100"), ol::proj::getProjection("EPSG:102113")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:102100"), ol::proj::getProjection("EPSG:900913")));

        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:102113"), ol::proj::getProjection("EPSG:3857")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:102113"), ol::proj::getProjection("EPSG:102100")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:102113"), ol::proj::getProjection("EPSG:102113")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:102113"), ol::proj::getProjection("EPSG:900913")));

        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:900913"), ol::proj::getProjection("EPSG:3857")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:900913"), ol::proj::getProjection("EPSG:102100")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:900913"), ol::proj::getProjection("EPSG:102113")));
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:900913"), ol::proj::getProjection("EPSG:900913")));
    }
    //    it('gives that custom 3413 is equivalent to self', function() {
    {
        //      const code = 'EPSG:3413';
        Projection::Options opt; opt.code = "EPSG:3413";
        //
        //      const source = new Projection({
        //        code: code
        //      });
        auto source = ProjectionP(new Projection(opt));
        //
        //      const destination = new Projection({
        //        code: code
        //      });
        auto destination = ProjectionP(new Projection(opt));
        //
        //      expect(equivalent(source, destination)).to.be.ok();
        EXPECT_TRUE(equivalent(source, destination));
    }
    //    });
    //
    //    it('gives that default 3857 is equivalent to self', function() {
    {
        //      _testAllEquivalent([
        //        'EPSG:3857',
        //        'EPSG:3857'
        //      ]);
        EXPECT_TRUE(ol::proj::equivalent(ol::proj::getProjection("EPSG:3857"), ol::proj::getProjection("EPSG:3857")));
    }
    //    });
    //
    //    it('gives that CRS:84, urn:ogc:def:crs:EPSG:6.6:4326, EPSG:4326 are ' +
    //        'equivalent',
    //    function() {
    {
        //      _testAllEquivalent([
        //        'CRS:84',
        //        'urn:ogc:def:crs:EPSG:6.6:4326',
        //        'EPSG:4326'
        //      ]);
        EXPECT_TRUE(equivalent(getProjection("CRS:84"), getProjection("CRS:84")));
        EXPECT_TRUE(equivalent(getProjection("CRS:84"), getProjection("urn:ogc:def:crs:EPSG:6.6:4326")));
        EXPECT_TRUE(equivalent(getProjection("CRS:84"), getProjection("EPSG:4326")));
    }
    //    });
    //
    //    it('requires code and units to be equal for projection equivalence,
    //      function() {
    {
        //        const proj1 = new Projection({
        //          code: 'EPSG:3857',
        //          units: 'm'
        //        });

        Projection::Options o1; 
        o1.code = "EPSG:3857";
        o1.units = "m";
        auto proj1 = ProjectionP(new Projection(o1));

        //        const proj2 = new Projection({
        //          code: 'EPSG:3857',
        //          units: 'tile-pixels'
        //        });
        o1.units = "tile-pixels";
        auto proj2 = ProjectionP(new Projection(o1));
        //        expect(equivalent(proj1, proj2)).to.not.be.ok();
        EXPECT_FALSE(equivalent(proj1, proj2));
    }
    //      });
    //
}

//  describe('identify transform', function() {
TEST_F(ol_proj, identify_transform)
{
    using namespace ol::proj;
    //
    //    it('returns a new object, with same coord values', function() {
    {
        auto epsg4326 = getProjection("EPSG:4326");
        ASSERT_TRUE(0 != epsg4326);
        ol::number_t uniqueObject = 0;
        ol::coordinate::Coordinate sourcePoint = { uniqueObject, uniqueObject };
        ol::coordinate::Coordinate destinationPoint = transform(sourcePoint, epsg4326, epsg4326);
        //      expect(sourcePoint === destinationPoint).to.not.be();
        EXPECT_TRUE(&sourcePoint != &destinationPoint); // :-)
        //      expect(destinationPoint[0] === sourcePoint[0]).to.be.ok();
        EXPECT_TRUE(destinationPoint[0] == sourcePoint[0]);
        //      expect(destinationPoint[1] === sourcePoint[1]).to.be.ok();
        EXPECT_TRUE(destinationPoint[1] == sourcePoint[1]);
        //    });
    }
    //  });
    //
    //  describe('transform 0,0 from 4326 to 3857', function() {
    {
        //
        //    it('returns expected value', function() {
        //      const point = transform([0, 0], 'EPSG:4326', 'EPSG:3857');
        auto point = transform({ 0, 0 }, "EPSG:4326", "EPSG:3857");
        //      expect(point).not.to.be(undefined);
        //      expect(point).not.to.be(null);
        ASSERT_EQ(2, point.size());
        //      expect(point[1]).to.roughlyEqual(0, 1e-9);
        EXPECT_NEAR(0, point[1], 1e-9);
        //    });
    }
    //  });
    //
    //  describe('transform 0,0 from 3857 to 4326', function() {
    {
        //
        //    it('returns expected value', function() {
        //      const point = transform([0, 0], 'EPSG:3857', 'EPSG:4326');
        auto point = transform({ 0, 0 }, "EPSG:3857", "EPSG:4326");
        //      expect(point).not.to.be(undefined);
        //      expect(point).not.to.be(null);
        ASSERT_EQ(2, point.size());
        //      expect(point[0]).to.eql(0);
        EXPECT_EQ(0, point[0]);
        //      expect(point[1]).to.eql(0);
        EXPECT_EQ(0, point[1]);
        //    });
    }
    //  });
    //
    //  describe('transform from 4326 to 3857 (Alastaira)', function() {
    {
        // http://alastaira.wordpress.com/2011/01/23/the-google-maps-bing-maps-spherical-mercator-projection/
        //
        //    it('returns expected value using ol.proj.transform', function() {
        {
            //      const point = transform(
            //        [-5.625, 52.4827802220782], 'EPSG:4326', 'EPSG:900913');
            auto point = transform({ -5.625, 52.4827802220782 }, "EPSG:4326", "EPSG:900913");
            //      expect(point).not.to.be(undefined);
            //      expect(point).not.to.be(null);
            ASSERT_EQ(2, point.size());
            //      expect(point[0]).to.roughlyEqual(-626172.13571216376, 1e-9);
            EXPECT_NEAR(-626172.13571216376, point[0], 1e-9);
            //      expect(point[1]).to.roughlyEqual(6887893.4928337997, 1e-8);
            EXPECT_NEAR(6887893.4928337997, point[1], 1e-8);
        }
        //    });
        //
        //    it('returns expected value using ol.proj.fromLonLat', function() {
        {
            auto point = fromLonLat({ -5.625, 52.4827802220782 });
            //      expect(point).not.to.be(undefined);
            //      expect(point).not.to.be(null);
            //      expect(point[0]).to.roughlyEqual(-626172.13571216376, 1e-9);
            //      expect(point[1]).to.roughlyEqual(6887893.4928337997, 1e-8);
            ASSERT_EQ(2, point.size());
            EXPECT_NEAR(-626172.13571216376, point[0], 1e-9);
            EXPECT_NEAR(6887893.4928337997, point[1], 1e-8);
        }
        //    });
    }
    //  });
    //
    //  describe('transform from 3857 to 4326 (Alastaira)', function() {
    // http://alastaira.wordpress.com/2011/01/23/the-google-maps-bing-maps-spherical-mercator-projection/
    //
    //    it('returns expected value using ol.proj.transform', function() {
    {
        //      const point = transform([-626172.13571216376, 6887893.4928337997],
        //        'EPSG:900913', 'EPSG:4326');
        //      expect(point).not.to.be(undefined);
        //      expect(point).not.to.be(null);
        //      expect(point[0]).to.roughlyEqual(-5.625, 1e-9);
        //      expect(point[1]).to.roughlyEqual(52.4827802220782, 1e-9);
        auto point = transform({ -626172.13571216376, 6887893.4928337997 }, "EPSG:900913", "EPSG:4326");
        ASSERT_EQ(2, point.size());
        EXPECT_NEAR(-5.625, point[0], 1e-9);
        EXPECT_NEAR(52.4827802220782, point[1], 1e-9);
    }
    //    });
    //
    //    it('returns expected value using ol.proj.toLonLat', function() {
    {
        auto point = toLonLat({ -626172.13571216376, 6887893.4928337997 });
        ASSERT_EQ(2, point.size());
        EXPECT_NEAR(-5.625, point[0], 1e-9);
        EXPECT_NEAR(52.4827802220782, point[1], 1e-9);
    }
    //  });
}

//  describe('canWrapX()', function() {
TEST_F(ol_proj, canWrapX)
{
    using namespace ol::proj;
    //
    //    it('requires an extent for allowing wrapX', function() {
    {
        //      let proj = new Projection({
        //        code: 'foo',
        //        global: true
        //      });
        auto proj = ProjectionP(new Projection(Projection::Options("foo", true)));
        //      expect(proj.canWrapX()).to.be(false);
        EXPECT_FALSE(proj->canWrapX());
        //      proj.setExtent([1, 2, 3, 4]);
        proj->setExtent({ 1,2,3,4 });
        //      expect(proj.canWrapX()).to.be(true);
        EXPECT_TRUE(proj->canWrapX());
        //      proj = new Projection({
        //        code: 'foo',
        //        global: true,
        //        extent: [1, 2, 3, 4]
        //      });
        proj = ProjectionP(new Projection(Projection::Options("foo", true, { 1, 2, 3, 4 })));
        //      expect(proj.canWrapX()).to.be(true);
        EXPECT_TRUE(proj->canWrapX());
        //      proj.setExtent(null);
        proj->setExtent(ol::extent::Extent());
        //      expect(proj.canWrapX()).to.be(false);
        EXPECT_FALSE(proj->canWrapX());
    }
    //    });
    //
    //    it('requires global to be true for allowing wrapX', function() {
    {
        //      let proj = new Projection({
        //        code: 'foo',
        //        extent: [1, 2, 3, 4]
        //      });
        auto proj = ProjectionP(new Projection(Projection::Options("foo", false, { 1,2,3,4 })));
        //      expect(proj.canWrapX()).to.be(false);
        EXPECT_FALSE(proj->canWrapX());
        //      proj.setGlobal(true);
        proj->setGlobal(true);
        //      expect(proj.canWrapX()).to.be(true);
        EXPECT_TRUE(proj->canWrapX());
        //      proj = new Projection({
        //        code: 'foo',
        //        global: true,
        //        extent: [1, 2, 3, 4]
        //      });
        proj = ProjectionP(new Projection(Projection::Options("foo", true, { 1,2,3,4 })));
        //      expect(proj.canWrapX()).to.be(true);
        EXPECT_TRUE(proj->canWrapX());
        //      proj.setGlobal(false);
        proj->setGlobal(false);
        //      expect(proj.canWrapX()).to.be(false);
        EXPECT_FALSE(proj->canWrapX());
    }
    //    });
    //
    //  });
}

//  describe('transformExtent()', function() {
TEST_F(ol_proj, transformExtent)
{
    using namespace ol::proj;
    //
    //    it('transforms an extent given projection identifiers', function() {
    {
        ol::extent::Extent sourceExtent = { -15, -30, 45, 60 };
        auto destinationExtent = transformExtent(
                sourceExtent, "EPSG:4326", "EPSG:3857");
        //      expect(destinationExtent).not.to.be(undefined);
        //      expect(destinationExtent).not.to.be(null);
        ASSERT_EQ(4, destinationExtent.size());
        //      expect(destinationExtent[0])
        //        .to.roughlyEqual(-1669792.3618991037, 1e-9);
        EXPECT_NEAR(-1669792.3618991037, destinationExtent[0], 1e-9);
        //      expect(destinationExtent[2]).to.roughlyEqual(5009377.085697311, 1e-9);
        EXPECT_NEAR(5009377.085697311, destinationExtent[2], 1e-9);
        //      expect(destinationExtent[1]).to.roughlyEqual(-3503549.843504376, 1e-8);
        EXPECT_NEAR(-3503549.843504376, destinationExtent[1], 1e-8);
        //      expect(destinationExtent[3]).to.roughlyEqual(8399737.889818361, 1e-8);
        EXPECT_NEAR(8399737.889818361, destinationExtent[3], 1e-8);
    }
    //    });
    //
    //  });
}

//  describe('getPointResolution()', function() {
TEST_F(ol_proj, getPointResolution)
{
    using namespace ol::proj;
    //    it('returns the correct point resolution for EPSG:4326', function() {
    {
        auto pointResolution = getPointResolution("EPSG:4326", 1, { 0, 0 });
        EXPECT_EQ(1,  pointResolution);
        pointResolution = getPointResolution("EPSG:4326", 1, { 0, 52 });
        EXPECT_EQ(1, pointResolution);
    }
    //    });
    //    it('returns the correct point resolution for EPSG:4326 with custom units', function() {
    {
        //      let pointResolution = getPointResolution('EPSG:4326', 1, [0, 0], 'm');
        //      expect(pointResolution).to.roughlyEqual(111195.0802335329, 1e-5);
        //      pointResolution = getPointResolution('EPSG:4326', 1, [0, 52], 'm');
        //      expect(pointResolution).to.roughlyEqual(89826.53390979706, 1e-5);
        auto pointResolution = getPointResolution("EPSG:4326", 1, { 0, 0 }, "m");
        EXPECT_NEAR(111195.0802335329, pointResolution, 1e-5);
        pointResolution = getPointResolution("EPSG:4326", 1, { 0, 52 }, "m");
        EXPECT_NEAR(89826.53390979706, pointResolution, 1e-5);
    }
    //    });
    //    it('returns the correct point resolution for EPSG:3857', function() {
    {
        auto pointResolution = getPointResolution("EPSG:3857", 1, { 0, 0 });
        EXPECT_EQ(1, pointResolution);
        pointResolution = getPointResolution("EPSG:3857", 1, fromLonLat({ 0, 52 }));
        EXPECT_NEAR(0.615661, pointResolution, 1e-5);
    }
    //    });
    //    it('returns the correct point resolution for EPSG:3857 with custom units', function() {
    {
        auto pointResolution = getPointResolution("EPSG:3857", 1, { 0, 0 }, "degrees");
        EXPECT_EQ(1, pointResolution);
        pointResolution = getPointResolution("EPSG:4326", 1, fromLonLat({ 0, 52 }), "degrees");
        EXPECT_EQ(1, pointResolution);
    }
    //    });
    //  });
}

class ol_proj4js : public ::testing::Test {
public:
    ol_proj4js()
    {}

    virtual void SetUp() override
    {
        //    afterEach(function() {
        //      delete proj4.defs['EPSG:21781'];
        //      clearAllProjections();
        //      addCommon();
        //    });
        ol::proj::proj4::proj4.defs.erase("EPSG:21781");
        ol::proj::clearAllProjections();
        ol::proj::addCommon();
    }
};

TEST_F(ol_proj4js, integration_1)
{
    using namespace ol::proj;

    //    it('creates ol.proj.Projection instance from EPSG:21781', function() {
    {
        //      proj4.defs('EPSG:21781',
        //        '+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 ' +
        //          '+k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel ' +
        //          '+towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs');
        ol::proj::proj4::proj4.defs("EPSG:21781",
            "+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 " \
            "+k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel " \
            "+towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs");

        proj4::Register(ol::proj::proj4::proj4);
        //      const proj = getProjection('EPSG:21781');
        //      expect(proj.getCode()).to.eql('EPSG:21781');
        //      expect(proj.getUnits()).to.eql('m');
        //      expect(proj.getMetersPerUnit()).to.eql(1);
        auto proj = getProjection("EPSG:21781");
        ASSERT_TRUE(proj != 0);
        EXPECT_EQ("EPSG:21781", proj->getCode());
        EXPECT_EQ("m", proj->getUnits());
        EXPECT_EQ(1, proj->getMetersPerUnit());
    }
    //    });
}

TEST_F(ol_proj4js, integration_2)
{
    using namespace ol::proj;

    //    it('creates ol.proj.Projection instance from EPSG:3739', function() {
    {
        //      proj4.defs('EPSG:3739',
        //        '+proj=tmerc +lat_0=40.5 +lon_0=-110.0833333333333 +k=0.9999375 ' +
        //          '+x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 ' +
        //          '+towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs');
        ol::proj::proj4::proj4.defs("EPSG:3739",
            "+proj=tmerc +lat_0=40.5 +lon_0=-110.0833333333333 +k=0.9999375 " \
            "+x_0=800000.0000101599 +y_0=99999.99998983997 +ellps=GRS80 " \
            "+towgs84=0,0,0,0,0,0,0 +units=us-ft +no_defs");
        proj4::Register(ol::proj::proj4::proj4);
        //      const proj = getProjection('EPSG:3739');
        //      expect(proj.getCode()).to.eql('EPSG:3739');
        //      expect(proj.getUnits()).to.eql('us-ft');
        //      expect(proj.getMetersPerUnit()).to.eql(1200 / 3937);
        //
        auto proj = getProjection("EPSG:3739");
        ASSERT_TRUE(proj != 0);
        EXPECT_EQ("EPSG:3739", proj->getCode());
        EXPECT_EQ("us-ft", proj->getUnits());
        EXPECT_EQ(1200.0 / 3937.0, proj->getMetersPerUnit());
        ol::proj::proj4::proj4.defs.erase("EPSG:3739");
    }
}

TEST_F(ol_proj4js, integration_3)
{
    using namespace ol::proj;
    // it('allows Proj4js projections to be used transparently', function() {
    {
        // register(proj4);
        proj4::Register(ol::proj::proj4::proj4);
        auto point = transform(
            { -626172.13571216376, 6887893.4928337997 }, "GOOGLE", "WGS84");

        // expect(point[0]).to.roughlyEqual(-5.625, 1e-9);
        EXPECT_NEAR(-5.625, point[0], 1e-9);
        // expect(point[1]).to.roughlyEqual(52.4827802220782, 1e-9);
        EXPECT_NEAR(52.4827802220782, point[1], 1e-9);
    }
}

TEST_F(ol_proj4js, integration_4)
{
    //
    //    it('allows new Proj4js projections to be defined', function() {
    //      proj4.defs('EPSG:21781',
    //        '+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 ' +
    //          '+k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel ' +
    //          '+towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs');
    //      register(proj4);
    //      const point = transform([7.439583333333333, 46.95240555555556],
    //        'EPSG:4326', 'EPSG:21781');
    //      expect(point[0]).to.roughlyEqual(600072.300, 1);
    //      expect(point[1]).to.roughlyEqual(200146.976, 1);
    //    });
}

TEST_F(ol_proj4js, integration_5)
{
    //
    //    it('works with ol.proj.fromLonLat and ol.proj.toLonLat', function() {
    //      proj4.defs('EPSG:21781',
    //        '+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 ' +
    //          '+k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel ' +
    //          '+towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs');
    //      register(proj4);
    //      const lonLat = [7.439583333333333, 46.95240555555556];
    //      let point = fromLonLat(lonLat, 'EPSG:21781');
    //      expect(point[0]).to.roughlyEqual(600072.300, 1);
    //      expect(point[1]).to.roughlyEqual(200146.976, 1);
    //      point = toLonLat(point, 'EPSG:21781');
    //      expect(point[0]).to.roughlyEqual(lonLat[0], 1);
    //      expect(point[1]).to.roughlyEqual(lonLat[1], 1);
    //    });
}
TEST_F(ol_proj4js, integration_6)
{
    //
    //    it('caches the new Proj4js projections given their srsCode', function() {
    //      proj4.defs('EPSG:21781',
    //        '+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 ' +
    //          '+k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel ' +
    //          '+towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs');
    //      const code = 'urn:ogc:def:crs:EPSG:21781';
    //      const srsCode = 'EPSG:21781';
    //      proj4.defs(code, proj4.defs(srsCode));
    //      register(proj4);
    //      const proj = getProjection(code);
    //      const proj2 = getProjection(srsCode);
    //      expect(equivalent(proj2, proj)).to.be(true);
    //      delete proj4.defs[code];
    //    });
}
TEST_F(ol_proj4js, integration_7)
{
    //
    //    it('numerically estimates point scale at the equator', function() {
    //      register(proj4);
    //      const googleProjection = getProjection('GOOGLE');
    //      expect(getPointResolution(googleProjection, 1, [0, 0])).
    //        to.roughlyEqual(1, 1e-1);
    //    });
    //
    //    it('numerically estimates point scale at various latitudes', function() {
    //      register(proj4);
    //      const epsg3857Projection = getProjection('EPSG:3857');
    //      const googleProjection = getProjection('GOOGLE');
    //      let point, y;
    //      for (y = -20; y <= 20; ++y) {
    //        point = [0, 1000000 * y];
    //        expect(getPointResolution(googleProjection, 1, point)).to.roughlyEqual(
    //          getPointResolution(epsg3857Projection, 1, point), 1e-1);
    //      }
    //    });
    //
    //    it('numerically estimates point scale at various points', function() {
    //      register(proj4);
    //      const epsg3857Projection = getProjection('EPSG:3857');
    //      const googleProjection = getProjection('GOOGLE');
    //      let point, x, y;
    //      for (x = -20; x <= 20; x += 2) {
    //        for (y = -20; y <= 20; y += 2) {
    //          point = [1000000 * x, 1000000 * y];
    //          expect(getPointResolution(googleProjection, 1, point)).to.roughlyEqual(
    //            getPointResolution(epsg3857Projection, 1, point), 1e-1);
    //        }
    //      }
    //    });
    //
    //    it('does not overwrite existing projections in the registry', function() {
    //      register(proj4);
    //      const epsg4326 = getProjection('EPSG:4326');
    //      new Projection({
    //        code: 'EPSG:4326',
    //        units: 'degrees',
    //        extent: [-45, -45, 45, 45]
    //      });
    //      expect(getProjection('EPSG:4326')).to.equal(epsg4326);
    //    });
    //
    //  });
}

class ol_reg_proj4 : public ::testing::Test {
public:
    ol_reg_proj4()
    {}

    virtual void SetUp() override
    {
        ol::proj::clearAllProjections();
        ol::proj::addCommon();
        ol::proj::proj4::Register(ol::proj::proj4::proj4);
    }
};

//  describe('ol.proj.getTransformFromProjections()', function() {
TEST_F(ol_reg_proj4, getTransformFromProjections)
{
    //
    //    beforeEach(function() {
    //      register(proj4);
    //    });
    //
    //    it('returns a transform function', function() {
    //      const transform = getTransformFromProjections(getProjection('GOOGLE'),
    //        getProjection('EPSG:4326'));
    //      expect(typeof transform).to.be('function');
    //
    //      const output = transform([-12000000, 5000000]);
    //
    //      expect(output[0]).to.roughlyEqual(-107.79783409434258, 1e-9);
    //      expect(output[1]).to.roughlyEqual(40.91627447067577, 1e-9);
    //    });
    //
    //    it('works for longer arrays', function() {
    //      const transform = getTransformFromProjections(getProjection('GOOGLE'),
    //        getProjection('EPSG:4326'));
    //      expect(typeof transform).to.be('function');
    //
    //      const output = transform([-12000000, 5000000, -12000000, 5000000]);
    //
    //      expect(output[0]).to.roughlyEqual(-107.79783409434258, 1e-9);
    //      expect(output[1]).to.roughlyEqual(40.91627447067577, 1e-9);
    //      expect(output[2]).to.roughlyEqual(-107.79783409434258, 1e-9);
    //      expect(output[3]).to.roughlyEqual(40.91627447067577, 1e-9);
    //    });
    EXPECT_TRUE(false) << "Not implemented yet";
}
//  });
//
//  describe('ol.proj.getTransform()', function() {
TEST_F(ol_reg_proj4, getTransform)
{
    EXPECT_TRUE(false) << "Not implemented yet";
    //
    //    beforeEach(function() {
    //      register(proj4);
    //    });
    //
    //    it('returns a function', function() {
    //      const transform = getTransform('GOOGLE', 'EPSG:4326');
    //      expect(typeof transform).to.be('function');
    //    });
    //
    //    it('returns a transform function', function() {
    //      const transform = getTransform('GOOGLE', 'EPSG:4326');
    //      expect(typeof transform).to.be('function');
    //
    //      const output = transform([-626172.13571216376, 6887893.4928337997]);
    //
    //      expect(output[0]).to.roughlyEqual(-5.625, 1e-9);
    //      expect(output[1]).to.roughlyEqual(52.4827802220782, 1e-9);
    //
    //    });
    //
    //    it('works for longer arrays of coordinate values', function() {
    //      const transform = getTransform('GOOGLE', 'EPSG:4326');
    //      expect(typeof transform).to.be('function');
    //
    //      const output = transform([
    //        -626172.13571216376, 6887893.4928337997,
    //        -12000000, 5000000,
    //        -626172.13571216376, 6887893.4928337997
    //      ]);
    //
    //      expect(output[0]).to.roughlyEqual(-5.625, 1e-9);
    //      expect(output[1]).to.roughlyEqual(52.4827802220782, 1e-9);
    //      expect(output[2]).to.roughlyEqual(-107.79783409434258, 1e-9);
    //      expect(output[3]).to.roughlyEqual(40.91627447067577, 1e-9);
    //      expect(output[4]).to.roughlyEqual(-5.625, 1e-9);
    //      expect(output[5]).to.roughlyEqual(52.4827802220782, 1e-9);
    //    });
    //
    //    it('accepts an optional destination array', function() {
    //      const transform = getTransform('EPSG:3857', 'EPSG:4326');
    //      const input = [-12000000, 5000000];
    //      const output = [];
    //
    //      const got = transform(input, output);
    //      expect(got).to.be(output);
    //
    //      expect(output[0]).to.roughlyEqual(-107.79783409434258, 1e-9);
    //      expect(output[1]).to.roughlyEqual(40.91627447067577, 1e-9);
    //
    //      expect(input).to.eql([-12000000, 5000000]);
    //    });
    //
    //    it('accepts a dimension', function() {
    //      const transform = getTransform('GOOGLE', 'EPSG:4326');
    //      expect(typeof transform).to.be('function');
    //
    //      const dimension = 3;
    //      const output = transform([
    //        -626172.13571216376, 6887893.4928337997, 100,
    //        -12000000, 5000000, 200,
    //        -626172.13571216376, 6887893.4928337997, 300
    //      ], undefined, dimension);
    //
    //      expect(output[0]).to.roughlyEqual(-5.625, 1e-9);
    //      expect(output[1]).to.roughlyEqual(52.4827802220782, 1e-9);
    //      expect(output[2]).to.be(100);
    //      expect(output[3]).to.roughlyEqual(-107.79783409434258, 1e-9);
    //      expect(output[4]).to.roughlyEqual(40.91627447067577, 1e-9);
    //      expect(output[5]).to.be(200);
    //      expect(output[6]).to.roughlyEqual(-5.625, 1e-9);
    //      expect(output[7]).to.roughlyEqual(52.4827802220782, 1e-9);
    //      expect(output[8]).to.be(300);
    //    });
    //  });
}
//
//  describe('ol.proj.transform()', function() {
TEST_F(ol_reg_proj4, transform)
{
//
//    it('transforms a 2d coordinate', function() {
//      const got = transform([-10, -20], 'EPSG:4326', 'EPSG:3857');
//      expect(got).to.have.length(2);
//      expect(got[0]).to.roughlyEqual(-1113194.9079327357, 1e-3);
//      expect(got[1]).to.roughlyEqual(-2273030.92698769, 1e-3);
//    });
//
//    it('transforms a 3d coordinate', function() {
//      const got = transform([-10, -20, 3], 'EPSG:4326', 'EPSG:3857');
//      expect(got).to.have.length(3);
//      expect(got[0]).to.roughlyEqual(-1113194.9079327357, 1e-3);
//      expect(got[1]).to.roughlyEqual(-2273030.92698769, 1e-3);
//      expect(got[2]).to.be(3);
//    });
//
//    it('transforms a 4d coordinate', function() {
//      const got = transform([-10, -20, 3, 4], 'EPSG:4326', 'EPSG:3857');
//      expect(got).to.have.length(4);
//      expect(got[0]).to.roughlyEqual(-1113194.9079327357, 1e-3);
//      expect(got[1]).to.roughlyEqual(-2273030.92698769, 1e-3);
//      expect(got[2]).to.be(3);
//      expect(got[3]).to.be(4);
//    });
//
//    it('works with 3d points and proj4 defs', function() {
//      proj4.defs('custom',
//        '+proj=somerc +lat_0=46.95240555555556 +lon_0=7.439583333333333 ' +
//          '+k_0=1 +x_0=600000 +y_0=200000 +ellps=bessel ' +
//          '+towgs84=674.374,15.056,405.346,0,0,0,0 +units=m +no_defs');
//      register(proj4);
//
//      const got = transform([-111, 45.5, 123], 'EPSG:4326', 'custom');
//      expect(got).to.have.length(3);
//      expect(got[0]).to.roughlyEqual(-6601512.194209638, 1);
//      expect(got[1]).to.roughlyEqual(6145843.802742112, 1);
//      expect(got[2]).to.be(123);
//
//      delete proj4.defs.custom;
//      clearAllProjections();
//      addCommon();
//    });
//
//  });
    EXPECT_TRUE(false) << "Not implemented yet";
}

class ol_reg_proj4_custom : public ::testing::Test {
public:
    ol_reg_proj4_custom()
    {}

    virtual void SetUp() override
    {
        //    afterEach(function() {
        //      delete proj4.defs['EPSG:26782'];
        //      delete proj4.defs['EPSG:3739'];
        //      delete proj4.defs['EPSG:4269'];
        //      delete proj4.defs['EPSG:4279'];
        //      clearAllProjections();
        //      addCommon();
        //    });

        ol::proj::proj4::proj4.defs.erase("EPSG:26782");
        ol::proj::proj4::proj4.defs.erase("EPSG:3739");
        ol::proj::proj4::proj4.defs.erase("EPSG:4269");
        ol::proj::proj4::proj4.defs.erase("EPSG:4279");

        ol::proj::clearAllProjections();
        ol::proj::addCommon();
#if 0
            beforeEach(function() {
              proj4.defs('EPSG:26782',
                '+proj=lcc +lat_1=29.3 +lat_2=30.7 +lat_0=28.66666666666667 ' +
                  '+lon_0=-91.33333333333333 +x_0=609601.2192024384 +y_0=0 ' +
                  '+ellps=clrk66 +datum=NAD27 +to_meter=0.3048006096012192 +no_defs');
              proj4.defs('EPSG:3739', '+proj=tmerc +lat_0=40.5 ' +
                  '+lon_0=-110.0833333333333 +k=0.9999375 +x_0=800000.0000101599 ' +
                  '+y_0=99999.99998983997 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 ' +
                  '+units=us-ft +no_defs');
              proj4.defs('EPSG:4269', 'GEOGCS["NAD83",' +
                  'DATUM["North_American_Datum_1983",' +
                  'SPHEROID["GRS 1980",6378137,298.257222101,' +
                  'AUTHORITY["EPSG","7019"]],' +
                  'AUTHORITY["EPSG","6269"]],' +
                  'PRIMEM["Greenwich",0,AUTHORITY["EPSG","8901"]],' +
                  'UNIT["degree",0.01745329251994328,AUTHORITY["EPSG","9122"]],' +
                  'AUTHORITY["EPSG","4269"]]');
              proj4.defs('EPSG:4279', 'GEOGCS["OS(SN)80",DATUM["OS_SN_1980",' +
                  'SPHEROID["Airy 1830",6377563.396,299.3249646,' +
                  'AUTHORITY["EPSG","7001"]],' +
                  'AUTHORITY["EPSG","6279"]],' +
                  'PRIMEM["Greenwich",0,AUTHORITY["EPSG","8901"]],' +
                  'UNIT["degree",0.01745329251994328,AUTHORITY["EPSG","9122"]],' +
                  'AUTHORITY["EPSG","4279"]]');
              register(proj4);
            });
#endif
        ol::proj::proj4::proj4.defs("EPSG:26782",
            "proj=lcc +lat_1=29.3 +lat_2=30.7 +lat_0=28.66666666666667 " \
            "+lon_0=-91.33333333333333 +x_0=609601.2192024384 +y_0=0 " \
            "+ellps=clrk66 +datum=NAD27 +to_meter=0.3048006096012192 +no_defs");
        ol::proj::proj4::proj4.defs("EPSG:3739", "+proj=tmerc +lat_0=40.5 " \
            "+lon_0=-110.0833333333333 +k=0.9999375 +x_0=800000.0000101599 " \
            "+y_0=99999.99998983997 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 " \
            "+units=us-ft +no_defs");
#if 0
        ol::proj::proj4::proj4.defs("EPSG:4269", "GEOGCS[\"NAD83\"," \
            "DATUM[\"North_American_Datum_1983\"," \
            "SPHEROID[\"GRS 1980\",6378137,298.257222101," \
            "AUTHORITY[\"EPSG\", \"7019\"]]," \
            "AUTHORITY[\"EPSG\",\"6269\"]]," \
            "PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]]," \
            "UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]]," \
            "AUTHORITY[\"EPSG\",\"4269\"]]");
        ol::proj::proj4::proj4.defs("EPSG:4279", "GEOGCS[\"OS(SN)80\",DATUM[\"OS_SN_1980\"," \
            "SPHEROID[\"Airy 1830\",6377563.396,299.3249646," \
            "AUTHORITY[\"EPSG\",\"7001\"]]," \
            "AUTHORITY[\"EPSG\",\"6279\"]]," \
            "PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]]," \
            "UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]]," \
            "AUTHORITY[\"EPSG\",\"4279\"]]");
#else
        ol::proj::proj4::proj4.defs("EPSG:4269", "+proj=longlat +ellps=GRS80 +datum=NAD83 +no_defs");
        ol::proj::proj4::proj4.defs("EPSG:4279", "+proj=longlat +ellps=airy +no_defs");
#endif
        ol::proj::proj4::Register(ol::proj::proj4::proj4);
    }
};

//
//  describe('ol.proj.Projection.prototype.getMetersPerUnit()', function() {
TEST_F(ol_reg_proj4_custom, getMetersPerUnit)
{
    using namespace ol::proj;

//    it('returns value in meters', function() {
    {
        auto epsg4326 = getProjection("EPSG:4326");
        ASSERT_TRUE(epsg4326 != 0);
        //      expect(epsg4326.getMetersPerUnit()).to.eql(METERS_PER_UNIT);
        EXPECT_EQ(METERS_PER_UNIT["degrees"], epsg4326->getMetersPerUnit());
    }
//    });
//
//    it('works for proj4js projections without units', function() {
    {
        auto epsg26782 = getProjection("EPSG:26782");
        ASSERT_TRUE(epsg26782 != 0);
        //      expect(epsg26782.getMetersPerUnit()).to.eql(0.3048006096012192);
        EXPECT_EQ(0.3048006096012192, epsg26782->getMetersPerUnit());
    }
//    });
//
//    it('works for proj4js projections with units other than m', function() {
    {
        auto epsg3739 = getProjection("EPSG:3739");
        ASSERT_TRUE(epsg3739 != 0);
        EXPECT_EQ(1200.0 / 3937.0, epsg3739->getMetersPerUnit());
    }
//    });
//
//    it('works for proj4js OGC WKT GEOGCS projections', function() {
    {
       auto epsg4269 = getProjection("EPSG:4269");
       ASSERT_TRUE(epsg4269 != 0);
        //      expect(epsg4269.getMetersPerUnit()).to.eql(
        //        6378137 * 0.01745329251994328);
       EXPECT_NEAR(6378137 * 0.01745329251994328, epsg4269->getMetersPerUnit(), 1e-9);
       auto epsg4279 = getProjection("EPSG:4279");
       ASSERT_TRUE(epsg4279 != 0);
        //      expect(epsg4279.getMetersPerUnit()).to.eql(
        //        6377563.396 * 0.01745329251994328);
       EXPECT_NEAR(6377563.396 * 0.01745329251994328, epsg4279->getMetersPerUnit(), 1e-9);
    }
//    });
//  });
}
//
//});
