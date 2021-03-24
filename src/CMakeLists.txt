find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(HermyGL STATIC)

set_property(TARGET HermyGL PROPERTY VERSION ${CMAKE_PROJECT_VERSION})
set_property(TARGET HermyGL PROPERTY SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

# include(GenerateExportHeader)
# generate_export_header(
#     HermyGL
#     EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/../include/HermyGL/HermyGL_export.h
# )

file(
    GLOB HermyGL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/HermyGL/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include/HermyGL/impl/*.inl"
)

target_sources(
    HermyGL PRIVATE
    ${HermyGL_SOURCES}
    $<TARGET_OBJECTS:glad>
)

target_link_libraries(HermyGL PUBLIC glad ${OPENGL_LIBRARIES} SDL2::SDL2 glm)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(HermyGL PUBLIC HGL_DEBUG)
endif()

target_include_directories(
    HermyGL PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)