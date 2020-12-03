#include "AdventOfCode.2020.Day3/toboggan_trajectory_part_1.h"

namespace AdventOfCode2020::Day3::Part1
{
  int Solve(const std::vector<std::string>& data_set, const int right, const int down) {
    int trees = 0;
    int right_delta = 0;

    for (auto i = 0; i < data_set.size(); i++) {
      if (i % down == 0) {
        if (data_set[i][right_delta % data_set[i].size()] == '#') {
          trees++;
        }
        right_delta += right;
      }
    }

    return trees;
  }
}
