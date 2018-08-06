#include <gtest/gtest.h>

#include <limits>
//import {clamp, lerp, cosh, roundUpToPowerOfTwo, solveLinearSystem, toDegrees, toRadians, modulo} from '../../../src/ol/math.js';
#include "../../../src/ol/math.h"

using namespace ol;
using namespace ol::math;

//describe('ol.math.clamp', function() {
TEST(ol_math, clamp)
{
    //  it('returns the correct value at -Infinity', function() {
    //    expect(clamp(-Infinity, 10, 20)).to.eql(10);
    EXPECT_EQ(10, ol::math::clamp(-std::numeric_limits<ol::number_t>::infinity(), 10, 20));
    //  });
    //
    //  it('returns the correct value at min', function() {
    //    expect(clamp(10, 10, 20)).to.eql(10);
    EXPECT_EQ(10, clamp(10, 10, 20));
    //  });
    //
    //  it('returns the correct value at mid point', function() {
    //    expect(clamp(15, 10, 20)).to.eql(15);
    EXPECT_EQ(15, clamp(15, 10, 20));
    //  });
    //
    //  it('returns the correct value at max', function() {
    //    expect(clamp(20, 10, 20)).to.eql(20);
    EXPECT_EQ(20, clamp(20, 10, 20));
    //  });
    //
    //  it('returns the correct value at Infinity', function() {
    //    expect(clamp(Infinity, 10, 20)).to.eql(20);
    EXPECT_EQ(20, clamp(std::numeric_limits<ol::number_t>::infinity(), 10, 20));
    //  });
}
//});

//describe('ol.math.cosh', function() {
TEST(ol_math, cosh)
{
    //
    //  it('returns the correct value at -Infinity', function() {
    //    expect(cosh(-Infinity)).to.eql(Infinity);
    EXPECT_EQ(std::numeric_limits<ol::number_t>::infinity(), std::cosh(-std::numeric_limits<ol::number_t>::infinity()));

    //  });
    //
    //  it('returns the correct value at -1', function() {
    //    expect(cosh(-1)).to.roughlyEqual(1.5430806348152437, 1e-9);
    EXPECT_NEAR(1.5430806348152437, std::cosh(-1), 1e-9);
    //  });
    //
    //  it('returns the correct value at 0', function() {
    //    expect(cosh(0)).to.eql(1);
    EXPECT_EQ(1, std::cosh(0));
    //  });
    //
    //  it('returns the correct value at 1', function() {
    //    expect(cosh(1)).to.roughlyEqual(1.5430806348152437, 1e-9);
    EXPECT_NEAR(1.5430806348152437, std::cosh(1), 1e-9);
    //  });
    //
    //  it('returns the correct value at Infinity', function() {
    //    expect(cosh(Infinity)).to.eql(Infinity);
    EXPECT_EQ(std::numeric_limits<ol::number_t>::infinity(), std::cosh(std::numeric_limits<ol::number_t>::infinity()));
    //  });
    //
    //});
}

TEST(ol_math, roundUpToPowerOfTwo)
{
    //
    //  it('raises an exception when x is negative', function() {
    //    expect(function() {
    //      roundUpToPowerOfTwo(-1);
    //    }).to.throwException();
    EXPECT_THROW(roundUpToPowerOfTwo(-1), std::exception);
    //  });
    //
    //  it('raises an exception when x is zero', function() {
    //    expect(function() {
    //      roundUpToPowerOfTwo(0);
    //    }).to.throwException();
    EXPECT_THROW(roundUpToPowerOfTwo(0), std::exception);
    //  });
    //
    //  it('returns the expected value for simple powers of two', function() {
    //    expect(roundUpToPowerOfTwo(1)).to.be(1);
    EXPECT_EQ(1, roundUpToPowerOfTwo(1));
    //    expect(roundUpToPowerOfTwo(2)).to.be(2);
    EXPECT_EQ(2, roundUpToPowerOfTwo(2));
    //    expect(roundUpToPowerOfTwo(4)).to.be(4);
    EXPECT_EQ(4, roundUpToPowerOfTwo(4));
    //    expect(roundUpToPowerOfTwo(8)).to.be(8);
    EXPECT_EQ(8, roundUpToPowerOfTwo(8));
    //    expect(roundUpToPowerOfTwo(16)).to.be(16);
    EXPECT_EQ(16, roundUpToPowerOfTwo(16));
    //    expect(roundUpToPowerOfTwo(32)).to.be(32);
    EXPECT_EQ(32, roundUpToPowerOfTwo(32));
    //    expect(roundUpToPowerOfTwo(64)).to.be(64);
    EXPECT_EQ(64, roundUpToPowerOfTwo(64));
    //    expect(roundUpToPowerOfTwo(128)).to.be(128);
    EXPECT_EQ(128, roundUpToPowerOfTwo(128));
    //    expect(roundUpToPowerOfTwo(256)).to.be(256);
    EXPECT_EQ(256, roundUpToPowerOfTwo(256));
    //  });
    //
    //  it('returns the expected value for simple powers of ten', function() {
    //    expect(roundUpToPowerOfTwo(1)).to.be(1);
    EXPECT_EQ(1, roundUpToPowerOfTwo(1));
    //    expect(roundUpToPowerOfTwo(10)).to.be(16);
    EXPECT_EQ(16, roundUpToPowerOfTwo(10));
    //    expect(roundUpToPowerOfTwo(100)).to.be(128);
    EXPECT_EQ(128, roundUpToPowerOfTwo(100));
    //    expect(roundUpToPowerOfTwo(1000)).to.be(1024);
    EXPECT_EQ(1024, roundUpToPowerOfTwo(1000));
    //    expect(roundUpToPowerOfTwo(10000)).to.be(16384);
    EXPECT_EQ(16384, roundUpToPowerOfTwo(10000));
    //    expect(roundUpToPowerOfTwo(100000)).to.be(131072);
    EXPECT_EQ(131072, roundUpToPowerOfTwo(100000));
    //    expect(roundUpToPowerOfTwo(1000000)).to.be(1048576);
    EXPECT_EQ(1048576, roundUpToPowerOfTwo(1000000));
    //    expect(roundUpToPowerOfTwo(10000000)).to.be(16777216);
    EXPECT_EQ(16777216, roundUpToPowerOfTwo(10000000));
    //  });
    //
}
//
TEST(ol_math, solveLinearSystem)
{
    //
    //  it('calculates correctly', function() 
    {
        //    const result = solveLinearSystem([
        //      [2, 1, 3, 1],
        //      [2, 6, 8, 3],
        //      [6, 8, 18, 5]
        //    ]);
        auto result = solveLinearSystem({
                {2, 1, 3, 1},
                {2, 6, 8, 3},
                {6, 8, 18, 5}
            });

        //    expect(result[0]).to.roughlyEqual(0.3, 1e-9);
        EXPECT_NEAR(0.3, result[0], 1e-9);
        //    expect(result[1]).to.roughlyEqual(0.4, 1e-9);
        EXPECT_NEAR(0.4, result[1], 1e-9);
        //    expect(result[2]).to.roughlyEqual(0, 1e-9);
        EXPECT_NEAR(0, result[2], 1e-9);
    }
    //
    //  it('can handle singular matrix', function() 
    {
        auto result = solveLinearSystem({
            {2, 1, 3, 1},
              {2, 6, 8, 3},
              {2, 1, 3, 1}
            });
        EXPECT_EQ(0, result.size());
    }
    //
}

