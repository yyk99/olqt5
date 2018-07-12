#
# olqt5/test/spec/ol/CMakeLists.txt
#

macro(add_ol_test name)
    add_executable(${name}_test ${name}.test.cpp)
    target_link_libraries(${name}_test olqt ${GTEST_BOTH_LIBS})
    add_dependencies(${name}_test googletest_build copy_olqt)
    add_test(${name}_test ${name}_test)
endmacro(add_ol_test)

include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR}/src)

add_custom_command(OUTPUT olqt_copy.timestamp     
    COMMAND ${CMAKE_COMMAND} -E echo copy $<TARGET_FILE:olqt> ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:olqt> ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
    COMMAND ${CMAKE_COMMAND} -E touch olqt_copy.timestamp
    DEPENDS olqt
)

add_custom_target(copy_olqt ALL 
    DEPENDS olqt_copy.timestamp
)

add_ol_test(uri)
add_ol_test(string)

# end of file
