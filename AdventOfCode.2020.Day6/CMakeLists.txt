cmake_minimum_required (VERSION 3.8)

set (TARGET_NAME AdventOfCode.2020.Day6)

# Static Library

add_library (${TARGET_NAME}
    STATIC
      "custom_customs_part_1.cc"
      "custom_customs_part_2.cc"
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
    "custom_customs.cc"
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
