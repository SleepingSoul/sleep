# this file adds googletest files to our build directory
include(AddGoogleTest.cmake)
find_package(Threads REQUIRED)

AddGoogleTest()

add_subdirectory(tmengine)
