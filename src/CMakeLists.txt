add_subdirectory(startup)

set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gui_main.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/data.h
        ${CMAKE_CURRENT_SOURCE_DIR}/gui_main.h
        PARENT_SCOPE
        )