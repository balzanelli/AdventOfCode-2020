#pragma once

#include <string_view>
#include <vector>

namespace AdventOfCode2020::Common::File
{
  std::vector<int> ReadAsNumbers(std::string_view file_name);
}
