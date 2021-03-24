add_executable(cube)
add_executable(triangle)

target_sources(cube PRIVATE cube.cpp)
target_sources(triangle PRIVATE triangle.cpp)

target_link_libraries(cube PRIVATE GLider)
target_link_libraries(triangle PRIVATE GLider)