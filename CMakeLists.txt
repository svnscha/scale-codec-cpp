#
# Copyright Soramitsu Co., Ltd. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.12)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/HunterGate.cmake)

HunterGate(
        URL  https://github.com/soramitsu/soramitsu-hunter/archive/master.tar.gz
        SHA1 39113c56b1d6be190b13995348816710dc1715f7
)

project(Scale CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Whether to include the test suite in build" OFF)

hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

hunter_add_package(Microsoft.GSL)
find_package(Microsoft.GSL CONFIG REQUIRED)

add_subdirectory(src)

if (${BUILD_TESTS})
    add_subdirectory(test ${CMAKE_BINARY_DIR}/tests_bin)
endif()

###############################################################################
#   INSTALLATION
###############################################################################

include(GNUInstallDirs)

install(TARGETS scale buffer EXPORT scaleConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_PREFIX}
    )

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/scale
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT scaleConfig
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/scale
    NAMESPACE scale::
)
