cmake_minimum_required(VERSION 3.10)
project(HermyGL LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

if(NOT CMAKE_BUILD_TYPE)
    set(
        CMAKE_BUILD_TYPE "Release" CACHE
        STRING "Choose the type of build." FORCE
    )
endif()


set(CMAKE_CXX_FLAGS_RELEASE "$<IF:$<CXX_COMPILER_ID:MSVC>,/02,-03>")

include(GNUInstallDirs)

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# Set where dependency libraries are going to be built

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/HermyGL)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/HermyGL)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_BINDIR})

set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/HermyGL)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR}/HermyGL)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})

# build dependency libraries

add_subdirectory(lib/glad)

# Set where library is going to be built

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})

set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/${CMAKE_INSTALL_LIBDIR})

# build library

add_subdirectory(src)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_subdirectory(test)
endif()

# install library and test for library

install(
    TARGETS HermyGL
    EXPORT HermyGLTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT HermyGL_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT HermyGL_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT HermyGL_Development
)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    install(
        TARGETS cube triangle
        EXPORT HermyGLTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT HermyGL_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT HermyGL_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT HermyGL_Development
    )
endif()
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/HermyGL
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    FILES LICENSE DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/HermyGL
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