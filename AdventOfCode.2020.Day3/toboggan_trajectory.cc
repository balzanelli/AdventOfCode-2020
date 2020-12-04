#include <iostream>

#include "AdventOfCode.2020.Common/file.h"
#include "AdventOfCode.2020.Day3/toboggan_trajectory_part_1.h"
#include "AdventOfCode.2020.Day3/toboggan_trajectory_part_2.h"

using namespace AdventOfCode2020::Day3;

constexpr int kRightDelta = 3;
constexpr int kDownDelta = 1;

void SolveProblem1(const std::vector<std::string>& data_set) {
  std::cout << "Problem 1: " <<
    Part1::Solve(data_set, kRightDelta, kDownDelta) << std::endl;
}

void SolveProblem2(const std::vector<std::string>& data_set) {
  std::cout << "Problem 2: " <<
            Part2::Solve(data_set, {
              {1, 1},
              {3, 1},
              {5, 1},
              {7, 1},
              {1, 2}
            }) << std::endl;
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cout << "File Must Be Specified" << std::endl;
    return -1;
  }

  const auto data_set = AdventOfCode2020::Common::File::ReadAsStrings(argv[1]);

  if (data_set.empty()) {
    std::cout << "Data Set is Empty: " << argv[0] << std::endl;
    return -1;
  }

  SolveProblem1(data_set);
  SolveProblem2(data_set);

  return 0;
}
