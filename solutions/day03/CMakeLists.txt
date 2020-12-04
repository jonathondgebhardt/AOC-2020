set(SOURCE_H
  ${CMAKE_CURRENT_SOURCE_DIR}/Utilities.ipp
)

set(SOURCE
)

set(
  AOC_SOURCE_H
  ${SOURCE_H}
  ${AOC_SOURCE_H}
  PARENT_SCOPE
)

set(
  AOC_SOURCE
  ${SOURCE}
  ${AOC_SOURCE}
  PARENT_SCOPE
)

add_subdirectory(part1)
add_subdirectory(part2)