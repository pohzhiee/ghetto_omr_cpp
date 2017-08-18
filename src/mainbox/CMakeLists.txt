add_subdirectory(contents)
set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/mainbox.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/stepbox.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/mainbox.h
        ${CMAKE_CURRENT_SOURCE_DIR}/stepbox.h
        PARENT_SCOPE
        )