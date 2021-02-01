set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_library(HermyGL SHARED)

set_property(TARGET HermyGL PROPERTY VERSION ${CMAKE_PROJECT_VERSION})
set_property(TARGET HermyGL PROPERTY SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

include(GenerateExportHeader)
generate_export_header(
    HermyGL
    EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/../include/HermyGL/HermyGL_export.h
)

file(
    GLOB HermyGL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/HermyGL/*.hpp"
)

target_sources(
    HermyGL PRIVATE
    ${HermyGL_SOURCES}
)

target_link_libraries(HermyGL INTERFACE SDL2::SDL2 glad ${OPENGL_LIBRARIES})

get_target_property(glad_inculde glad INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(SDL2_inculde SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(
    HermyGL PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${glad_inculde}
        ${SDL2_inculde}
)