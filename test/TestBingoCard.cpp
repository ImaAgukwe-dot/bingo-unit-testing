/**
 * @author L. Nicole Wilson [n.wilson@uleth.ca], J. Anvik [john.anvik@uleth.ca]
 * @date 2023-09
 */
#include <string>
#include <vector>

#include "BingoCard.h"
#include "BingoTypes.h"
#include "Square.h"
#include "VictoryCondition.h"
#include "Exceptions.h"
#include "gtest/gtest.h"

TEST(TestBingoCard, defaultConstructorTest) {
  BingoCard bc;

  BingoTypes::squarePos pos;
  pos.row = 1;
  pos.col = 1;
  EXPECT_EQ(bc.getGameType(), BingoTypes::BINGO75);
  EXPECT_THROW(bc.typesMatch(BingoTypes::BINGO75, BingoTypes::BLACKOUT),
               incomplete_settings);
  EXPECT_THROW(bc.daubSquare(10, pos), incomplete_settings);
  EXPECT_THROW(bc.isCorrect(), incomplete_settings);
  EXPECT_THROW(bc.isVictorious(), incomplete_settings);
  EXPECT_THROW(bc.getVictoryType(), incomplete_settings);
}

TEST(TestBingoCard, oneParamConstructorTest) {
  BingoCard bc(BingoTypes::BINGO50);

  BingoTypes::squarePos pos;
  pos.row = 1;
  pos.col = 1;

  EXPECT_EQ(bc.getGameType(), BingoTypes::BINGO50);
  EXPECT_THROW(bc.typesMatch(BingoTypes::BINGO50, BingoTypes::BLACKOUT),
               incomplete_settings);
  EXPECT_THROW(bc.daubSquare(10, pos), incomplete_settings);
  EXPECT_THROW(bc.isCorrect(), incomplete_settings);
  EXPECT_THROW(bc.isVictorious(), incomplete_settings);
  EXPECT_THROW(bc.getVictoryType(), incomplete_settings);
}

