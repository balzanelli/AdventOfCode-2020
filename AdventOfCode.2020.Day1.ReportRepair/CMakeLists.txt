cmake_minimum_required (VERSION 3.8)

# Static Library

add_library (AdventOfCode.2020.Day1.ReportRepair
	STATIC
		"report_repair_part_1_brute_force.cc"
		"report_repair_part_1_optimal.cc"
		"report_repair_part_2_brute_force.cc"
		"report_repair_part_2_optimal.cc"
)

target_compile_features (AdventOfCode.2020.Day1.ReportRepair
	PRIVATE
		cxx_std_20
)

target_include_directories (AdventOfCode.2020.Day1.ReportRepair
	PUBLIC
		${PROJECT_SOURCE_DIR}
)

target_link_libraries (AdventOfCode.2020.Day1.ReportRepair
	INTERFACE
		AdventOfCode.2020.Common
)

# Executable

add_executable (AdventOfCode.2020.Day1.ReportRepair.Test
	"report_repair.cc"
)

target_compile_features (AdventOfCode.2020.Day1.ReportRepair.Test
	PRIVATE
		cxx_std_20
)

target_include_directories (AdventOfCode.2020.Day1.ReportRepair.Test
	PUBLIC
		${PROJECT_SOURCE_DIR}
)

target_link_libraries (AdventOfCode.2020.Day1.ReportRepair.Test
	PRIVATE
		AdventOfCode.2020.Day1.ReportRepair
)

# Unit Tests

add_executable (AdventOfCode.2020.Day1.ReportRepair.UnitTest
	"report_repair_tests.cc"
	"report_repair_part_1_brute_force_tests.cc"
	"report_repair_part_1_optimal_tests.cc"
	"report_repair_part_2_brute_force_tests.cc"
	"report_repair_part_2_optimal_tests.cc"
)

add_test (
	NAME
		AdventOfCode.2020.Day1.ReportRepair.UnitTest
	COMMAND
		AdventOfCode.2020.Day1.ReportRepair.UnitTest
)

target_compile_features (AdventOfCode.2020.Day1.ReportRepair.UnitTest
	PRIVATE
		cxx_std_20
)

target_include_directories (AdventOfCode.2020.Day1.ReportRepair.UnitTest
	PUBLIC
		${PROJECT_SOURCE_DIR}
	PRIVATE
		"${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include"
)

target_link_libraries (AdventOfCode.2020.Day1.ReportRepair.UnitTest
	PRIVATE
		AdventOfCode.2020.Day1.ReportRepair
		GTest::gtest
)
