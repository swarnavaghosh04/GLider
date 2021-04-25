cmake_minimum_required(VERSION 3.10)
project(GLider LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

if(NOT CMAKE_BUILD_TYPE)
    set(
        CMAKE_BUILD_TYPE "Release" CACHE
        STRING "Choose the type of build." FORCE
    )
endif()

if(NOT BUILD_TESTS)
    set(BUILD_TESTS FALSE)
endif()

string(
    APPEND _opts
    "$<IF:$<CXX_COMPILER_ID:MSVC>,"
        "/W4;$<$<CONFIG:RELEASE>:/O2>,"
        "-Wall;-Wextra;-Werror;"
            "$<$<CONFIG:RELEASE>:-O3>"
    ">"
)
add_compile_options("${_opts}")

include(GNUInstallDirs)

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# Set where dependency libraries are going to be built

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/GLider)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/GLider)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_BINDIR})

set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/GLider)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/GLider)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})

# build dependency libraries

find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG)
add_subdirectory(lib/glad)

# Set where library is going to be built

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})

set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})

# build library

add_subdirectory(src)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# install library and test for library

install(
    TARGETS GLider
    EXPORT GLiderTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT GLider_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT GLider_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT GLider_Development
)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    install(
        TARGETS cube triangle
        EXPORT GLiderTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT GLider_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT GLider_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT GLider_Development
    )
endif()
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/GLider
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    FILES LICENSE DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/GLider
)

# install dependency libraries
if(NOT glad_FOUND)
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

install(
    EXPORT GLiderTargets
    FILE GLiderTargets.cmake
    NAMESPACE GLider::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GLider
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/GLiderConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/GLiderConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GLider
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/GLiderConfigVersion.cmake
    VERSION ${GLider_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/GLiderConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/GLiderConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GLider
)

export(
    EXPORT GLiderTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/GLiderTargets.cmake
    NAMESPACE GLider::
)

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake)

endif()