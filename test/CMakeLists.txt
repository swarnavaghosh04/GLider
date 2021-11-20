
find_package(SDL2 CONFIG)

if(NOT TARGET SDL2::SDL2 OR NOT TARGET SDL2::SDL2-static)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2ConfigBackup.cmake)
endif()

add_library(util OBJECT)
target_sources(util PRIVATE util.cpp util.hpp)
target_link_libraries(util INTERFACE SDL2::SDL2)

foreach(target init triangle cube)

    add_executable(${target})
    target_link_libraries(${target} PRIVATE GLider util)
    target_sources(${target} PRIVATE ${target}.cpp $<TARGET_OBJECTS:util>)

endforeach()

add_test(NAME init COMMAND init)
add_test(NAME triangle COMMAND triangle 2000)

