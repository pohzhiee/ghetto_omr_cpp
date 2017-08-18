add_subdirectory(startup)
add_subdirectory(mainbox)
add_subdirectory(data)
set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gui_window.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/gui_window.h
        PARENT_SCOPE
        )