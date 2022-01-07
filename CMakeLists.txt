cmake_minimum_required(VERSION 3.10)
project(
    GLider
    LANGUAGES C CXX
    VERSION 0.1.0
    HOMEPAGE_URL https://github.com/swarnavaghosh04/GLider
    DESCRIPTION "A simple library that abstracts OpenGL into classes."
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

set(BUILD_GLIDER_TESTS FALSE CACHE BOOL "Build the unit tests (inside `test` directory)")

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

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)

    set(GLIDER_ROOT_BUILD TRUE BOOL)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR}/GLider)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR}/GLider)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_BINDIR})

    set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR}/GLider)
    set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR}/GLider)
    set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_BINDIR})

else()

    set(GLIDER_ROOT_BUILD FALSE BOOL)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/GLider)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/GLider)

    set(ARCHIVE_OUTPUT_DIRECTORY ${ARCHIVE_OUTPUT_DIRECTORY}/GLider)
    set(LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY}/GLider)

endif()

# build dependency libraries

find_package(OpenGL REQUIRED)
find_package(glad CONFIG)

# Dependency fixes

if(NOT glad_FOUND)
    add_subdirectory(extern/glad)
endif()

# Set where library is going to be built

if(GLIDER_ROOT_BUILD)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR})

    set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR})

else()

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/..)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/..)

    set(ARCHIVE_OUTPUT_DIRECTORY ${ARCHIVE_OUTPUT_DIRECTORY}/..)
    set(LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY}/..)

endif()

# build library

add_subdirectory(src)
if(BUILD_GLIDER_TESTS)
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
if(BUILD_GLIDER_TESTS)
    install(
        TARGETS cube triangle init
        EXPORT GLiderTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT GLider_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT GLider_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT GLider_Development
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/share/GLider/test
        DESTINATION ${CMAKE_INSTALL_DATADIR}/GLider
    )
endif()
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/GLider
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    FILES LICENSE DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/GLider
)

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

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GLider.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/GLider.pc"
    @ONLY)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/cmake/GLider.pc"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake)

endif()