cmake_minimum_required(VERSION 3.9)
project(ghetto_omr)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(src)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )
add_executable(ghetto_omr ${SOURCE} ${HEADERS})

target_link_libraries(ghetto_omr
        ${GTKMM_LIBRARIES}  )