add_executable(cube)

target_sources(cube PRIVATE cube.cpp)

target_link_libraries(cube PRIVATE HermyGL)