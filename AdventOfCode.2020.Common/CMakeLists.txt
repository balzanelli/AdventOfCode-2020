cmake_minimum_required (VERSION 3.8)

set (SOURCE_FILES
		"file.cc"
		"trim.cc"
	)

add_library (AdventOfCode.2020.Common
		STATIC
			${SOURCE_FILES}
		)

target_compile_features (AdventOfCode.2020.Common
		PRIVATE
			cxx_std_20
		)

target_include_directories (AdventOfCode.2020.Common
		PUBLIC
			${PROJECT_SOURCE_DIR}
	)
