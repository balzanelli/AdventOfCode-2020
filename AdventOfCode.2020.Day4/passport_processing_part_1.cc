#include "AdventOfCode.2020.Day4/passport_processing_part_1.h"

#include "AdventOfCode.2020.Common/trim.h"

#include <fstream>
#include <optional>
#include <regex>
#include <unordered_map>

namespace AdventOfCode2020::Day4::Part1
{
  template <typename T>
  struct PassportProperty {
    PassportProperty() = default;
    explicit PassportProperty(T value);

    T value = {};
    bool exists = {};
  };

  template<typename T>
  PassportProperty<T>::PassportProperty(T value)
    : value(std::move(value)), exists(true) {}

  struct Passport {
    PassportProperty<int> byr = {};
    PassportProperty<int> iyr = {};
    PassportProperty<int> eyr = {};
    PassportProperty<std::string> hgt = {};
    PassportProperty<std::string> hcl = {};
    PassportProperty<std::string> ecl = {};
    PassportProperty<std::string> pid = {};
    PassportProperty<std::string> cid = {};

    [[nodiscard]] bool IsValid() const;
  };

  bool Passport::IsValid() const {
    return
      this->byr.exists && this->iyr.exists && this->eyr.exists &&
      this->hgt.exists && this->hcl.exists && this->ecl.exists &&
      this->pid.exists;
  }

  std::vector<std::string> ReadPassportFile(const std::string_view file_name) {
    std::vector<std::string> passports = {};
    std::string current_line = {};
    std::string line = {};
    std::ifstream stream(file_name.data());

    if (!stream) {
      return {};
    }

    while (std::getline(stream, line)) {
      if (line.empty()) {
        passports.push_back(Common::Trim(current_line));
        current_line = {};
      } else {
        current_line += line + " ";
      }
    }

    passports.push_back(Common::Trim(current_line));

    return passports;
  }

  std::unordered_map<std::string, std::string> TokenizePassportData(const std::string& line) {
    static std::regex regex(R"([^( |\r\n|\r|\n)]+)", std::regex_constants::ECMAScript);

    std::vector<std::string> tokens{
      std::sregex_token_iterator{ line.begin(), line.end(), regex },
      std::sregex_token_iterator{}
    };

    std::unordered_map<std::string, std::string> key_value_pairs = {};

    for (auto& token : tokens) {
      const auto separator_index = token.find(':');
      if (separator_index != std::string::npos) {
        const auto key = token.substr(0, separator_index);
        const auto value = token.substr(separator_index + 1, token.size() - separator_index - 1);
        key_value_pairs[key] = value;
      }
    }

    return key_value_pairs;
  }

  std::optional<Passport> ParsePassportData(const std::string& line) {
    const auto tokenized_passport_data = TokenizePassportData(line);

    if (!tokenized_passport_data.empty()) {
      Passport passport = {};
      if (tokenized_passport_data.contains("byr")) {
        passport.byr = PassportProperty<int>{ std::stoi(tokenized_passport_data.at("byr")) };
      }
      if (tokenized_passport_data.contains("iyr")) {
        passport.iyr = PassportProperty<int>{ std::stoi(tokenized_passport_data.at("iyr")) };
      }
      if (tokenized_passport_data.contains("eyr")) {
        passport.eyr = PassportProperty<int>{ std::stoi(tokenized_passport_data.at("eyr")) };
      }
      if (tokenized_passport_data.contains("hgt")) {
        passport.hgt = PassportProperty<std::string>{ tokenized_passport_data.at("hgt") };
      }
      if (tokenized_passport_data.contains("hcl")) {
        passport.hcl = PassportProperty<std::string>{ tokenized_passport_data.at("hcl") };
      }
      if (tokenized_passport_data.contains("ecl")) {
        passport.ecl = PassportProperty<std::string>{ tokenized_passport_data.at("ecl") };
      }
      if (tokenized_passport_data.contains("pid")) {
        passport.pid = PassportProperty<std::string>{ tokenized_passport_data.at("pid") };
      }
      if (tokenized_passport_data.contains("cid")) {
        passport.cid = PassportProperty<std::string>{ tokenized_passport_data.at("cid") };
      }
      return passport;
    }

    return {};
  }

  std::vector<Passport> ParsePassports(const std::vector<std::string>& data_set) {
    std::vector<Passport> passports = {};

    for (const auto& line : data_set) {
      const auto passport = ParsePassportData(line);
      if (passport != std::nullopt) {
        passports.push_back(*passport);
      }
    }

    return passports;
  }

  int Solve(const std::string_view file_name) {
    const auto data_set = ReadPassportFile(file_name);

    if (data_set.empty()) {
      return -1;
    }

    int valid_passports = 0;

    for (auto& passport : ParsePassports(data_set)) {
      if (passport.IsValid()) {
        valid_passports++;
      }
    }

    return valid_passports;
  }
}
