cmake_minimum_required(VERSION 3.12)

include(../../cmake/HunterGate.cmake)

HunterGate(
        URL  https://github.com/soramitsu/soramitsu-hunter/archive/master.tar.gz
        SHA1 39113c56b1d6be190b13995348816710dc1715f7
)

project(ScaleTest CXX)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/scale-install/")
find_package(scale REQUIRED)

hunter_add_package(Boost COMPONENTS random)
find_package(Boost CONFIG REQUIRED random)

add_executable(scale_test scale_test.cpp)
target_link_libraries(scale_test
    scale::scale
    )
add_test(NAME scale_test COMMAND $<TARGET_FILE:scale_test>)
set_target_properties(scale_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_bin
    ARCHIVE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/test_lib
    LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/test_lib
    )
