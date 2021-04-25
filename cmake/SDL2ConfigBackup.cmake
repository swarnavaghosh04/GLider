cmake_minimum_required(VERSION 3.13)

project(SDL2 LANGUAGES C)# VERSION ${sdl2-version})

execute_process(
    COMMAND sdl2-config --version
    OUTPUT_VARIABLE sdl2-version
    ERROR_VARIABLE sdl2-version-error
    ENCODING UTF8
)

message(STATUS ${sdl2-version})

add_library(SDL2 INTERFACE IMPORTED)
add_library(SDL2-static INTERFACE IMPORTED)

execute_process(
    COMMAND sdl2-config --cflags
    OUTPUT_VARIABLE sdl2-cflags
)

message(STATUS ${sdl2-cflags})

execute_process(
    COMMAND sdl2-config --libs
    OUTPUT_VARIABLE sdl2-libs
)

message(STATUS ${sdl2-libs})

execute_process(
    COMMAND sdl2-config --static-libs
    OUTPUT_VARIABLE sdl2-static-libs
)

message(STATUS ${sdl2-static-libs})

find_library(SDL2-library NAMES SDL2)
find_library(SDL2-main NAMES SDL2main)

target_link_libraries(SDL2 INTERFACE ${SDL2-library} ${SDL2-main})
target_link_libraries(SDL2-static INTERFACE ${SDL2-library} ${SDL2-main})

find_path(sdl2-incl NAMES "SDL2/SDL.h")
target_include_directories(SDL2 INTERFACE ${sdl2-incl})
target_include_directories(SDL2-static INTERFACE ${sdl2-incl})

target_compile_options(SDL2 INTERFACE ${sdl2-cflags})
target_compile_options(SDL2-static INTERFACE ${sdl2-cflags})

target_link_options(SDL2 INTERFACE ${sdl2-libs})
target_link_options(SDL2-static INTERFACE ${sdl2-static-libs})

add_library(SDL2::SDL2 ALIAS SDL2)
add_library(SDL2::SDL2-static ALIAS SDL2-static)