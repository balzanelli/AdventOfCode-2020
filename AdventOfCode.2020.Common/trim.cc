#include "AdventOfCode.2020.Common/trim.h"

namespace AdventOfCode2020::Common
{
  void TrimInPlace(std::string& value) {
    value.erase(std::find_if(value.rbegin(), value.rend(), [](unsigned char c) -> bool {
      return !std::isspace(c);
    }).base(), value.end());
  }

  std::string Trim(std::string value) {
    TrimInPlace(value);
    return value;
  }
}
