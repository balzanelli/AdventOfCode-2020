#include <gtest/gtest.h>

#include "AdventOfCode.2020.Day1/report_repair_part_1_brute_force.h"

namespace AdventOfCode2020::Day1::Part1::BruteForce
{
  TEST(AdventOfCode2020_Day1_Part1_BruteForce_Solve, Found_Multiply) {
    // Arrange

    const std::vector<int> data_set = {
      1, 4, 11, 13, 20
    };

    // Act

    const auto result = Solve(data_set, 15);

    // Assert

    EXPECT_EQ(result, 44);
  }

  TEST(AdventOfCode2020_Day1_Part1_BruteForce_Solve, NotFound_Error) {
    // Arrange

    const std::vector<int> data_set = {
      1, 4, 11, 13, 20
    };

    // Act

    const auto result = Solve(data_set, 0);

    // Assert

    EXPECT_EQ(result, -1);
  }
}
