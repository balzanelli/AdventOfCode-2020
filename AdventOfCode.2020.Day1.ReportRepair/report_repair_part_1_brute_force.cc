#include "AdventOfCode.2020.Day1.ReportRepair/report_repair_part_1_brute_force.h"

namespace AdventOfCode2020::Day1::ReportRepair::Part1::BruteForce
{
  int Solve(const std::vector<int>& data_set, const int sum) {
    for (std::size_t i = 0; i < data_set.size(); i++) {
      for (std::size_t j = i + 1; j < data_set.size() - 1; j++) {
        if (data_set[i] + data_set[j] == sum) {
          return data_set[i] * data_set[j];
        }
      }
    }

    return -1;
  }
}
