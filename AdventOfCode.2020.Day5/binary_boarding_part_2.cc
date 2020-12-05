#include "AdventOfCode.2020.Day5/binary_boarding_part_2.h"

#include <algorithm>

namespace AdventOfCode2020::Day5::Part2
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

  int GetFirstAvailableSeat(const std::vector<BoardingPass>& boarding_passes) {
    for (int i = 0; i < boarding_passes.size(); i++) {
      if (boarding_passes[i + 1].seat_id - boarding_passes[i].seat_id == 2) {
        return boarding_passes[i].seat_id + 1;
      }
    }
    return -1;
  }

  int Solve(const std::vector<std::string>& data_set) {
    auto boarding_passes = ParseBoardingPasses(data_set);
    SortBoardingPassesBySeatIdAscending(boarding_passes);
    return GetFirstAvailableSeat(boarding_passes);
  }
}
