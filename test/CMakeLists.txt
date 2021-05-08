foreach(target init triangle cube)

    add_executable(${target})
    target_sources(${target} PRIVATE ${target}.cpp)
    target_link_libraries(${target} PRIVATE GLider)

endforeach()

add_test(NAME init COMMAND init)
add_test(NAME triangle COMMAND triangle 2000)

