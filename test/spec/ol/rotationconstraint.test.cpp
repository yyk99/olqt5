#include <gtest/gtest.h>
//import {createSnapToZero} from '../../../src/ol/rotationconstraint.js';
#include "../../../src/ol/rotationconstraint.h"
//
//
TEST(ol_rotationconstraint, t1)
{
    //describe('ol.rotationconstraint', function() {
    //
    //  describe('SnapToZero', function() {
    //
    //    it('returns expected rotation value', function() {
    {
        auto rotationConstraint = ol::rotationconstraint::createSnapToZero(0.3);
        //
        //      expect(rotationConstraint(0.1, 0)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(0.1, 0).value());
        //      expect(rotationConstraint(0.2, 0)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(0.2, 0).value());
        //      expect(rotationConstraint(0.3, 0)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(0.3, 0).value());
        //      expect(rotationConstraint(0.4, 0)).to.eql(0.4);
        EXPECT_EQ(0.4, rotationConstraint(0.4, 0).value());
        //
        //      expect(rotationConstraint(-0.1, 0)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(-0.1, 0).value());
        //      expect(rotationConstraint(-0.2, 0)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(-0.2, 0).value());
        //      expect(rotationConstraint(-0.3, 0)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(-0.3, 0).value());
        //      expect(rotationConstraint(-0.4, 0)).to.eql(-0.4);
        EXPECT_EQ(-0.4, rotationConstraint(-0.4, 0).value());
        //
        //      expect(rotationConstraint(1, -0.9)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(1, -0.9).value());
        //      expect(rotationConstraint(1, -0.8)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(1, -0.8).value());
        //      // floating-point arithmetic
        //      expect(rotationConstraint(1, -0.7)).not.to.eql(0);
        EXPECT_NE(0, rotationConstraint(1, -0.7).value());
        //      expect(rotationConstraint(1, -0.6)).to.eql(0.4);
        EXPECT_EQ(0.4, rotationConstraint(1, -0.6).value());
        //
        //      expect(rotationConstraint(-1, 0.9)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(-1, 0.9).value());
        //      expect(rotationConstraint(-1, 0.8)).to.eql(0);
        EXPECT_EQ(0, rotationConstraint(-1, 0.8).value());
        //      // floating-point arithmetic
        //      expect(rotationConstraint(-1, 0.7)).not.to.eql(0);
        EXPECT_NE(0, rotationConstraint(-1, 0.7).value());
        //      expect(rotationConstraint(-1, 0.6)).to.eql(-0.4);
        EXPECT_EQ(-0.4, rotationConstraint(-1, 0.6).value());
        //    });
    }
    //
    //  });
    //});
}

