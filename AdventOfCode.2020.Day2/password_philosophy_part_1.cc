#include "AdventOfCode.2020.Day2/password_philosophy_part_1.h"

#include <optional>
#include <regex>

namespace AdventOfCode2020::Day2::Part1
{
  struct LineData {
    int min;
    int max;
    char type;
    std::string password;

    [[nodiscard]] bool IsValid() const;
  };

  bool LineData::IsValid() const {
    const auto count = std::count(this->password.begin(), this->password.end(), this->type);

    return
      count >= this->min &&
      count <= this->max;
  }

  std::optional<LineData> ParseLineData(const std::string& line) {
    static std::regex regex(R"((\d+)-(\d+) (.): (.+))",
      std::regex_constants::ECMAScript);

    std::smatch matches;

    if (std::regex_match(line, matches, regex)) {
      const auto min = std::stoi(matches[1]);
      const auto max = std::stoi(matches[2]);
      const auto type = matches[3].str()[0];

      return LineData{ min, max, type, matches[4] };
    }

    return {};
  }

  int Solve(const std::vector<std::string>& data_set) {
    int valid_password_count = 0;

    for (const auto& line : data_set) {
      const auto line_data = ParseLineData(line);

      if (line_data == std::nullopt) {
        return -1;
      }

      if (line_data->IsValid()) {
        valid_password_count++;
      }
    }

    return valid_password_count;
  }
}
