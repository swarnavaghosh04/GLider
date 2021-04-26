cmake_minimum_required(VERSION 3.13)

execute_process(
    COMMAND sdl2-config --version
    OUTPUT_VARIABLE sdl2-version
)

foreach(flag version cflags libs static-libs)
    execute_process(
        COMMAND sdl2-config --${flag}
        OUTPUT_VARIABLE sdl2-${flag}
    )
    string(REPLACE " " ";" sdl2-${flag} ${sdl2-${flag}})
endforeach()

project(SDL2 LANGUAGES C) # VERSION ${sdl2-version})

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/std=c++${CMAKE_CXX_STANDARD} ${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD} ${CMAKE_CXX_FLAGS}")
endif()

add_library(SDL2 INTERFACE IMPORTED)
add_library(SDL2-static INTERFACE IMPORTED)

target_compile_options(SDL2 INTERFACE "${sdl2-cflags}")
target_compile_options(SDL2-static INTERFACE "${sdl2-cflags}")

target_link_options(SDL2 INTERFACE "${sdl2-libs}")
target_link_options(SDL2-static INTERFACE "${sdl2-static-libs}")

add_library(SDL2::SDL2 ALIAS SDL2)
add_library(SDL2::SDL2-static ALIAS SDL2-static)

message(${sdl2-version})
message(${sdl2-cflags})
message(${sdl2-libs})
message(${sdl2-static-libs})