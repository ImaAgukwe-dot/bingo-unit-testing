/**
* @author L. Nicole Wilson [n.wilson@uleth.ca]
* @date 2023-09
*/
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "BingoTypes.h"
#include "VictoryCondition.h"
#include "Square.h"

TEST(TestVerticalLine, constructionTest) {
  VictoryCondition* victory = new VerticalLine();

  std::string expectedDesc = "Daub five squares in a vertical line.";

  EXPECT_EQ(victory->getDescription(), expectedDesc);
  EXPECT_EQ(victory->getVictoryType(), BingoTypes::VERTICAL_LINE);

  delete victory;
}

