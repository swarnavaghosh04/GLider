find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(GLider STATIC)

set_property(TARGET GLider PROPERTY VERSION ${CMAKE_PROJECT_VERSION})
set_property(TARGET GLider PROPERTY SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

# include(GenerateExportHeader)
# generate_export_header(
#     GLider
#     EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/../include/GLider/GLider_export.h
# )

file(
    GLOB GLider_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/GLider/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/GLider/impl/*.inl"
)

target_sources(
    GLider PRIVATE
    ${GLider_SOURCES}
    $<TARGET_OBJECTS:glad>
)

target_link_libraries(GLider PUBLIC glad ${OPENGL_LIBRARIES} SDL2::SDL2 glm)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(GLider PUBLIC GLI_DEBUG)
endif()

target_include_directories(
    GLider PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)