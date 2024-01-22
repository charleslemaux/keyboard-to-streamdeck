cmake_minimum_required(VERSION 3.26)
project(keyboard_to_streamdeck C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LUA REQUIRED lua)
pkg_check_modules(LIBUDEV REQUIRED libudev)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)

include_directories(includes)

add_executable(keyboard_to_streamdeck
        includes/keyboards.h
        includes/san-francisco.h
        src/keyboard_listener.c
        src/keyboards.c
        src/main.c
)

target_link_libraries(keyboard_to_streamdeck ${LUA_LIBRARIES} ${LIBUDEV_LIBRARIES} ${LIBEVDEV_LIBRARIES})
include_directories(${LUA_INCLUDE_DIRS} ${LIBUDEV_INCLUDE_DIRS} ${LIBEVDEV_INCLUDE_DIRS})
