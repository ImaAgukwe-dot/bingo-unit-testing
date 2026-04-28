/**
 * @author Student
 * @date 2026-01
 */
#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "BingoGame.h"
#include "BingoCaller.h"
#include "BingoCard.h"
#include "BingoCardFactory.h"
#include "VictoryCondition.h"
#include "BingoTypes.h"
#include "Exceptions.h"

static BingoCard* makeCard75() {
  BingoCardFactory factory;
  VictoryCondition* vc = new HorizontalLine();
  BingoCard* card = factory.makeBingoCard(BingoTypes::BINGO75, vc);
  delete vc;
  return card;
}

TEST(TestBingoGame, defaultConstructorNumPlayersIsZero) {
  BingoGame game;
  EXPECT_EQ(game.getNumPlayers(), 0u);
}

TEST(TestBingoGame, getGameTypeThrowsWhenCallerNotSet) {
  BingoGame game;
  EXPECT_THROW(game.getGameType(), incomplete_settings);
}

TEST(TestBingoGame, getVictoryTypeThrowsWhenCallerNotSet) {
  BingoGame game;
  EXPECT_THROW(game.getVictoryType(), incomplete_settings);
}

TEST(TestBingoGame, setCallerThrowsOnNullptr) {
  BingoGame game;
  EXPECT_THROW(game.setCaller(nullptr), bad_input);
}

TEST(TestBingoGame, setCallerSetsGameType) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  EXPECT_EQ(game.getGameType(), BingoTypes::BINGO75);
}

TEST(TestBingoGame, setCallerSetsVictoryType) {
  BingoGame game;
  game.setCaller(new Bingo75Caller(BingoTypes::BLACKOUT));
  EXPECT_EQ(game.getVictoryType(), BingoTypes::BLACKOUT);
}

TEST(TestBingoGame, joinGameAddsPlayer) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  BingoCard* card = makeCard75();
  EXPECT_TRUE(game.joinGame("alice", card));
  EXPECT_EQ(game.getNumPlayers(), 1u);
}

TEST(TestBingoGame, joinGameThrowsOnBlankId) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  BingoCard* card = makeCard75();
  EXPECT_THROW(game.joinGame("", card), invalid_identifier);
  delete card;
}

TEST(TestBingoGame, joinGameThrowsOnCardMismatch) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  BingoCardFactory factory;
  VictoryCondition* vc = new HorizontalLine();
  BingoCard* card = factory.makeBingoCard(BingoTypes::BINGO50, vc);
  delete vc;
  EXPECT_THROW(game.joinGame("bob", card), card_to_game_mismatch);
  delete card;
}

TEST(TestBingoGame, leaveGameRemovesPlayer) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  game.joinGame("alice", makeCard75());
  EXPECT_TRUE(game.leaveGame("alice"));
  EXPECT_EQ(game.getNumPlayers(), 0u);
}

TEST(TestBingoGame, leaveGameReturnsFalseForUnknownId) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  EXPECT_FALSE(game.leaveGame("nobody"));
}

TEST(TestBingoGame, resetVictoryTypeThrowsWhenCallerNotSet) {
  BingoGame game;
  EXPECT_THROW(game.resetVictoryType(BingoTypes::BLACKOUT),
               incomplete_settings);
}

TEST(TestBingoGame, resetVictoryTypeChangesType) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  game.resetVictoryType(BingoTypes::VERTICAL_LINE);
  EXPECT_EQ(game.getVictoryType(), BingoTypes::VERTICAL_LINE);
}

TEST(TestBingoGame, completeNextCallThrowsWhenCallerNotSet) {
  BingoGame game;
  std::ostringstream out;
  EXPECT_THROW(game.completeNextCall(out), incomplete_settings);
}

TEST(TestBingoGame, completeNextCallThrowsWhenNoPlayers) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  std::ostringstream out;
  EXPECT_THROW(game.completeNextCall(out), invalid_size);
}

TEST(TestBingoGame, completeNextCallSucceedsWithPlayer) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  game.joinGame("alice", makeCard75());
  std::ostringstream out;
  EXPECT_NO_THROW(game.completeNextCall(out));
}

TEST(TestBingoGame, resetGameThrowsWhenCallerNotSet) {
  BingoGame game;
  EXPECT_THROW(game.resetGame(), incomplete_settings);
}

TEST(TestBingoGame, resetGameClearsPlayers) {
  BingoGame game;
  game.setCaller(new Bingo75Caller());
  game.joinGame("alice", makeCard75());
  game.resetGame();
  EXPECT_EQ(game.getNumPlayers(), 0u);
}