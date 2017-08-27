
set(SOURCE
        ${SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/_dialog_qn.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/dialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/marker_class.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mcq_class.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/numerical_class.cpp
        PARENT_SCOPE
        )

set(HEADERS
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/_dialog_qn.h
        ${CMAKE_CURRENT_SOURCE_DIR}/dialog.h
        ${CMAKE_CURRENT_SOURCE_DIR}/marker_class.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mcq_class.h
        ${CMAKE_CURRENT_SOURCE_DIR}/numerical_class.h
        PARENT_SCOPE
        )