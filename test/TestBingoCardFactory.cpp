#include "gtest/gtest.h"
#include "BingoCardFactory.h"
#include "BingoCard.h"
#include "BingoTypes.h"
#include "VictoryCondition.h"
#include "Exceptions.h"

TEST(TestBingoCardFactory, makeBingoCard75WithHorizontalLine) {
  BingoCardFactory factory;
  VictoryCondition* vc = new HorizontalLine();
  BingoCard* card = factory.makeBingoCard(BingoTypes::BINGO75, vc);
  EXPECT_NE(card, nullptr);
  EXPECT_EQ(card->getGameType(), BingoTypes::BINGO75);
  delete vc;
  delete card;
}

TEST(TestBingoCardFactory, makeBingoCard50WithVerticalLine) {
  BingoCardFactory factory;
  VictoryCondition* vc = new VerticalLine();
  BingoCard* card = factory.makeBingoCard(BingoTypes::BINGO50, vc);
  EXPECT_NE(card, nullptr);
  EXPECT_EQ(card->getGameType(), BingoTypes::BINGO50);
  delete vc;
  delete card;
}

TEST(TestBingoCardFactory, makeBingoCard75WithBlackout) {
  BingoCardFactory factory;
  VictoryCondition* vc = new Blackout();
  BingoCard* card = factory.makeBingoCard(BingoTypes::BINGO75, vc);
  EXPECT_NE(card, nullptr);
  EXPECT_EQ(card->getVictoryType(), BingoTypes::BLACKOUT);
  delete vc;
  delete card;
}

TEST(TestBingoCardFactory, makeBingoCardThrowsOnNullVictory) {
  BingoCardFactory factory;
  EXPECT_THROW(factory.makeBingoCard(BingoTypes::BINGO75, nullptr),
               incomplete_settings);
}

TEST(TestBingoCardFactory, makeBingoCardVictoryTypeMatches) {
  BingoCardFactory factory;
  VictoryCondition* vc = new AnyLine();
  BingoCard* card = factory.makeBingoCard(BingoTypes::BINGO75, vc);
  EXPECT_EQ(card->getVictoryType(), BingoTypes::ANY_LINE);
  delete vc;
  delete card;
}

TEST(TestBingoCardFactory, makeBingoCardIndependentOfOriginalVictory) {
  BingoCardFactory factory;
  VictoryCondition* vc = new HorizontalLine();
  BingoCard* card = factory.makeBingoCard(BingoTypes::BINGO75, vc);
  // Delete original vc — card should still work since it copies it
  delete vc;
  EXPECT_EQ(card->getVictoryType(), BingoTypes::HORIZONTAL_LINE);
  delete card;
}