cmake_minimum_required (VERSION 3.8)

project (AdventOfCode.2020 CXX)

enable_testing ()

find_package (GTest)

add_subdirectory (AdventOfCode.2020.Common)
add_subdirectory (AdventOfCode.2020.Day1.ReportRepair)
