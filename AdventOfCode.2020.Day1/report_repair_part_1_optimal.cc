#include "AdventOfCode.2020.Day1/report_repair_part_1_optimal.h"

#include <optional>
#include <unordered_set>

namespace AdventOfCode2020::Day1::Part1::Optimal
{
  struct Pair {
    Pair(int X, int Y);

    int x;
    int y;
  };

  Pair::Pair(const int X, const int Y)
    : x(X), y(Y) {}

  std::optional<Pair> FindPairThatSumTo(const std::vector<int>& data_set, const int sum) {
    std::unordered_set<int> hash_set = {};

    for (const auto value : data_set) {
      const auto hash_set_value = hash_set.find(sum - value);

      if (hash_set_value == hash_set.end()) {
        hash_set.insert(value);
      } else {
        return Pair{
          *hash_set_value,
          value
        };
      }
    }

    return {};
  }

  int Solve(const std::vector<int>& data_set, const int sum) {
    const auto pair = FindPairThatSumTo(data_set, sum);

    return pair != std::nullopt ? pair->x * pair->y : -1;
  }
}
