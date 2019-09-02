# this file setups actual tests for a foo library, linking them with built googletest
set(project_name "tmengine-unit-tests")
file(GLOB_RECURSE test_sources *.cpp *.h)

add_executable(${project_name} ${test_sources})

target_link_libraries(${project_name}
    libtmengine
    libgtest
    libgmock
)

include_directories(../../tmengine)
include_directories(ecs .)


add_test(NAME ${project_name}
         COMMAND ${project_name})
