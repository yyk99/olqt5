//
// yyk 2018
//

#include <gtest/gtest.h>

//import {compareVersions, padNumber} from '../../../src/ol/string.js';
#include "../../../src/ol/string.h"

using namespace ol::string;

TEST(ol_string, split)
{
    {
        auto s = split("1 2 3 4 5", " ");
        EXPECT_EQ(5, s.size());
    }
    {
        auto s = split("1 2 3 4 5 ", " ");
        EXPECT_EQ(5, s.size());
    }
    {
        auto s = split(" ", " ");
        EXPECT_EQ(0, s.size());
    }
    {
        auto s = split(std::string(), " ");
        EXPECT_EQ(0, s.size());
    }
    {
        auto s = split("1/2/3", '/');
        EXPECT_EQ(3, s.size());
    }
    {
        auto s = split("1/2/3", "/");
        EXPECT_EQ(3, s.size());
    }
}

//
//
//describe('ol.string', function() {
//
TEST(ol_string, padNumber)
{
    //  describe('ol.string.padNumber', function() {
    //
    //    it('returns the correct padding without precision', function() {
    {
        EXPECT_EQ("06.5", padNumber(6.5, 2));
        EXPECT_EQ("006.5", padNumber(6.5, 3));
        EXPECT_EQ("01.25", padNumber(1.25, 2));
        EXPECT_EQ("005", padNumber(5, 3));
    }
    //    });
    //
    //    it('returns the same string when padding is less than length', function() {
    {
        //      expect(padNumber(6.5, 0)).to.be('6.5');
        EXPECT_EQ("6.5", padNumber(6.5, 0));
        //      expect(padNumber(6.5, 1)).to.be('6.5');
        EXPECT_EQ("6.5", padNumber(6.5, 1));
        //      expect(padNumber(1.25, 0)).to.be('1.25');
        EXPECT_EQ("1.25", padNumber(1.25, 0));
        //      expect(padNumber(5, 0)).to.be('5');
        EXPECT_EQ("5", padNumber(5, 0));
        //      expect(padNumber(5, 1)).to.be('5');
        EXPECT_EQ("5", padNumber(5, 1));
    }
    //    });
    //
    //    it('returns the correct string precision is given', function() {
    {
        //      expect(padNumber(6.5, 0, 2)).to.be('6.50');
        EXPECT_EQ("6.50", padNumber(6.5, 0, 2));
        //      expect(padNumber(6.5, 1, 2)).to.be('6.50');
        EXPECT_EQ("6.50", padNumber(6.5, 1, 2));
        //      expect(padNumber(6.5, 2, 2)).to.be('06.50');
        EXPECT_EQ("06.50", padNumber(6.5, 2, 2));
        //      expect(padNumber(1.25, 2, 3)).to.be('01.250');
        EXPECT_EQ("01.250", padNumber(1.25, 2, 3));
        //      expect(padNumber(1.25, 2, 1)).to.be('01.3');
        EXPECT_EQ("01.3", padNumber(1.25, 2, 1));
        //      expect(padNumber(9.9, 2, 0)).to.be('10');
        EXPECT_EQ("10", padNumber(9.9, 2, 0));
        //      expect(padNumber(5, 0, 0)).to.be('5');
        EXPECT_EQ("5", padNumber(5, 0, 0));
        //      expect(padNumber(5, 1, 1)).to.be('5.0');
        EXPECT_EQ("5.0", padNumber(5, 1, 1));
        //      expect(padNumber(5, 2, 1)).to.be('05.0');
        EXPECT_EQ("05.0", padNumber(5, 2, 1));
        //      expect(padNumber(5, 2, 0)).to.be('05');
        EXPECT_EQ("05", padNumber(5, 2, 0));
    }
    //    });
    //
    //  });
}
//

