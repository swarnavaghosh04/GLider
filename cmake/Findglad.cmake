cmake_minimum_required(VERSION 3.10)

find_library(glad_lib NAMES glad)
find_path(glad_inc NAMES "glad/glad.h")

if(NOT ${glad_lib} STREQUAL "glad_lib-NOTFOUND" AND NOT ${glad_inc} STREQUAL "glad_inc-NOTFOUND")

    add_library(glad INTERFACE IMPORTED GLOBAL)
    target_link_libraries(glad INTERFACE glad_lib)
    target_include_directories(glad INTERFACE glad_inc)

else()

    include(GNUInstallDirs)

    if(NOT GLIDER_GLAD_API)
        set(GLIDER_GLAD_API "gl:core" CACHE STRING "--api argument to glad")
    endif()

    message(STATUS "generating glad sources")
    execute_process(COMMAND glad --out-path ${CMAKE_CURRENT_BINARY_DIR}/glad --api ${GLIDER_GLAD_API})

    add_library(glad OBJECT)
    FILE(GLOB glad_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/glad/src/*.c)
    target_sources(glad PRIVATE ${glad_SOURCES})
    target_link_libraries(glad INTERFACE ${CMAKE_DL_LIBS})

    target_include_directories(
        glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/glad/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/GLider>
    )

    message(STATUS ${CMAKE_CURRENT_BINARY_DIR}/glad/include)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glad/include/glad ${CMAKE_CURRENT_BINARY_DIR}/glad/include/KHR DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GLider)
    
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
