#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "BingoTypes.h"
#include "VictoryCondition.h"
#include "Square.h"

// Helper: build a 25-square grid (all IntSquares, no free square)
static std::vector<Square*> makeGrid() {
  std::vector<Square*> grid;
  for (unsigned i = 1; i <= 25; ++i) {
    grid.push_back(new IntSquare(i));
  }
  return grid;
}
 
static void deleteGrid(std::vector<Square*>& grid) {
  for (auto s : grid) delete s;
  grid.clear();
}
 
// Daub squares at given 0-based indices
static void daubIndices(std::vector<Square*>& grid,
                        std::vector<unsigned> indices) {
  for (unsigned idx : indices) {
    grid[idx]->daubSquare(grid[idx]->getValue());
  }
}

TEST(TestHorizontalLine, constructionTest) {
  VictoryCondition* vc = new HorizontalLine();
  EXPECT_EQ(vc->getVictoryType(), BingoTypes::HORIZONTAL_LINE);
  std::string desc = "Daub five squares in a horizontal line.";
  EXPECT_EQ(vc->getDescription(), desc);
  delete vc;
}

TEST(TestHorizontalLine, hasWonFalseWhenNoDaubs) {
  HorizontalLine hl;
  std::vector<Square*> grid = makeGrid();
  EXPECT_FALSE(hl.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestHorizontalLine, hasWonTrueFirstRow) {
  HorizontalLine hl;
  std::vector<Square*> grid = makeGrid();
  // Row 1: indices 0,1,2,3,4
  daubIndices(grid, {0, 1, 2, 3, 4});
  EXPECT_TRUE(hl.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestHorizontalLine, hasWonTrueLastRow) {
  HorizontalLine hl;
  std::vector<Square*> grid = makeGrid();
  // Row 5: indices 20,21,22,23,24
  daubIndices(grid, {20, 21, 22, 23, 24});
  EXPECT_TRUE(hl.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestHorizontalLine, hasWonFalsePartialRow) {
  HorizontalLine hl;
  std::vector<Square*> grid = makeGrid();
  // Only 4 of 5 in row 1
  daubIndices(grid, {0, 1, 2, 3});
  EXPECT_FALSE(hl.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestHorizontalLine, hasWonFalseVerticalDaubs) {
  HorizontalLine hl;
  std::vector<Square*> grid = makeGrid();
  // Column 1: indices 0,5,10,15,20
  daubIndices(grid, {0, 5, 10, 15, 20});
  EXPECT_FALSE(hl.hasWon(grid));
  deleteGrid(grid);
}

// AnyLine construction test
TEST(TestAnyLine, constructionTest) {
  VictoryCondition* vc = new AnyLine();
  EXPECT_EQ(vc->getVictoryType(), BingoTypes::ANY_LINE);
  std::string desc =
    "Daub five squares in a horizontal, vertical, or diagonal line.";
  EXPECT_EQ(vc->getDescription(), desc);
  delete vc;
}

TEST(TestAnyLine, hasWonFalseWhenNoDaubs) {
  AnyLine al;
  std::vector<Square*> grid = makeGrid();
  EXPECT_FALSE(al.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestAnyLine, hasWonTrueHorizontalLine) {
  AnyLine al;
  std::vector<Square*> grid = makeGrid();
  daubIndices(grid, {0, 1, 2, 3, 4});
  EXPECT_TRUE(al.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestAnyLine, hasWonTrueVerticalLine) {
  AnyLine al;
  std::vector<Square*> grid = makeGrid();
  // Column 1: indices 0,5,10,15,20
  daubIndices(grid, {0, 5, 10, 15, 20});
  EXPECT_TRUE(al.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestAnyLine, hasWonTrueDiagonalTopLeftToBottomRight) {
  AnyLine al;
  std::vector<Square*> grid = makeGrid();
  // Main diagonal: indices 0,6,12,18,24
  daubIndices(grid, {0, 6, 12, 18, 24});
  EXPECT_TRUE(al.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestAnyLine, hasWonTrueDiagonalTopRightToBottomLeft) {
  AnyLine al;
  std::vector<Square*> grid = makeGrid();
  // Anti-diagonal: indices 4,8,12,16,20
  daubIndices(grid, {4, 8, 12, 16, 20});
  EXPECT_TRUE(al.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestAnyLine, hasWonFalsePartialLine) {
  AnyLine al;
  std::vector<Square*> grid = makeGrid();
  daubIndices(grid, {0, 1, 2, 3});
  EXPECT_FALSE(al.hasWon(grid));
  deleteGrid(grid);
}

TEST(TestBlackout, constructionTest) {
  VictoryCondition* vc = new Blackout();
  EXPECT_EQ(vc->getVictoryType(), BingoTypes::BLACKOUT);
  std::string desc = "Daub all squares on the card.";
  EXPECT_EQ(vc->getDescription(), desc);
  delete vc;
}

TEST(TestBlackout, hasWonFalseWhenNoDaubs) {
  Blackout bo;
  std::vector<Square*> grid = makeGrid();
  EXPECT_FALSE(bo.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestBlackout, hasWonFalseWhenPartialDaubs) {
  Blackout bo;
  std::vector<Square*> grid = makeGrid();
  for (unsigned i = 0; i < 24; ++i) {
    grid[i]->daubSquare(grid[i]->getValue());
  }
  EXPECT_FALSE(bo.hasWon(grid));
  deleteGrid(grid);
}
 
TEST(TestBlackout, hasWonTrueWhenAllDaubed) {
  Blackout bo;
  std::vector<Square*> grid = makeGrid();
  for (auto s : grid) {
    s->daubSquare(s->getValue());
  }
  EXPECT_TRUE(bo.hasWon(grid));
  deleteGrid(grid);
}