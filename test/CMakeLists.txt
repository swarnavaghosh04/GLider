foreach(test_target init window)

    add_executable(${test_target})
    target_sources(${test_target} PRIVATE ${test_target}.cpp)
    target_link_libraries(${test_target} PRIVATE GLider)
    add_test(NAME ${test_target} COMMAND ${test_target})

endforeach()

foreach(normal_target cube triangle)

    add_executable(${normal_target})
    target_sources(${normal_target} PRIVATE ${normal_target}.cpp)
    target_link_libraries(${normal_target} PRIVATE GLider)

endforeach()

