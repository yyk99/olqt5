#include <gtest/gtest.h>

//import {add as addCoordinate, 
//    scale as scaleCoordinate, 
//    rotate as rotateCoordinate, 
//    equals as coordinatesEqual, 
//    format as formatCoordinate, 
//    closestOnCircle, 
//    closestOnSegment, 
//    createStringXY, 
//    squaredDistanceToSegment, 
//    toStringXY, toStringHDMS} from '../../../src/ol/coordinate.js';
#include "../../../src/ol/coordinate.h"
//import Circle from '../../../src/ol/geom/Circle.js';
#include "../../../src/ol/geom/Circle.h"

using namespace ol::coordinate;

//
//
//describe('ol.coordinate', function() {

TEST(ol_coordinate, add)
{
    //  describe('#add', function() {
    //    let coordinate, delta;
    //
    //    beforeEach(function() {
    //    });
    //
    //    it('returns a coordinate', function() {
    {
        Coordinate coordinate = { 50.73, 7.1 };
        Coordinate      delta = { -2, 3 };

        auto returnedCoordinate = addCoordinate(coordinate, delta);
        //      expect(returnedCoordinate).to.be.an('array');
        EXPECT_EQ(2, returnedCoordinate.size()); // .to.have.length(2);
    }
    //    });
    //
    //    it('adds the delta', function() {
    {
        Coordinate coordinate = { 50.73, 7.1 };
        Coordinate delta = { -2, 3 };

        auto returnedCoordinate = addCoordinate(coordinate, delta);
        ASSERT_EQ(2, returnedCoordinate.size());
        EXPECT_EQ(48.73, returnedCoordinate[0]); // .to.eql(48.73);
        EXPECT_EQ(10.1, returnedCoordinate[1]); // .to.eql(10.1);
    }
    //    });
    //
    //    it('modifies in place', function() {
    {
        Coordinate coordinate = { 50.73, 7.1 };
        Coordinate delta = { -2, 3 };

        addCoordinate(coordinate, delta);
        EXPECT_EQ(48.73, coordinate[0]); // .to.eql(48.73);
        EXPECT_EQ(10.1, coordinate[1]); // .to.eql(10.1);
    }
    //    });
    //  });
}


TEST(ol_coordinate, equals)
{
    //  describe('#equals', function() {
    Coordinate cologne = { 50.93333, 6.95 };
    Coordinate bonn1 = { 50.73, 7.1 };
    Coordinate bonn2 = { 50.73000, 7.10000 };
    //
    //    it('compares correctly', function() {
    bool bonnEqualsBonn = coordinatesEqual(bonn1, bonn2);
    bool bonnEqualsCologne = coordinatesEqual(bonn1, cologne);
    EXPECT_TRUE(bonnEqualsBonn); // .to.be(true);
    EXPECT_FALSE(bonnEqualsCologne); // .to.be(false);
    //    });
    //  });
    //
}

TEST(ol_coordinate, format)
{
    //  describe('#format', function() {
    //    let coordinate;
    //    beforeEach(function() {
    Coordinate coordinate = { 6.6123, 46.7919 };
    //    });
    //
    //    it('rounds the values', function() {
    {
        std::string s = formatCoordinate(coordinate, "{x} {y}", 0);
        EXPECT_EQ("7 47", s);
    }
    //
    //    it('handles the optional fractionDigits param', function() {
    {
        std::string  s = formatCoordinate(coordinate, "{x} {y}", 3);
        EXPECT_EQ("6.612 46.792", s); // (string).to.eql('6.612 46.792');
    }
    //    });
    //  });
    //
}

TEST(ol_coordinate, createStringXY)
{

    //  describe('#createStringXY', function() {
    //    let coordinate, created, formatted;
    //    beforeEach(function() {
    //      coordinate = [6.6123, 46.7919];
    //      created = null;
    //      formatted = null;
    //    });
    //
    //    it('returns a CoordinateFormatType', function() {
    //      created = createStringXY();
    //      expect(created).to.be.a('function');
    //
    //      formatted = created(coordinate);
    //      expect(formatted).to.be.a('string');
    //      expect(formatted).to.eql('7, 47');
    //    });
    //
    //    it('respects opt_fractionDigits', function() {
    //      created = createStringXY(3);
    //      expect(created).to.be.a('function');
    //
    //      formatted = created(coordinate);
    //      expect(formatted).to.be.a('string');
    //      expect(formatted).to.eql('6.612, 46.792');
    //    });
    //  });
}

TEST(ol_coordinate, closestOnCircle)
{

//  describe('#closestOnCircle', function() {
//    const center = [5, 10];
//    const circle = new Circle(center, 10);
//    it('can find the closest point on circle', function() {
//      expect(closestOnCircle([-20, 10], circle))
//        .to.eql([-5, 10]);
//    });
//    it('can handle coordinate equal circle center', function() {
//      expect(closestOnCircle(center, circle))
//        .to.eql([15, 10]);
//    });
//  });
}

