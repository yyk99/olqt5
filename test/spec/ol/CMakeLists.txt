#
# olqt5/test/spec/ol/CMakeLists.txt
#

macro(add_ol_test name)
    string(REPLACE "/" "_" _name ${name})
    set (name_test ${_name}_test)
    add_executable(${name_test} ${name}.test.cpp)
    target_link_libraries(${name_test} olqt ${GTEST_BOTH_LIBS})
    add_dependencies(${name_test} googletest_build copy_olqt)
    add_test(${name_test} ${name_test})
    set_target_properties(${name_test} PROPERTIES FOLDER "test")
endmacro(add_ol_test)

include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR}/src)

add_custom_command(OUTPUT olqt_copy.timestamp     
    COMMAND ${CMAKE_COMMAND} -E echo copy $<TARGET_FILE:olqt> ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:olqt> ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
    COMMAND ${CMAKE_COMMAND} -E touch olqt_copy.timestamp
    DEPENDS olqt
)

add_custom_target(copy_olqt ALL 
    DEPENDS olqt_copy.timestamp
)
set_target_properties(copy_olqt PROPERTIES FOLDER "test")

add_ol_test(array)
add_ol_test(assertionerror)
add_ol_test(coordinate)
add_ol_test(disposable)
add_ol_test(geolocation)
add_ol_test(index)
add_ol_test(math)
add_ol_test(object)
add_ol_test(proj)
add_ol_test(rotationconstraint)
add_ol_test(size)
add_ol_test(sphere)
add_ol_test(string)
add_ol_test(tile)
add_ol_test(tilecache)
add_ol_test(tilecoord)
add_ol_test(tilerange)
add_ol_test(tilequeue)
add_ol_test(uri)
add_ol_test(vectortile)

# event dir
add_ol_test(events/event)
add_ol_test(events/eventtarget)

# tilegrid dir
add_ol_test(tilegrid/tilegrid)

#
add_ol_test(proj/epsg3857)
add_ol_test(proj/transforms)

# end of file