TEST(ol_string, compareVersions)
{
    //  describe('ol.string.compareVersions', function() {
    //    it('should return the correct value for number input', function() {
    {
        //      expect(compareVersions(1, 1)).to.be(0);
        EXPECT_EQ(0, compareVersions(1, 1));
        //      expect(compareVersions(1.0, 1.1)).to.be.below(0);
        EXPECT_EQ(-1, compareVersions(1.0, 1.1));
        //      expect(compareVersions(2.0, 1.1)).to.be.above(0);
        EXPECT_EQ(1, compareVersions(2.0, 1.1));
    }
    //    });
    //    it('should return the correct value for string input', function() {
    {
        //      expect(compareVersions('1.0', '1.0')).to.be(0);
        EXPECT_EQ(0, compareVersions("1.0", "1.0"));
        //      expect(compareVersions('1.0.0.0', '1.0')).to.be(0);
        EXPECT_EQ(0, compareVersions("1.0.0.0", "1.0"));
        //      expect(compareVersions('1.000', '1.0')).to.be(0);
        EXPECT_EQ(0, compareVersions("1.000", "1.0"));
        //      expect(compareVersions('1.0.2.1', '1.1')).to.be.below(0);
        EXPECT_EQ(-1, compareVersions("1.0.2.1", "1.1"));
        //      expect(compareVersions('1.1', '1.0.2.1')).to.be.above(0);
        EXPECT_EQ(1, compareVersions("1.1", "1.0.2.1"));
        //      expect(compareVersions('1', '1.1')).to.be.below(0);
        EXPECT_EQ(-1, compareVersions("1", "1.1"));
        //      expect(compareVersions('2.2', '2')).to.be.above(0);
        EXPECT_EQ(1, compareVersions("2.2", "2"));
        //
        //      expect(compareVersions('9.5', '9.10')).to.be.below(0);
        EXPECT_EQ(-1, compareVersions("9.5", "9.10"));
        //      expect(compareVersions('9.5', '9.11')).to.be.below(0);
        EXPECT_EQ(-1, compareVersions("9.5", "9.11"));
        //      expect(compareVersions('9.11', '9.10')).to.be.above(0);
        EXPECT_EQ(1, compareVersions("9.11", "9.10"));
        //      expect(compareVersions('9.1', '9.10')).to.be.below(0);
        EXPECT_EQ(-1, compareVersions("9.1", "9.10"));
        //      expect(compareVersions('9.1.1', '9.10')).to.be.below(0);
        EXPECT_EQ(-1, compareVersions("9.1.1", "9.10"));
        //      expect(compareVersions('9.1.1', '9.11')).to.be.below(0);
        EXPECT_EQ(-1, compareVersions("9.1.1", "9.11"));
        //
        //      expect(compareVersions(' 7', '6')).to.be.above(0);
        EXPECT_EQ(1, compareVersions(" 7", "6"));
        //      expect(compareVersions('7 ', '6')).to.be.above(0);
        EXPECT_EQ(1, compareVersions("7 ", "6"));
        //      expect(compareVersions(' 7 ', '6')).to.be.above(0);
        EXPECT_EQ(1, compareVersions(" 7 ", "6"));
        //      expect(compareVersions('7', ' 6')).to.be.above(0);
        EXPECT_EQ(1, compareVersions("7", "6"));
        //      expect(compareVersions('7', '6 ')).to.be.above(0);
        EXPECT_EQ(1, compareVersions("7", "6 "));
        //      expect(compareVersions('7', ' 6 ')).to.be.above(0);
        EXPECT_EQ(1, compareVersions("7", " 6 "));
        //      expect(compareVersions(' 7', ' 6')).to.be.above(0);
        EXPECT_EQ(1, compareVersions(" 7", " 6"));
        //      expect(compareVersions('7 ', '6 ')).to.be.above(0);
        EXPECT_EQ(1, compareVersions("7 ", "6 "));
        //      expect(compareVersions(' 7 ', ' 6 ')).to.be.above(0);
        EXPECT_EQ(1, compareVersions(" 7 ", " 6 "));
    }
    //    });
    //  });
}
//});
