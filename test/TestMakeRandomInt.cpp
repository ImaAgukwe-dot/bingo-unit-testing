#include "MakeRandomInt.h"
#include "gtest/gtest.h"

TEST(TestMakeRandomInt, getInstanceReturnsSameInstance) {
  MakeRandomInt& a = MakeRandomInt::getInstance();
  MakeRandomInt& b = MakeRandomInt::getInstance();
  EXPECT_EQ(&a, &b);
}

TEST(TestMakeRandomInt, getValueInRange) {
  MakeRandomInt& rng = MakeRandomInt::getInstance();
  for (unsigned i = 0; i < 20; ++i) {
    unsigned val = rng.getValue(10);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 10u);
  }
}

TEST(TestMakeRandomInt, getValueWithUpperBound1AlwaysReturns0) {
  MakeRandomInt& rng = MakeRandomInt::getInstance();
  for (unsigned i = 0; i < 10; ++i) {
    EXPECT_EQ(rng.getValue(1), 0u);
  }
}

TEST(TestMakeRandomInt, getValueDefaultUpperBoundInRange) {
  MakeRandomInt& rng = MakeRandomInt::getInstance();
  for (unsigned i = 0; i < 20; ++i) {
    unsigned val = rng.getValue();
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 10u);
  }
}

TEST(TestMakeRandomInt, getValueLargeUpperBound) {
  MakeRandomInt& rng = MakeRandomInt::getInstance();
  for (unsigned i = 0; i < 20; ++i) {
    unsigned val = rng.getValue(75);
    EXPECT_GE(val, 0u);
    EXPECT_LT(val, 75u);
  }
}