#include <iostream>

#include "AdventOfCode.2020.Common/file.h"
#include "AdventOfCode.2020.Day4/passport_processing_part_1.h"
#include "AdventOfCode.2020.Day4/passport_processing_part_2.h"

using namespace AdventOfCode2020::Day4;

void SolveProblem1(const std::string_view file_path) {
  std::cout << "Problem 1: " <<
    Part1::Solve(file_path) << std::endl;
}

void SolveProblem2(const std::string_view file_path) {
  std::cout << "Problem 2: " <<
    Part2::Solve(file_path) << std::endl;
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cout << "File Must Be Specified" << std::endl;
    return -1;
  }

  const std::string file_path = argv[1];

  if (file_path.empty()) {
    std::cout << "File Must Be Specified" << std::endl;
    return -1;
  }

  SolveProblem1(file_path);
  SolveProblem2(file_path);

  return 0;
}
