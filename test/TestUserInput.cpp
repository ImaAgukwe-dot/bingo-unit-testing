#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "UserInput.h"
#include "BingoTypes.h"
#include "Exceptions.h"

TEST(TestUserInput, getDoYouResponseYesReturnsTrue) {
  UserInput ui;
  std::istringstream in("yes");
  EXPECT_TRUE(ui.getDoYouResponse(in));
}
 
TEST(TestUserInput, getDoYouResponseNoReturnsFalse) {
  UserInput ui;
  std::istringstream in("no");
  EXPECT_FALSE(ui.getDoYouResponse(in));
}
 
TEST(TestUserInput, getDoYouResponseTrueReturnsTrue) {
  UserInput ui;
  std::istringstream in("true");
  EXPECT_TRUE(ui.getDoYouResponse(in));
}
 
TEST(TestUserInput, getDoYouResponseFalseReturnsFalse) {
  UserInput ui;
  std::istringstream in("false");
  EXPECT_FALSE(ui.getDoYouResponse(in));
}
 
TEST(TestUserInput, getDoYouResponseInvalidThrows) {
  UserInput ui;
  std::istringstream in("maybe");
  EXPECT_THROW(ui.getDoYouResponse(in), bad_input);
}

TEST(TestUserInput, getNumberResponseValidValue) {
  UserInput ui;
  std::istringstream in("5");
  EXPECT_EQ(ui.getNumberResponse(in, 10, 1), 5u);
}
 
TEST(TestUserInput, getNumberResponseMinValue) {
  UserInput ui;
  std::istringstream in("1");
  EXPECT_EQ(ui.getNumberResponse(in, 10, 1), 1u);
}
 
TEST(TestUserInput, getNumberResponseMaxValue) {
  UserInput ui;
  std::istringstream in("10");
  EXPECT_EQ(ui.getNumberResponse(in, 10, 1), 10u);
}
 
TEST(TestUserInput, getNumberResponseInvalidThrows) {
  UserInput ui;
  std::istringstream in("abc");
  EXPECT_THROW(ui.getNumberResponse(in, 10, 0), bad_input);
}
 
TEST(TestUserInput, getNumberResponseMinGreaterThanMaxThrows) {
  UserInput ui;
  std::istringstream in("5");
  EXPECT_THROW(ui.getNumberResponse(in, 1, 10), bad_input);
}
 
TEST(TestUserInput, getGameTypeBingo75) {
  UserInput ui;
  std::istringstream in("75");
  EXPECT_EQ(ui.getGameType(in), BingoTypes::BINGO75);
}
 
TEST(TestUserInput, getGameTypeBingo50) {
  UserInput ui;
  std::istringstream in("50");
  EXPECT_EQ(ui.getGameType(in), BingoTypes::BINGO50);
}
 
TEST(TestUserInput, getGameTypeInvalidThrows) {
  UserInput ui;
  std::istringstream in("99");
  EXPECT_THROW(ui.getGameType(in), bad_input);
}
 
TEST(TestUserInput, getVictoryTypeHorizontal) {
  UserInput ui;
  std::istringstream in("1");
  EXPECT_EQ(ui.getVictoryType(in), BingoTypes::HORIZONTAL_LINE);
}
 
TEST(TestUserInput, getVictoryTypeVertical) {
  UserInput ui;
  std::istringstream in("2");
  EXPECT_EQ(ui.getVictoryType(in), BingoTypes::VERTICAL_LINE);
}
 
TEST(TestUserInput, getVictoryTypeAnyLine) {
  UserInput ui;
  std::istringstream in("3");
  EXPECT_EQ(ui.getVictoryType(in), BingoTypes::ANY_LINE);
}
 
TEST(TestUserInput, getVictoryTypeBlackout) {
  UserInput ui;
  std::istringstream in("4");
  EXPECT_EQ(ui.getVictoryType(in), BingoTypes::BLACKOUT);
}
 
TEST(TestUserInput, getVictoryTypeInvalidThrows) {
  UserInput ui;
  std::istringstream in("9");
  EXPECT_THROW(ui.getVictoryType(in), bad_input);
}
 
// ─── getMoveType ──────────────────────────────────────────────────────────────
 
TEST(TestUserInput, getMoveTypeDaub) {
  UserInput ui;
  std::istringstream in("1");
  EXPECT_EQ(ui.getMoveType(in), BingoTypes::DAUB);
}
 
TEST(TestUserInput, getMoveTypeQuit) {
  UserInput ui;
  std::istringstream in("8");
  EXPECT_EQ(ui.getMoveType(in), BingoTypes::QUIT_GAME);
}
 
TEST(TestUserInput, getMoveTypeInvalidThrows) {
  UserInput ui;
  std::istringstream in("99");
  EXPECT_THROW(ui.getMoveType(in), bad_input);
}
 
TEST(TestUserInput, getSquarePositionValid) {
  UserInput ui;
  std::istringstream in("3 4");
  BingoTypes::squarePos pos = ui.getSquarePosition(in);
  EXPECT_EQ(pos.row, 3u);
  EXPECT_EQ(pos.col, 4u);
}
 
TEST(TestUserInput, getSquarePositionInvalidThrows) {
  UserInput ui;
  std::istringstream in("abc");
  EXPECT_THROW(ui.getSquarePosition(in), bad_input);
}
 
TEST(TestUserInput, getPlayerIdValidString) {
  UserInput ui;
  std::istringstream in("alice");
  EXPECT_EQ(ui.getPlayerId(in), "alice");
}
 
TEST(TestUserInput, getPlayerIdEmptyThrows) {
  UserInput ui;
  std::istringstream in("");
  EXPECT_THROW(ui.getPlayerId(in), invalid_identifier);
}