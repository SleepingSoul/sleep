include(AddBrigand.cmake)

# project defining the foo library
set(lib_name "libtmengine")

file(GLOB_RECURSE lib_srcs *.cpp *.h)

# Declare the library
add_library(${lib_name} STATIC  ${lib_srcs})

AddBrigand(${lib_name})

#include_directories(/mnt/c/CodeProjects/CLion/SFML/SFML-Game-Engine/cmake-build-debug/tmengine/brigand/src/brigand/include)

# where to find headers used by this library
target_include_directories(${lib_name} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

# where to find headers a the scope of this subproject
target_include_directories(
        ${lib_name}
        PRIVATE ecs)

