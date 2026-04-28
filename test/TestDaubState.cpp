#include "DaubState.h"
#include "gtest/gtest.h"

TEST(TestNoDaub, isDaubedReturnsFalse) {
  NoDaub nd;
  EXPECT_FALSE(nd.isDaubed());
}
 
TEST(TestNoDaub, isCorrectReturnsTrue) {
  NoDaub nd;
  EXPECT_TRUE(nd.isCorrect());
}
 
// GoodDaub Tests
 
TEST(TestGoodDaub, isDaubedReturnsTrue) {
  GoodDaub gd;
  EXPECT_TRUE(gd.isDaubed());
}
 
TEST(TestGoodDaub, isCorrectReturnsTrue) {
  GoodDaub gd;
  EXPECT_TRUE(gd.isCorrect());
}
 
// BadDaub Tests
 
TEST(TestBadDaub, isDaubedReturnsTrue) {
  BadDaub bd;
  EXPECT_TRUE(bd.isDaubed());
}
 
TEST(TestBadDaub, isCorrectReturnsFalse) {
  BadDaub bd;
  EXPECT_FALSE(bd.isCorrect());
}
 
// NeedsDaub Tests
 
TEST(TestNeedsDaub, isDaubedReturnsFalse) {
  NeedsDaub nd;
  EXPECT_FALSE(nd.isDaubed());
}
 
TEST(TestNeedsDaub, isCorrectReturnsFalse) {
  NeedsDaub nd;
  EXPECT_FALSE(nd.isCorrect());
}