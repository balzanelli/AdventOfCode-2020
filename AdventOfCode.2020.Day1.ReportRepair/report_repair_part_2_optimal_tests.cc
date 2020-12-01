#include <gtest/gtest.h>

#include "AdventOfCode.2020.Day1.ReportRepair/report_repair_part_2_optimal.h"

namespace AdventOfCode2020::Day1::ReportRepair::Part2::Optimal
{
  TEST(AdventOfCode2020_Day1_ReportRepair_Part2_Optimal_Solve, Found_Multiply) {
    // Arrange

    const std::vector<int> data_set = {
      1, 4, 11, 13, 20
    };

    // Act

    const auto result = Solve(data_set, 28);

    // Assert

    EXPECT_EQ(result, 572);
  }

  TEST(AdventOfCode2020_Day1_ReportRepair_Part2_Optimal_Solve, NotFound_Error) {
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
