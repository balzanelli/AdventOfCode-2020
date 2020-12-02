#include "AdventOfCode.2020.Day2/password_philosophy_part_2.h"

#include <optional>
#include <regex>

namespace AdventOfCode2020::Day2::Part2
{
  struct LineData {
    int pos1;
    int pos2;
    char type;
    std::string password;

    [[nodiscard]] char GetAt(int pos) const;
    [[nodiscard]] bool IsInBounds(int pos) const;
    [[nodiscard]] bool IsValid() const;
  };

  char LineData::GetAt(const int pos) const {
    return this->IsInBounds(pos) ? this->password[pos] : ' ';
  }

  bool LineData::IsInBounds(const int pos) const {
    return pos <= static_cast<int>(this->password.size());
  }

  bool LineData::IsValid() const {
    const auto c1 = this->GetAt(this->pos1 - 1);
    const auto c2 = this->GetAt(this->pos2 - 1);

    int matches = 0;

    if (c1 == this->type) {
      matches++;
    }

    if (c2 == this->type) {
      matches++;
    }

    return matches == 1;
  }

  std::optional<LineData> ParseLineData(const std::string& line) {
    static std::regex regex(R"((\d+)-(\d+) (.): (.+))",
      std::regex_constants::ECMAScript);

    std::smatch matches;

    if (std::regex_match(line, matches, regex)) {
      const auto pos1 = std::stoi(matches[1]);
      const auto pos2 = std::stoi(matches[2]);
      const auto type = matches[3].str()[0];

      return LineData{ pos1, pos2, type, matches[4] };
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
