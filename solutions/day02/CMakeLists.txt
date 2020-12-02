set(SOURCE_H
    Export.hpp
    PasswordEntry.ipp
)

set(SOURCE
)

add_library(PasswordEntry SHARED 
    ${SOURCE_H}
    ${SOURCE}
)

set_target_properties(PasswordEntry PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(PasswordEntry AOC)

add_subdirectory(part1)
add_subdirectory(part2)
