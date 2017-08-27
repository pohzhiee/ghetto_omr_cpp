add_subdirectory(content2)
set(SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/content1.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/content2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/content3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/content4.cpp
        ${SOURCE}
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/contents.h
        ${CMAKE_CURRENT_SOURCE_DIR}/content2.h
        PARENT_SCOPE
        )