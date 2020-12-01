#include "AdventOfCode.2020.Common/file.h"

#include <fstream>
#include <iostream>
#include <string>

namespace AdventOfCode2020::Common::File
{
  std::vector<int> ReadAsNumbers(const std::string_view file_name) {
    std::vector<int> items = {};
    std::string      line = {};
    std::ifstream    stream(file_name.data());

    if (!stream) {
      std::cout << "Failed To Open File: " << file_name << std::endl;
      return {};
    }

    while (std::getline(stream, line)) {
      if (line.empty()) {
        continue;
      }

      try {
        items.push_back(std::stoi(line));
      }
      catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
      }
    }

    return items;
  }
}
