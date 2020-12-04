# Since our day solutions are one directory deeper, we have to echo the root AOC variables
# down to subdirectories.
set(
  ${AOC_SOURCE_H}
  AOC_SOURCE_H
  PARENT_SCOPE
)

set(
  ${AOC_SOURCE}
  AOC_SOURCE
  PARENT_SCOPE
)

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)

# Now that we've visited subdirectories, echo the AOC variables back up to the parent scope.
set(
  ${AOC_SOURCE_H}
  AOC_SOURCE_H
  PARENT_SCOPE
)

set(
  ${AOC_SOURCE}
  AOC_SOURCE
  PARENT_SCOPE
)
