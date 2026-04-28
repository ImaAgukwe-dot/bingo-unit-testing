#include <sstream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "ScreenDisplay.h"
#include "BingoCard.h"
#include "BingoCaller.h"
#include "BingoCardFactory.h"
#include "VictoryCondition.h"
#include "Square.h"
#include "BingoTypes.h"
#include "Exceptions.h"


static BingoCard* makeCard() {
  BingoCardFactory factory;
  VictoryCondition* vc = new HorizontalLine();
  BingoCard* card = factory.makeBingoCard(BingoTypes::BINGO75, vc);
  delete vc;
  return card;
}

TEST(TestScreenDisplay, displayCallerMessageOutputsMessage) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayCallerMessage(out, "B:05");
  EXPECT_FALSE(out.str().empty());
  EXPECT_NE(out.str().find("B:05"), std::string::npos);
}

TEST(TestScreenDisplay, displayGameTypeBingo75OutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayGameType(out, BingoTypes::BINGO75);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayGameTypeBingo50OutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayGameType(out, BingoTypes::BINGO50);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayVictoryTypeHorizontalOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayVictoryType(out, BingoTypes::HORIZONTAL_LINE);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayVictoryTypeBlackoutOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayVictoryType(out, BingoTypes::BLACKOUT);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayVictoryDescriptionOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayVictoryDescription(out, BingoTypes::VERTICAL_LINE);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayGameTypePromptOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayGameTypePrompt(out);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayVictoryTypePromptOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayVictoryTypePrompt(out);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayMoveTypeDaubOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayMoveType(out, BingoTypes::DAUB);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayMoveTypePromptOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displayMoveTypePrompt(out);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displaySquarePositionPromptOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  sd.displaySquarePositionPrompt(out);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayBingoCardOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  BingoCard* card = makeCard();
  sd.displayBingoCard(out, card);
  EXPECT_FALSE(out.str().empty());
  delete card;
}

TEST(TestScreenDisplay, displayValidityOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  BingoCard* card = makeCard();
  sd.displayValidity(out, card);
  EXPECT_FALSE(out.str().empty());
  delete card;
}

TEST(TestScreenDisplay, displayGameInfoOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  Bingo75Caller caller;
  sd.displayGameInfo(out, &caller);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayGameInfoThrowsOnNullCaller) {
  ScreenDisplay sd;
  std::ostringstream out;
  EXPECT_THROW(sd.displayGameInfo(out, nullptr), bad_input);
}

TEST(TestScreenDisplay, displayGameBoardOutputsContent) {
  ScreenDisplay sd;
  std::ostringstream out;
  Bingo75Caller caller;
  caller.pullBall();
  sd.displayGameBoard(out, &caller);
  EXPECT_FALSE(out.str().empty());
}

TEST(TestScreenDisplay, displayGameBoardThrowsOnNullCaller) {
  ScreenDisplay sd;
  std::ostringstream out;
  EXPECT_THROW(sd.displayGameBoard(out, nullptr), bad_input);
}

TEST(TestScreenDisplay, displayGameInstructionsThrowsOnBadFile) {
  ScreenDisplay sd;
  std::ostringstream out;
  EXPECT_THROW(sd.displayGameInstructions(out, "nofile.txt", "tag"),
               bad_input);
}