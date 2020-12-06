#include "AdventOfCode.2020.Day4/passport_processing_part_2.h"

#include "AdventOfCode.2020.Common/trim.h"

#include <fstream>
#include <optional>
#include <regex>
#include <unordered_map>

namespace AdventOfCode2020::Day4::Part2
{
  template <typename T>
  struct PassportProperty {
    PassportProperty() = default;
    explicit PassportProperty(T value);
    virtual ~PassportProperty() = default;

    T value = {};
    bool exists = {};

    [[nodiscard]] virtual bool IsValid() const;
  };

  template<typename T>
  PassportProperty<T>::PassportProperty(T value) : value(std::move(value)), exists(true) {}

  template <typename T>
  bool PassportProperty<T>::IsValid() const {
    return this->exists;
  }

  struct BirthYearProperty : PassportProperty<int> {
    BirthYearProperty() = default;
    BirthYearProperty(int byr);

    [[nodiscard]] bool IsValid() const override;
  };

  BirthYearProperty::BirthYearProperty(int byr)
    : PassportProperty(byr) {}

  bool BirthYearProperty::IsValid() const {
    return PassportProperty::IsValid() &&
      this->value >= 1920 &&
      this->value <= 2002;
  }

  struct IssueYearProperty : PassportProperty<int> {
    IssueYearProperty() = default;
    IssueYearProperty(int iyr);

    [[nodiscard]] bool IsValid() const override;
  };

  IssueYearProperty::IssueYearProperty(int iyr)
    : PassportProperty(iyr) {}

  bool IssueYearProperty::IsValid() const {
    return PassportProperty::IsValid() &&
      this->value >= 2010 &&
      this->value <= 2020;
  }

  struct ExpirationYearProperty : PassportProperty<int> {
    ExpirationYearProperty() = default;
    ExpirationYearProperty(int eyr);

    [[nodiscard]] bool IsValid() const override;
  };

  ExpirationYearProperty::ExpirationYearProperty(int eyr)
    : PassportProperty(eyr) {}

  bool ExpirationYearProperty::IsValid() const {
    return PassportProperty::IsValid() &&
      this->value >= 2020 &&
      this->value <= 2030;
  }

  struct HeightProperty : PassportProperty<std::string> {
    enum Type {
      kCentimetres,
      kInches
    };

    HeightProperty() = default;
    HeightProperty(std::string hgt);

    [[nodiscard]] std::optional<Type> HeightType() const;
    [[nodiscard]] std::optional<int> GetHeight(Type type) const;
    [[nodiscard]] bool IsValid() const override;
  };

  HeightProperty::HeightProperty(std::string hgt)
    : PassportProperty(hgt) {}

  std::optional<HeightProperty::Type> HeightProperty::HeightType() const {
    if (this->value.find("cm") != std::string::npos) {
      return Type::kCentimetres;
    }
    if (this->value.find("in") != std::string::npos) {
      return Type::kInches;
    }
    return {};
  }

  std::optional<int> HeightProperty::GetHeight(const Type type) const {
    switch (type) {
    case Type::kCentimetres:
      return std::stoi(this->value.substr(0, this->value.find("cm")));
    case Type::kInches:
      return std::stoi(this->value.substr(0, this->value.find("in")));
    default:
      return {};
    }
  }

  bool HeightProperty::IsValid() const {
    if (!PassportProperty::IsValid()) {
      return false;
    }
    const auto height_type = this->HeightType();
    if (height_type == std::nullopt) {
      return false;
    }
    const auto height = this->GetHeight(*height_type);
    if (height == std::nullopt) {
      return false;
    }
    switch (*height_type) {
    case Type::kCentimetres:
      return
        *height >= 150 &&
        *height <= 193;
    case Type::kInches:
      return
        *height >= 59 &&
        *height <= 76;
    default:
      return false;
    }
  }

