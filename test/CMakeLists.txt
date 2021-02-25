add_executable(test1)
add_executable(test2)

target_sources(test1 PRIVATE test1.cpp)
target_sources(test2 PRIVATE test2.cpp)

target_link_libraries(test1 PRIVATE HermyGL)
target_link_libraries(test2 PRIVATE HermyGL)