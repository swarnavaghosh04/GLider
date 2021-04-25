cmake_minimum_required(VERSION 3.13)

# execute_process(
#     COMMAND sdl2-config --version
#     OUTPUT_VARIABLE sdl2-version
# )

project(SDL2 LANGUAGES C VERSION) #${sdl2-version})

add_library(SDL2 INTERFACE IMPORTED)
add_library(SD2-static INTERFACE IMPORTED)

execute_process(
    COMMAND sdl2-config --libs
    OUTPUT_VARIABLE sdl2-libs
)

execute_process(
    COMMAND sdl2-config --static-libs
    OUTPUT_VARIABLE sdl2-static-libs
)

find_path(sdl2-incl NAMES "SDL2/SDL.h")
target_include_directories(SDL2 INTERFACE ${sdl2-incl})
target_include_directories(SDL2-static INTERFACE ${sdl2-incl})

target_link_options(SDL2 INTERFACE ${sdl2-libs})
target_link_options(SDL2-static INTERFACE ${sdl2-static-libs})

add_library(SDL2::SDL2 ALIAS SDL2)
add_library(SDL2::SDL2-static ALIAS SDL2-static)