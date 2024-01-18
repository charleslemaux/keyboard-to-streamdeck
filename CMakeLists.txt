cmake_minimum_required(VERSION 3.26)
project(keyboard_to_streamdeck C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)


include_directories(/usr/include/libevdev-1.0/)
include_directories(includes)

add_executable(keyboard_to_streamdeck
        includes/keyboards.h
        includes/san-francisco.h
        src/keyboard_listener.c
        src/keyboards.c
        src/main.c
)
