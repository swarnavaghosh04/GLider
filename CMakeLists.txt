cmake_minimum_required(VERSION 3.10)
project(HermyGL LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include(GNUInstallDirs)

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# Set where dependency libraries are going to be built

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/HermyGL)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/HermyGL)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_BINDIR})

set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib/${CMAKE_INSTALL_LIBDIR})
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib/${CMAKE_INSTALL_LIBDIR})
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})

# build dependency libraries

add_subdirectory(lib/glad)

# Set where library is going to be built

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)

set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)

# build library

add_subdirectory(src)
add_subdirectory(test)

# install library and test for library

install(
    TARGETS HermyGL test1 test2
    EXPORT HermyGLTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT HermyGL_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT HermyGL_Development # HermyGL_Runtime NAMELINK_SKIP
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT HermyGL_Development
)
# install(
#     TARGETS HermyGL
#     EXPORT HermyGLTargets
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         COMPONENT HermyGL_Development NAMELINK_ONLY
# )
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/HermyGL
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# install dependency libraries

install(
    TARGETS glad
    EXPORT HermyGLTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT HermyGL_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/HermyGL
        COMPONENT HermyGL_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/HermyGL
        COMPONENT HermyGL_Development
)
install(
    EXPORT HermyGLTargets
    FILE HermyGLTargets.cmake
    NAMESPACE HermyGL::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HermyGL
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/HermyGLConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/HermyGLConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HermyGL
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/HermyGLConfigVersion.cmake
    VERSION ${HermyGL_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/HermyGLConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/HermyGLConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HermyGL
)

export(
    EXPORT HermyGLTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/HermyGLTargets.cmake
    NAMESPACE HermyGL::
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