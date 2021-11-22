cmake_minimum_required(VERSION 3.10)

find_library(glad_lib NAMES glad)
find_path(glad_inc NAMES "glad/glad.h")

if(NOT ${glad_lib} STREQUAL "glad_lib-NOTFOUND" AND NOT ${glad_inc} STREQUAL "glad_inc-NOTFOUND")

    add_library(glad INTERFACE IMPORTED GLOBAL)
    target_link_libraries(glad INTERFACE glad_lib)
    target_include_directories(glad INTERFACE glad_inc)

else()

    function(SET_GLAD_OPTION option default_value doc_string)
        string(TOUPPER ${option} var_name)
        string(PREPEND var_name "GLAD_")
        if(DEFINED "${var_name}")
            set(${var_name} ${${var_name}} CACHE STRING ${doc_string} FORCE)
        else()
            set(${var_name} ${default_value} CACHE STRING ${doc_string} FORCE)
        endif()
        if(NOT ("${${var_name}}" STREQUAL ""))
            string(PREPEND ${var_name} "--${option};")
            set(${var_name} ${${var_name}} PARENT_SCOPE)
        endif()
    endfunction()

    message(STATUS "Generating Glad sources using python pip")

    project(glad LANGUAGES C)

    SET_GLAD_OPTION("profile" "core" "OpenGL profile (defaults to core)")
    SET_GLAD_OPTION("api" "" "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    SET_GLAD_OPTION("spec" "" "Name of spec (gl, egl, glx or wgl)")
    SET_GLAD_OPTION("extensions" "" "Path to extensions file or comma separated list of extensions, if missing all extensions are included")

    add_library(glad OBJECT)

    if(
        NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c OR
        NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h OR
        NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h
    )
        execute_process(
            COMMAND python3 -m pip install glad
        )
        execute_process(
            COMMAND python3 -m glad --out-path ${CMAKE_CURRENT_SOURCE_DIR} ${GLAD_PROFILE} ${GLAD_API} ${GLAD_SPEC} ${GLAD_EXTENSIONS} --generator=c
        )
    endif()

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
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/GLider/external>
    )

    install(DIRECTORY include/glad include/KHR DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GLider/external)

endif()

add_library(glad::glad ALIAS glad)
