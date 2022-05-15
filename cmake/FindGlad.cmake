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

    project(glad LANGUAGES C)

    SET_GLAD_OPTION("profile" "core" "OpenGL profile (defaults to core)")
    SET_GLAD_OPTION("api" "" "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    SET_GLAD_OPTION("spec" "" "Name of spec (gl, egl, glx or wgl)")
    SET_GLAD_OPTION("extensions" "" "Path to extensions file or comma separated list of extensions, if missing all extensions are included")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        set(GLAD_GEN "c-debug")
    else()
        set(GLAD_GEN "c")
    endif()

    add_library(glad OBJECT)

    if(
        NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/src/glad.c OR
        NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/include/glad/glad.h OR
        NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/include/KHR/khrplatform.h
    )
        message(STATUS "generating glad sources using python pip")
        execute_process(
            COMMAND python3 -m pip install glad
        )
        execute_process(
            COMMAND python3 -m glad --out-path ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad ${GLAD_PROFILE} ${GLAD_API} ${GLAD_SPEC} ${GLAD_EXTENSIONS} --generator=${GLAD_GEN}
        )
    else()
        message(STATUS "using previously generated glad sources")
    endif()

    target_sources(
        glad PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/src/glad.c
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/include/glad/glad.h
        ${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/include/KHR/khrplatform.h
    )

    target_link_libraries(glad INTERFACE ${CMAKE_DL_LIBS})

    include(GNUInstallDirs)

    target_include_directories(
        glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extern/glad/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/GLider/extern>
    )

    install(DIRECTORY extern/glad/include/glad extern/glad/include/KHR DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GLider/extern)
    
    install(
        TARGETS glad
        EXPORT GLiderTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT GLider_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/GLider
            COMPONENT GLider_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/GLider
            COMPONENT GLider_Development
    )

endif()

add_library(glad::glad ALIAS glad)
