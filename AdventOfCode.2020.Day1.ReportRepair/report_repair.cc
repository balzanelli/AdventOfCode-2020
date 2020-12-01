#include <iostream>

#include "AdventOfCode.2020.Common/file.h"
#include "AdventOfCode.2020.Day1.ReportRepair/report_repair_part_1_brute_force.h"
#include "AdventOfCode.2020.Day1.ReportRepair/report_repair_part_1_optimal.h"
#include "AdventOfCode.2020.Day1.ReportRepair/report_repair_part_2_brute_force.h"
#include "AdventOfCode.2020.Day1.ReportRepair/report_repair_part_2_optimal.h"

using namespace AdventOfCode2020::Day1::ReportRepair;

constexpr int kSumTarget = 2020;

void SolveProblem1(const std::vector<int>& data_set) {
  std::cout << "Problem 1 (Brute Force): " <<
    Part1::BruteForce::Solve(data_set, kSumTarget) << std::endl;

  std::cout << "Problem 1 (Optimal): " <<
    Part1::Optimal::Solve(data_set, kSumTarget) << std::endl;
}

void SolveProblem2(const std::vector<int>& data_set) {
  std::cout << "Problem 2 (Brute Force): " <<
    Part2::BruteForce::Solve(data_set, kSumTarget) << std::endl;

  std::cout << "Problem 2 (Optimal): " <<
    Part2::Optimal::Solve(data_set, kSumTarget) << std::endl;
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cout << "File Must Be Specified" << std::endl;
    return -1;
  }

  const auto data_set = AdventOfCode2020::Common::File::ReadAsNumbers(argv[1]);

  if (data_set.empty()) {
    std::cout << "Data Set is Empty: " << argv[0] << std::endl;
    return -1;
  }

  SolveProblem1(data_set);
  SolveProblem2(data_set);

  return 0;
}
