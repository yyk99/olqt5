#
# olqt5/test/spec/ol/CMakeLists.txt
#

macro(add_ol_test name)
    add_executable(${name}_test ${name}.test.cpp)
    target_link_libraries(${name}_test olqt ${GTEST_BOTH_LIBS})
    add_dependencies(${name}_test googletest_build)
    add_test(${name}_test ${name}_test)
    add_custom_command(TARGET ${name}_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:olqt> 
        $<TARGET_FILE_DIR:${name}_test>
    )
endmacro(add_ol_test)

include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR}/src)

add_ol_test(uri)
add_ol_test(string)

# end of file
