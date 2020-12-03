#include "AdventOfCode.2020.Day3/toboggan_trajectory_part_2.h"

#include <numeric>

namespace AdventOfCode2020::Day3::Part2
{
  Slope::Slope(const int Right, const int Down)
    : right(Right), down(Down) {}

  bool Slope::IsRowOnSlope(const int row) const {
    return row % this->down == 0;
  }

  bool Slope::IsTreeInPath(const std::vector<std::string>& data_set, const int row) const {
    return data_set[row][this->right_delta % data_set[row].size()] == '#';
  }

  std::int64_t AccumulateSlopeTrees(const std::vector<Slope>& slopes) {
    return std::accumulate(slopes.begin(), slopes.end(), static_cast<std::int64_t>(1), [](const std::int64_t accumulated, const Slope& slope) -> std::int64_t {
      return accumulated * slope.trees;
    });
  }

  std::int64_t Solve(const std::vector<std::string>& data_set, std::vector<Slope> slopes) {
    for (auto i = 0; i < data_set.size(); i++) {
      for (auto& slope : slopes) {
        if (slope.IsRowOnSlope(i)) {
          if (slope.IsTreeInPath(data_set, i)) {
            slope.trees++;
          }
          slope.right_delta += slope.right;
        }
      }
    }

    return AccumulateSlopeTrees(slopes);
  }
}
