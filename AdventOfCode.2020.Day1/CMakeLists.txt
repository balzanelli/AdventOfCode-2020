cmake_minimum_required (VERSION 3.8)

set (TARGET_NAME AdventOfCode.2020.Day1)

# Static Library

add_library (${TARGET_NAME}
	STATIC
		"report_repair_part_1_brute_force.cc"
		"report_repair_part_1_optimal.cc"
		"report_repair_part_2_brute_force.cc"
		"report_repair_part_2_optimal.cc"
)

target_compile_features (${TARGET_NAME}
	PRIVATE
		cxx_std_20
)

target_include_directories (${TARGET_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}
)

target_link_libraries (${TARGET_NAME}
	INTERFACE
		AdventOfCode.2020.Common
)

# Executable

add_executable (${TARGET_NAME}.Test
	"report_repair.cc"
)

target_compile_features (${TARGET_NAME}.Test
	PRIVATE
		cxx_std_20
)

target_include_directories (${TARGET_NAME}.Test
	PUBLIC
		${PROJECT_SOURCE_DIR}
)

target_link_libraries (${TARGET_NAME}.Test
	PRIVATE
		${TARGET_NAME}
)

# Unit Tests

add_executable (${TARGET_NAME}.UnitTest
	"report_repair_tests.cc"
	"report_repair_part_1_brute_force_tests.cc"
	"report_repair_part_1_optimal_tests.cc"
	"report_repair_part_2_brute_force_tests.cc"
	"report_repair_part_2_optimal_tests.cc"
)

add_test (
	NAME
		${TARGET_NAME}.UnitTest
	COMMAND
		${TARGET_NAME}.UnitTest
)

target_compile_features (${TARGET_NAME}.UnitTest
	PRIVATE
		cxx_std_20
)

target_include_directories (${TARGET_NAME}.UnitTest
	PUBLIC
		${PROJECT_SOURCE_DIR}
	PRIVATE
		"${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include"
)

target_link_libraries (${TARGET_NAME}.UnitTest
	PRIVATE
		${TARGET_NAME}
		GTest::gtest
)
