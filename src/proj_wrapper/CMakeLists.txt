#
#
#

set(PROJ_WRAPPER_SRC
    proj_wrapper.cpp
    proj_wrapper.h
)

add_library(proj_wrapper STATIC ${PROJ_WRAPPER_SRC})
target_link_libraries(proj_wrapper PRIVATE
    debug ${PROJ4_LIBRARY_DEBUG}
    optimized ${PROJ4_LIBRARY_RELEASE}
)
target_include_directories(proj_wrapper PRIVATE 
    ${PROJ4_INCLUDE_DIR}
)
set_target_properties(proj_wrapper PROPERTIES FOLDER "src")

# end of file
