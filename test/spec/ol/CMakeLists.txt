#
# olqt5/test/spec/ol/CMakeLists.txt
#

include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR}/src)

add_executable(uri_test uri.test.cpp)
target_link_libraries(uri_test olqt ${GTEST_BOTH_LIBS})
add_dependencies(uri_test googletest_build)



# end of file