  struct HairColorProperty : PassportProperty<std::string> {
    HairColorProperty() = default;
    HairColorProperty(std::string hcl);

    [[nodiscard]] bool IsValid() const override;
  };

  HairColorProperty::HairColorProperty(std::string hcl)
    : PassportProperty(hcl) {}

  bool HairColorProperty::IsValid() const {
    if (!PassportProperty::IsValid()) {
      return false;
    }
    static std::regex regex(R"(#(?:[0-9a-fA-F]{6}))", std::regex_constants::ECMAScript);
    return std::regex_match(this->value, regex);
  }

  struct EyeColorProperty : PassportProperty<std::string> {
    EyeColorProperty() = default;
    EyeColorProperty(std::string ecl);

    [[nodiscard]] bool IsValid() const override;
  };

  EyeColorProperty::EyeColorProperty(std::string ecl)
    : PassportProperty(ecl) {}

  static std::vector<std::string> EyeColors = {
      {"amb"},
      {"blu"},
      {"brn"},
      {"gry"},
      {"grn"},
      {"hzl"},
      {"oth"}
  };

  bool EyeColorProperty::IsValid() const {
    if (!PassportProperty::IsValid()) {
      return false;
    }
    return std::find(EyeColors.begin(), EyeColors.end(), this->value) != EyeColors.end();;
  }

  struct PassportIdProperty : PassportProperty<std::string> {
    PassportIdProperty() = default;
    PassportIdProperty(std::string pid);

    [[nodiscard]] bool IsValid() const override;
  };

  PassportIdProperty::PassportIdProperty(std::string pid)
    : PassportProperty(pid) {}

  bool PassportIdProperty::IsValid() const {
    if (!PassportProperty::IsValid()) {
      return false;
    }
    static std::regex regex(R"(\d{9})", std::regex_constants::ECMAScript);
    return std::regex_match(this->value, regex);
  }

  struct Passport {
    BirthYearProperty byr = {};
    IssueYearProperty iyr = {};
    ExpirationYearProperty eyr = {};
    HeightProperty hgt = {};
    HairColorProperty hcl = {};
    EyeColorProperty ecl = {};
    PassportIdProperty pid = {};
    PassportProperty<std::string> cid = {};

    [[nodiscard]] bool IsValid() const;
  };

  bool Passport::IsValid() const {
    return
        this->byr.IsValid() && this->iyr.IsValid() && this->eyr.IsValid() &&
        this->hgt.IsValid() && this->hcl.IsValid() && this->ecl.IsValid() &&
        this->pid.IsValid();
  }

  std::vector<std::string> ReadPassportFile(const std::string_view file_path) {
    std::vector<std::string> passports = {};
    std::string current_line = {};
    std::string line = {};
    std::ifstream stream(file_path.data());

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
        passport.byr = BirthYearProperty{ std::stoi(tokenized_passport_data.at("byr")) };
      }
      if (tokenized_passport_data.contains("iyr")) {
        passport.iyr = IssueYearProperty{ std::stoi(tokenized_passport_data.at("iyr")) };
      }
      if (tokenized_passport_data.contains("eyr")) {
        passport.eyr = ExpirationYearProperty{ std::stoi(tokenized_passport_data.at("eyr")) };
      }
      if (tokenized_passport_data.contains("hgt")) {
        passport.hgt = HeightProperty{ tokenized_passport_data.at("hgt") };
      }
      if (tokenized_passport_data.contains("hcl")) {
        passport.hcl = HairColorProperty{ tokenized_passport_data.at("hcl") };
      }
      if (tokenized_passport_data.contains("ecl")) {
        passport.ecl = EyeColorProperty{ tokenized_passport_data.at("ecl") };
      }
      if (tokenized_passport_data.contains("pid")) {
        passport.pid = PassportIdProperty{ tokenized_passport_data.at("pid") };
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

  int Solve(const std::string_view file_path) {
    const auto data_set = ReadPassportFile(file_path);

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
