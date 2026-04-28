#include <string>
#include "Square.h"
#include "DaubState.h"
#include "gtest/gtest.h"

TEST(TestFreeSquare, constructorDefaultValue) {
  FreeSquare fs;
  EXPECT_EQ(fs.getValue(), 0u);
}
 
TEST(TestFreeSquare, constructorWithValue) {
  FreeSquare fs(5);
  EXPECT_EQ(fs.getValue(), 0u);  // FreeSquare ignores value, always 0
}

TEST(TestFreeSquare, daubStateIsGoodDaubInitially) {
  FreeSquare fs;
  EXPECT_TRUE(fs.getDaubState()->isDaubed());
  EXPECT_TRUE(fs.getDaubState()->isCorrect());
}
 
TEST(TestFreeSquare, daubSquareAlwaysReturnsTrue) {
  FreeSquare fs;
  EXPECT_TRUE(fs.daubSquare(0));
  EXPECT_TRUE(fs.daubSquare(10));
  EXPECT_TRUE(fs.daubSquare(75));
}
 
TEST(TestFreeSquare, daubStateUnchangedAfterDaub) {
  FreeSquare fs;
  fs.daubSquare(42);
  EXPECT_TRUE(fs.getDaubState()->isDaubed());
  EXPECT_TRUE(fs.getDaubState()->isCorrect());
}

TEST(TestFreeSquare, shouldDaubSquareDoesNotChangeState) {
  FreeSquare fs;
  fs.shouldDaubSquare(10);
  EXPECT_TRUE(fs.getDaubState()->isDaubed());
  EXPECT_TRUE(fs.getDaubState()->isCorrect());
}
 
TEST(TestFreeSquare, resetSquareDoesNotChangeState) {
  FreeSquare fs;
  fs.resetSquare();
  EXPECT_TRUE(fs.getDaubState()->isDaubed());
  EXPECT_TRUE(fs.getDaubState()->isCorrect());
}
 
TEST(TestFreeSquare, toStringReturnsFree) {
  FreeSquare fs;
  EXPECT_EQ(fs.toString(), "free");
}

TEST(TestIntSquare, constructorDefaultValue) {
  IntSquare sq;
  EXPECT_EQ(sq.getValue(), 0u);
}
 
TEST(TestIntSquare, constructorWithValue) {
  IntSquare sq(15);
  EXPECT_EQ(sq.getValue(), 15u);
}

TEST(TestIntSquare, initialStateIsNoDaub) {
  IntSquare sq(10);
  EXPECT_FALSE(sq.getDaubState()->isDaubed());
  EXPECT_TRUE(sq.getDaubState()->isCorrect());
}

TEST(TestIntSquare, daubSquareMatchingNumberSetsGoodDaub) {
  IntSquare sq(20);
  sq.daubSquare(20);
  EXPECT_TRUE(sq.getDaubState()->isDaubed());
  EXPECT_TRUE(sq.getDaubState()->isCorrect());
}
 
TEST(TestIntSquare, daubSquareNonMatchingNumberSetsBadDaub) {
  IntSquare sq(20);
  sq.daubSquare(15);
  EXPECT_TRUE(sq.getDaubState()->isDaubed());
  EXPECT_FALSE(sq.getDaubState()->isCorrect());
}
 
TEST(TestIntSquare, daubSquareReturnsTrueWhenNotPreviouslyDaubed) {
  IntSquare sq(20);
  EXPECT_TRUE(sq.daubSquare(20));
}
 
TEST(TestIntSquare, daubSquareReturnsFalseWhenAlreadyDaubed) {
  IntSquare sq(20);
  sq.daubSquare(20);
  EXPECT_FALSE(sq.daubSquare(20));
}

TEST(TestIntSquare, resetSquareRestoresToNoDaub) {
  IntSquare sq(20);
  sq.daubSquare(20);
  sq.resetSquare();
  EXPECT_FALSE(sq.getDaubState()->isDaubed());
  EXPECT_TRUE(sq.getDaubState()->isCorrect());
}

TEST(TestIntSquare, shouldDaubSquareSetsNeedsDaubWhenMatchAndNotDaubed) {
  IntSquare sq(30);
  sq.shouldDaubSquare(30);
  EXPECT_FALSE(sq.getDaubState()->isDaubed());
  EXPECT_FALSE(sq.getDaubState()->isCorrect());
}
 
TEST(TestIntSquare, shouldDaubSquareDoesNotChangeStateWhenNoMatch) {
  IntSquare sq(30);
  sq.shouldDaubSquare(99);
  EXPECT_FALSE(sq.getDaubState()->isDaubed());
  EXPECT_TRUE(sq.getDaubState()->isCorrect());
}
 
TEST(TestIntSquare, shouldDaubSquareDoesNotChangeStateWhenAlreadyDaubed) {
  IntSquare sq(30);
  sq.daubSquare(30);  // already daubed
  sq.shouldDaubSquare(30);
  EXPECT_TRUE(sq.getDaubState()->isDaubed());
  EXPECT_TRUE(sq.getDaubState()->isCorrect());
}

TEST(TestIntSquare, toStringUndaubedTwoDigits) {
  IntSquare sq(7);
  EXPECT_EQ(sq.toString(), "07");
}
 
TEST(TestIntSquare, toStringDaubedEnclosedInBraces) {
  IntSquare sq(7);
  sq.daubSquare(7);
  EXPECT_EQ(sq.toString(), "{07}");
}
 
TEST(TestIntSquare, toStringTwoDigitNumber) {
  IntSquare sq(42);
  EXPECT_EQ(sq.toString(), "42");
}
 
TEST(TestIntSquare, toStringDaubedTwoDigitNumber) {
  IntSquare sq(42);
  sq.daubSquare(42);
  EXPECT_EQ(sq.toString(), "{42}");
}