TEST(ol_coordinate, closestOnSegment)
{
    //
//  describe('#closestOnSegment', function() {
//    it('can handle points where the foot of the perpendicular is closest',
//      function() {
//        const point = [2, 5];
//        const segment = [[-5, 0], [10, 0]];
//        expect(closestOnSegment(point, segment))
//          .to.eql([2, 0]);
//      });
//    it('can handle points where the foot of the perpendicular is not closest',
//      function() {
//        const point = [0, -6];
//        const segment = [[-5, 0], [0, -1]];
//        expect(closestOnSegment(point, segment))
//          .to.eql([0, -1]);
//      });
//  });
//
}

TEST(ol_coordinate, format2)
{
    //  describe('#format', function() {
    //    it('can deal with undefined coordinate', function() {
    //      expect(formatCoordinate()).to.be('');
    //    });
    //    it('formats a coordinate into a template (default precision is 0)',
    //      function() {
    //        const coord = [7.85, 47.983333];
    //        const template = 'Coordinate is ({x}|{y}).';
    //        const got = formatCoordinate(coord, template);
    //        const expected = 'Coordinate is (8|48).';
    //        expect(got).to.be(expected);
    //      });
    //    it('formats a coordinate into a template and respects precision)',
    //      function() {
    //        const coord = [7.85, 47.983333];
    //        const template = 'Coordinate is ({x}|{y}).';
    //        const got = formatCoordinate(coord, template, 2);
    //        const expected = 'Coordinate is (7.85|47.98).';
    //        expect(got).to.be(expected);
    //      });
    //  });
    //
}

TEST(ol_coordinate, rotate)
{
    //  describe('#rotate', function() {
//    it('can rotate point in place', function() {
//      const coord = [7.85, 47.983333];
//      const rotateRadians = Math.PI / 2; // 90 degrees
//      rotateCoordinate(coord, rotateRadians);
//      expect(coord[0].toFixed(6)).to.eql('-47.983333');
//      expect(coord[1].toFixed(6)).to.eql('7.850000');
//    });
//    it('returns the rotated point', function() {
//      const coord = [7.85, 47.983333];
//      const rotateRadians = Math.PI / 2; // 90 degrees
//      const rotated = rotateCoordinate(coord, rotateRadians);
//      expect(rotated[0].toFixed(7)).to.eql('-47.9833330');
//      expect(rotated[1].toFixed(7)).to.eql('7.8500000');
//    });
//  });
//
}

TEST(ol_coordinate, scale)
{
    //  describe('#scale', function() {
//    it('can scale point in place', function() {
//      const coord = [7.85, 47.983333];
//      const scale = 1.2;
//      scaleCoordinate(coord, scale);
//      expect(coord[0].toFixed(7)).to.eql('9.4200000');
//      expect(coord[1].toFixed(7)).to.eql('57.5799996');
//    });
//    it('returns the scaled point', function() {
//      const coord = [7.85, 47.983333];
//      const scale = 1.2;
//      const scaledCoord = scaleCoordinate(coord, scale);
//      expect(scaledCoord[0].toFixed(7)).to.eql('9.4200000');
//      expect(scaledCoord[1].toFixed(7)).to.eql('57.5799996');
//    });
//  });
//
}

TEST(ol_coordinate, squaredDistanceToSegment)
{
    //  describe('#squaredDistanceToSegment', function() {
//    it('can handle points where the foot of the perpendicular is closest',
//      function() {
//        const point = [2, 5];
//        const segment = [[-5, 0], [10, 0]];
//        expect(squaredDistanceToSegment(point, segment))
//          .to.eql(25);
//      });
//    it('can handle points where the foot of the perpendicular is not closest',
//      function() {
//        const point = [0, -6];
//        const segment = [[-5, 0], [0, -1]];
//        expect(squaredDistanceToSegment(point, segment))
//          .to.eql(25);
//      });
//
//  });
//
}
TEST(ol_coordinate, toStringHDMS)
{
    //  describe('#toStringHDMS', function() {
//    it('returns the empty string on undefined input', function() {
//      const got = toStringHDMS();
//      const expected = '';
//      expect(got).to.be(expected);
//    });
//    it('formats with zero fractional digits as default', function() {
//      const coord = [7.85, 47.983333];
//      const got = toStringHDMS(coord);
//      const expected = '47° 59′ 00″ N 7° 51′ 00″ E';
//      expect(got).to.be(expected);
//    });
//    it('formats with given fractional digits, if passed', function() {
//      const coord = [7.85, 47.983333];
//      const got = toStringHDMS(coord, 3);
//      const expected = '47° 58′ 59.999″ N 7° 51′ 00.000″ E';
//      expect(got).to.be(expected);
//    });
//  });
//
}

TEST(ol_coordinate, toStringXY)
{
    //  describe('#toStringXY', function() {
//    it('formats with zero fractional digits as default', function() {
//      const coord = [7.85, 47.983333];
//      const got = toStringXY(coord);
//      const expected = '8, 48';
//      expect(got).to.be(expected);
//    });
//    it('formats with given fractional digits, if passed', function() {
//      const coord = [7.85, 47.983333];
//      const got = toStringXY(coord, 2);
//      const expected = '7.85, 47.98';
//      expect(got).to.be(expected);
//    });
//  });
//
//});
}
