#include "AdventOfCode.2020.Day5/binary_boarding_part_1.h"

#include <algorithm>

namespace AdventOfCode2020::Day5::Part1
{
  struct BoardingPass {
    BoardingPass(const std::string_view BoardingPassId);

    std::string boarding_pass_id = {};
    int seat_id = {};
  };

  BoardingPass::BoardingPass(const std::string_view BoardingPassId)
    : boarding_pass_id(BoardingPassId) {}

  std::vector<BoardingPass> ParseBoardingPasses(const std::vector<std::string>& data_set) {
    std::vector<BoardingPass> boarding_passes = {};
    for (const auto& line : data_set) {
      BoardingPass boarding_pass{ line };
      for (const auto& direction : line) {
        boarding_pass.seat_id *= 2;
        if (direction == 'B' || direction == 'R') {
          boarding_pass.seat_id++;
        }
      }
      boarding_passes.push_back(boarding_pass);
    }
    return boarding_passes;
  }

  void SortBoardingPassesBySeatIdAscending(std::vector<BoardingPass>& boarding_passes) {
    std::sort(boarding_passes.begin(), boarding_passes.end(), [](const BoardingPass& left, const BoardingPass& right) -> bool {
      return left.seat_id < right.seat_id;
    });
  }

  int Solve(const std::vector<std::string>& data_set) {
    auto boarding_passes = ParseBoardingPasses(data_set);
    SortBoardingPassesBySeatIdAscending(boarding_passes);
    return boarding_passes[boarding_passes.size() - 1].seat_id;
  }
}
