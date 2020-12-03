#pragma once

#include <string>
#include <vector>

namespace AdventOfCode2020::Day3::Part2
{
  struct Slope {
    Slope(int Right, int Down);

    int right;
    int down;
    int right_delta = {};
    int trees = {};

    [[nodiscard]] bool IsRowOnSlope(int row) const;
    [[nodiscard]] bool IsTreeInPath(const std::vector<std::string>& data_set, int row) const;
  };

  std::int64_t Solve(const std::vector<std::string>& data_set, std::vector<Slope> slopes);
}
