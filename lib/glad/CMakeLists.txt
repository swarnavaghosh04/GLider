cmake_minimum_required(VERSION 3.10)

project(glad LANGUAGES C VERSION 0.1.34)

find_library(glad_lib NAMES glad)
find_path(glad_include NAMES "glad/glad.h")

if(${glad_lib} STREQUAL "glad_lib-NOTFOUND" OR ${glad_include} STREQUAL "glad_include-NOTFOUND")

    message(STATUS "glad not found, resorting to provided library")

    add_library(glad STATIC)

    file(
        GLOB glad_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
    )

    target_sources(glad PRIVATE ${glad_SOURCES})

    include(GNUInstallDirs)

    target_include_directories(
        glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/HermyGL>
    )

    install(DIRECTORY include/glad include/KHR DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/HermyGL)

else()

    message(STATUS "glad found")
    message(STATUS "\tlibrary location: ${glad_lib}")
    message(STATUS "\tbase header:      ${glad_include}/glad/glad.hpp")

    add_library(glad INTERFACE)

    target_link_libraries(glad INTERFACE ${glad_lib})
    target_include_directories(glad INTERFACE ${glad_include})

endif()