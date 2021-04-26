cmake_minimum_required(VERSION 3.13)

# foreach(flag version cflags libs static-libs)
#     execute_process(
#         COMMAND sdl2-config --${flag}
#         OUTPUT_VARIABLE sdl2-${flag}
#     )
#     string(PREPEND sdl2-${flag} "SHELL:")
#     string(REGEX REPLACE "\n$" "" sdl2-${flag} ${sdl2-${flag}})
# endforeach()

execute_process(
	COMMAND pkg-config sdl2 --cflags --libs
	OUTPUT_VARIABLE sdl2-configs
)
string(PREPEND sdl2-configs "SHELL:")
string(REGEX REPLACE "\n$" "" sdl2-configs ${sdl2-configs})

project(SDL2 LANGUAGES C) # VERSION ${sdl2-version})

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/std=c++${CMAKE_CXX_STANDARD} ${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD} ${CMAKE_CXX_FLAGS}")
endif()

add_library(SDL2 INTERFACE IMPORTED GLOBAL)
add_library(SDL2-static INTERFACE IMPORTED GLOBAL)

find_library(SDL2-library NAMES SDL2)
find_library(SDL2-main NAMES SDL2main)
find_path(sdl2-incl NAMES "SDL2/SDL.h")

foreach(target SDL2 SDL2-static)
    target_include_directories(${target} INTERFACE ${sdl2-incl})
    target_link_libraries(${target} INTERFACE ${SDL2-main} ${SDL2-library})
endforeach()

target_link_options(SDL2 INTERFACE ${sdl2-configs})
target_link_options(SDL2-static INTERFACE ${sdl2-configs})

add_library(SDL2::SDL2 ALIAS SDL2)
add_library(SDL2::SDL2-static ALIAS SDL2-static)

# message(${sdl2-version})
# message(${sdl2-cflags})
# message(${sdl2-libs})
# message(${sdl2-static-libs})
message(${sdl2-configs})
