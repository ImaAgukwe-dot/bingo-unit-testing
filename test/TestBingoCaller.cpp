#include <string>
#include "gtest/gtest.h"
#include "BingoCaller.h"
#include "BingoTypes.h"
#include "Exceptions.h"

TEST(TestBingo75Caller, defaultConstructorVictoryType) {
  Bingo75Caller caller;
  EXPECT_EQ(caller.getVictoryType(), BingoTypes::HORIZONTAL_LINE);
}
 
TEST(TestBingo75Caller, constructorWithVictoryType) {
  Bingo75Caller caller(BingoTypes::BLACKOUT);
  EXPECT_EQ(caller.getVictoryType(), BingoTypes::BLACKOUT);
}
 
TEST(TestBingo75Caller, getGameType) {
  Bingo75Caller caller;
  EXPECT_EQ(caller.getGameType(), BingoTypes::BINGO75);
}
 
TEST(TestBingo75Caller, getNumBalls) {
  Bingo75Caller caller;
  EXPECT_EQ(caller.getNumBalls(), 75u);
}
 
TEST(TestBingo75Caller, initialNumBallsPulledIsZero) {
  Bingo75Caller caller;
  EXPECT_EQ(caller.getNumBallsPulled(), 0u);
}
 
TEST(TestBingo75Caller, initialNumBallsInCageIs75) {
  Bingo75Caller caller;
  EXPECT_EQ(caller.getNumBallsInCage(), 75u);
}

TEST(TestBingo75Caller, pullBallReducesCage) {
  Bingo75Caller caller;
  caller.pullBall();
  EXPECT_EQ(caller.getNumBallsInCage(), 74u);
  EXPECT_EQ(caller.getNumBallsPulled(), 1u);
}
 
TEST(TestBingo75Caller, pullAllBallsReturnsFalseWhenEmpty) {
  Bingo75Caller caller;
  for (unsigned i = 0; i < 75; ++i) {
    caller.pullBall();
  }
  EXPECT_FALSE(caller.pullBall());
  EXPECT_EQ(caller.getNumBallsInCage(), 0u);
}
 
TEST(TestBingo75Caller, getCurrentNumberAfterPull) {
  Bingo75Caller caller;
  caller.pullBall();
  unsigned num = caller.getCurrentNumber();
  EXPECT_GE(num, 1u);
  EXPECT_LE(num, 75u);
}
 
TEST(TestBingo75Caller, getCurrentNumberThrowsWhenNoBallsPulled) {
  Bingo75Caller caller;
  EXPECT_THROW(caller.getCurrentNumber(), invalid_size);
}
 
TEST(TestBingo75Caller, getAnnouncementThrowsWhenNoBallsPulled) {
  Bingo75Caller caller;
  EXPECT_THROW(caller.getAnnouncement(), invalid_size);
}
 
TEST(TestBingo75Caller, getAnnouncementAfterPull) {
  Bingo75Caller caller;
  caller.pullBall();
  EXPECT_NO_THROW(caller.getAnnouncement());
  EXPECT_FALSE(caller.getAnnouncement().empty());
}
 
TEST(TestBingo75Caller, wasNumberCalledAfterPull) {
  Bingo75Caller caller;
  caller.pullBall();
  unsigned num = caller.getCurrentNumber();
  EXPECT_TRUE(caller.wasNumberCalled(num));
}
 
TEST(TestBingo75Caller, wasNumberCalledReturnsFalseBeforePull) {
  Bingo75Caller caller;
  EXPECT_FALSE(caller.wasNumberCalled(1));
}
 
TEST(TestBingo75Caller, wasNumberCalledThrowsOnInvalidNumber) {
  Bingo75Caller caller;
  EXPECT_THROW(caller.wasNumberCalled(0), bad_input);
  EXPECT_THROW(caller.wasNumberCalled(76), bad_input);
}
 
TEST(TestBingo75Caller, resetGameRestoresCage) {
  Bingo75Caller caller;
  caller.pullBall();
  caller.pullBall();
  caller.resetGame();
  EXPECT_EQ(caller.getNumBallsInCage(), 75u);
  EXPECT_EQ(caller.getNumBallsPulled(), 0u);
}
 
TEST(TestBingo75Caller, setVictoryTypeChangesType) {
  Bingo75Caller caller;
  caller.setVictoryType(BingoTypes::VERTICAL_LINE);
  EXPECT_EQ(caller.getVictoryType(), BingoTypes::VERTICAL_LINE);
}
 
TEST(TestBingo75Caller, setVictoryTypeThrowsWhenGameInProgress) {
  Bingo75Caller caller;
  caller.pullBall();
  EXPECT_THROW(caller.setVictoryType(BingoTypes::BLACKOUT),
               function_unavailable);
}
 
TEST(TestBingo75Caller, listPulledBallsThrowsWhenNonePulled) {
  Bingo75Caller caller;
  EXPECT_THROW(caller.listPulledBalls(), invalid_size);
}
 
TEST(TestBingo75Caller, listPulledBallsAfterPull) {
  Bingo75Caller caller;
  caller.pullBall();
  EXPECT_NO_THROW(caller.listPulledBalls());
  EXPECT_FALSE(caller.listPulledBalls().empty());
}
 
TEST(TestBingo75Caller, listUnpulledBallsInitiallyNotEmpty) {
  Bingo75Caller caller;
  EXPECT_NO_THROW(caller.listUnpulledBalls());
  EXPECT_FALSE(caller.listUnpulledBalls().empty());
}
 
// Bingo50Caller Tests
 
TEST(TestBingo50Caller, defaultConstructorVictoryType) {
  Bingo50Caller caller;
  EXPECT_EQ(caller.getVictoryType(), BingoTypes::HORIZONTAL_LINE);
}
 
TEST(TestBingo50Caller, getGameType) {
  Bingo50Caller caller;
  EXPECT_EQ(caller.getGameType(), BingoTypes::BINGO50);
}
 
TEST(TestBingo50Caller, getNumBalls) {
  Bingo50Caller caller;
  EXPECT_EQ(caller.getNumBalls(), 50u);
}
 
TEST(TestBingo50Caller, initialNumBallsInCageIs50) {
  Bingo50Caller caller;
  EXPECT_EQ(caller.getNumBallsInCage(), 50u);
}
 
TEST(TestBingo50Caller, getAnnouncementAfterPull) {
  Bingo50Caller caller;
  caller.pullBall();
  EXPECT_NO_THROW(caller.getAnnouncement());
  EXPECT_FALSE(caller.getAnnouncement().empty());
}
 
TEST(TestBingo50Caller, getAnnouncementThrowsWhenNoBallsPulled) {
  Bingo50Caller caller;
  EXPECT_THROW(caller.getAnnouncement(), invalid_size);
}
 
TEST(TestBingo50Caller, readCluesThrowsOnBadFile) {
  Bingo50Caller caller;
  EXPECT_THROW(caller.readClues("nonexistent_file.csv"), bad_input);
}