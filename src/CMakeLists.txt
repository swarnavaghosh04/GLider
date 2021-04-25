
add_library(GLider STATIC)

set_property(TARGET GLider PROPERTY VERSION ${CMAKE_PROJECT_VERSION})
set_property(TARGET GLider PROPERTY SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

file(
    GLOB GLider_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/GLider/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/GLider/impl/*.inl"
)

target_sources(
    GLider PRIVATE
    ${GLider_SOURCES}
)

if(NOT glad_FOUND)
    target_sources(
        GLider PRIVATE
        $<TARGET_OBJECTS:glad>
    )
endif()

target_link_libraries(GLider PUBLIC glad::glad ${OPENGL_LIBRARIES} SDL2::SDL2)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(GLider PUBLIC GLI_DEBUG)
endif()

get_target_property(glm_incl glm::glm INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(
    GLider PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${glm_incl}
)