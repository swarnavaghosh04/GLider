cmake_minimum_required(VERSION 3.10)

if(NOT glad_FOUND)

    message(STATUS "glad not found, generating sources using python pip")

    project(glad LANGUAGES C)

    set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile (defaults to compatibility)")
    set(GLAD_API "" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    set(GLAD_SPEC "" CACHE STRING "Name of spec (gl, egl, glx or wgl)")
    set(GLAD_EXTENSIONS "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included")

    if(NOT (GLAD_PROFILE STREQUAL ""))
        string(PREPEND GLAD_PROFILE "--profile;")
    endif()

    if(NOT (GLAD_API STREQUAL ""))
        string(PREPEND GLAD_API "--api;")
    endif()

    if(NOT (GLAD_SPEC STREQUAL ""))
        string(PREPEND GLAD_SPEC "--spec;")
    endif()

    if(NOT (GLAD_EXTENSIONS STREQUAL ""))
        string(PREPEND GLAD_EXTENSIONS "--extensions;")
    endif()

    add_library(glad OBJECT)

    execute_process(
        COMMAND python3 -m pip install glad
    )
    execute_process(
        COMMAND python3 -m glad --out-path ${CMAKE_CURRENT_SOURCE_DIR} ${GLAD_PROFILE} ${GLAD_API} ${GLAD_SPEC} ${GLAD_EXTENSIONS} --generator=c
    )

    file(
        GLOB glad_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
    )

    target_sources(glad PRIVATE ${glad_SOURCES})
    target_link_libraries(glad INTERFACE ${CMAKE_DL_LIBS})

    include(GNUInstallDirs)

    target_include_directories(
        glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/GLider>
    )

    install(DIRECTORY include/glad include/KHR DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GLider)

    add_library(glad::glad ALIAS glad)

endif()
