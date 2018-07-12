#
#
#

set(OLQT_SRC
    dll_export.h
    string.cpp
    string.h
    uri.cpp
    uri.h
)

add_library(olqt SHARED ${OLQT_SRC})

# end of file