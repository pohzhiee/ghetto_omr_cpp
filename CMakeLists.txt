cmake_minimum_required(VERSION 3.9)
project(gtk_main)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )

include_directories(
        ${GTKMM_INCLUDE_DIRS}  )
add_subdirectory(src)
add_executable(gtk_main ${SOURCE} ${HEADERS})

target_link_libraries(gtk_main
        ${GTKMM_LIBRARIES}  )