//
TEST(ol_math, toDegrees) {
    //  it('returns the correct value at -π', function() {
    //    expect(toDegrees(-Math.PI)).to.be(-180);
    EXPECT_EQ(-180, toDegrees(-PI));
    //  });
    //  it('returns the correct value at 0', function() {
    //    expect(toDegrees(0)).to.be(0);
    EXPECT_EQ(0, toDegrees(0));
    //  });
    //  it('returns the correct value at π', function() {
    //    expect(toDegrees(Math.PI)).to.be(180);
    EXPECT_EQ(180, toDegrees(PI));
    //  });
}

TEST(ol_math, toRadians) {
//  it('returns the correct value at -180', function() {
//    expect(toRadians(-180)).to.be(-Math.PI);
    EXPECT_EQ(-PI, toRadians(-180));
//  });
//  it('returns the correct value at 0', function() {
//    expect(toRadians(0)).to.be(0);
    EXPECT_EQ(0, toRadians(0));
//  });
//  it('returns the correct value at 180', function() {
//    expect(toRadians(180)).to.be(Math.PI);
    EXPECT_EQ(PI, toRadians(180));
//  });
}

TEST(ol_math, modulo) 
{
    //  it('256 / 8 returns 0', function() {
    //    expect(modulo(256, 8)).to.be(0);
    EXPECT_EQ(0, modulo(256, 8));
    //  });
    //  it('positive and positive returns a positive ', function() {
    //    expect(modulo(7, 8)).to.be(7);
    EXPECT_EQ(7, modulo(7, 8));
    //  });
    //  it('same Dividend and Divisor returns 0', function() {
    //    expect(modulo(4, 4)).to.be(0);
    EXPECT_EQ(0, modulo(4, 4));
    //  });
    //  it('negative and positive returns positive', function() {
    //    expect(modulo(-3, 4)).to.be(1);
    EXPECT_EQ(1, modulo(-3, 4));
    //  });
    //  it('negative and negative returns negative', function() {
    //    expect(modulo(-4, -5)).to.be(-4);
    EXPECT_EQ(-4, modulo(-4, -5));
    //    expect(modulo(-3, -4)).to.be(-3);
    EXPECT_EQ(-3, modulo(-3, -4));
    //  });
    //  it('positive and negative returns negative', function() {
    //    expect(modulo(3, -4)).to.be(-1);
    EXPECT_EQ(-1, modulo(3, -4));
    //    expect(modulo(1, -5)).to.be(-4);
    EXPECT_EQ(-4, modulo(1, -5));
    //    expect(modulo(6, -5)).to.be(-4);
    EXPECT_EQ(-4, modulo(6, -5));
    //  });
}

TEST(ol_math, lerp)
{
    //  it('correctly interpolated numbers', function() {
    //    expect(lerp(0, 0, 0)).to.be(0);
    EXPECT_EQ(0, lerp(0, 0, 0));
    //    expect(lerp(0, 1, 0)).to.be(0);
    EXPECT_EQ(0, lerp(0, 1, 0));
    //    expect(lerp(1, 11, 5)).to.be(51);
    EXPECT_EQ(51, lerp(1, 11, 5));
    //  });
    //  it('correctly interpolates floats', function() {
    //    expect(lerp(0, 1, 0.5)).to.be(0.5);
    EXPECT_EQ(0.5, lerp(0, 1, 0.5));
    //    expect(lerp(0.25, 0.75, 0.5)).to.be(0.5);
    EXPECT_EQ(0.5, lerp(0.25, 0.75, 0.5));
    //  });
}
