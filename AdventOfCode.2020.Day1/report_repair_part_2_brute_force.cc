#include "AdventOfCode.2020.Day1/report_repair_part_2_brute_force.h"

namespace AdventOfCode2020::Day1::Part2::BruteForce
{
  int Solve(const std::vector<int>& data_set, const int sum) {
    for (std::size_t i = 0; i < data_set.size() - 2; i++) {
      for (std::size_t j = i + 1; j < data_set.size() - 1; j++) {
        for (std::size_t x = j + 1; x < data_set.size(); x++) {
          if (data_set[i] + data_set[j] + data_set[x] == sum) {
            return data_set[i] * data_set[j] * data_set[x];
          }
        }
      }
    }

    return -1;
  }
}
