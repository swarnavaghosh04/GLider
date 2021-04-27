cmake_minimum_required(VERSION 3.10)

if(NOT glad_FOUND)

    message(STATUS "glad not found, generating sources using python pip")

    project(glad LANGUAGES C)

    add_library(glad OBJECT)

    execute_process(
        COMMAND python3 -m pip install glad
    )
    execute_process(
        COMMAND python3 -m glad --out-path ${CMAKE_CURRENT_SOURCE_DIR} --generator=c --profile=core
    )

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
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/GLider>
    )

    install(DIRECTORY include/glad include/KHR DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GLider)

    add_library(glad::glad ALIAS glad)

endif()
