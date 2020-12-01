#include "AdventOfCode.2020.Day1.ReportRepair/report_repair_part_2_optimal.h"

#include <optional>
#include <unordered_set>

namespace AdventOfCode2020::Day1::ReportRepair::Part2::Optimal
{
  struct Triplet {
    Triplet(int X, int Y, int Z);

    int x;
    int y;
    int z;
  };

  Triplet::Triplet(const int X, const int Y, const int Z)
    : x(X), y(Y), z(Z) {}

  std::optional<Triplet> FindTripletThatSumTo(const std::vector<int>& data_set, const int sum) {
    for (std::size_t i = 0; i < data_set.size() - 2; i++) {
      std::unordered_set<int> hash_set = {};

      for (std::size_t j = i + 1; j < data_set.size(); j++) {
        const auto value = sum - data_set[i] - data_set[j];

        if (hash_set.find(value) == hash_set.end()) {
          hash_set.insert(data_set[j]);
        } else {
          return Triplet{
            data_set[i],
            data_set[j],
            value
          };
        }
      }
    }

    return {};
  }

  int Solve(const std::vector<int>& data_set, const int sum) {
    const auto triplet = FindTripletThatSumTo(data_set, sum);

    return triplet != std::nullopt ? triplet->x * triplet->y * triplet->z : -1;
  }
}
