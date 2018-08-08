#
#
#

project (olqt)
cmake_minimum_required(VERSION 3.10)

option (BUILD_TESTS "Buyild tests" ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# find proj4 library

message(STATUS $ENV{LOCALAPPDATA}/OSGeo4W/local/include)

find_path(PROJ4_INCLUDE_DIR names proj.h PATH $ENV{LOCALAPPDATA}/OSGeo4W/local/include)
find_library(PROJ4_LIBRARY_DEBUG names pro_5_0_d.lib PATH $ENV{LOCALAPPDATA}/OSGeo4W/local/lib)
find_library(PROJ4_LIBRARY_RELEASE names pro_5_0.lib PATH $ENV{LOCALAPPDATA}/OSGeo4W/local/lib)

add_subdirectory(src)

if(BUILD_TESTS)
    include(ExternalProject)
 
    list(APPEND GTESTBUILD_CACHE_ARGS "-DBUILD_GMOCK:BOOL=OFF")
    list(APPEND GTESTBUILD_CACHE_ARGS "-DBUILD_GTEST:BOOL=ON")
    list(APPEND GTESTBUILD_CACHE_ARGS "-Dgtest_force_shared_crt:BOOL=ON")
    string(REPLACE ";" "$<SEMICOLON>" CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}")

    list(APPEND GTESTBUILD_CACHE_ARGS "-DCMAKE_CONFIGURATION_TYPES:STRING=${CONFIGURATION_TYPES}")

    ExternalProject_Add(
        googletest_build
	GIT_REPOSITORY    https://github.com/google/googletest.git
	GIT_TAG           "41f0e24335d8874cc87420a6349bb1844e2a15de"
	SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest_src"
	BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest_build"
	TEST_COMMAND      ""
	CMAKE_ARGS        ${GTESTBUILD_CACHE_ARGS}
	INSTALL_COMMAND   ""
#	BUILD_COMMAND     ""
    )

    set(GTEST_SOURCE_DIR ${CMAKE_BINARY_DIR}/googletest_src/googletest)
    set(GTEST_BOTH_LIBS 
        ${CMAKE_BINARY_DIR}/googletest_build/googletest/$<CONFIG>/gtest_main$<$<CONFIG:Debug>:d>.lib
        ${CMAKE_BINARY_DIR}/googletest_build/googletest/$<CONFIG>/gtest$<$<CONFIG:Debug>:d>.lib
        )

    enable_testing()
    add_subdirectory(test)
endif()
