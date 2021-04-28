# Installation Procedure #

### For Arch Based Linux ###

1. Copy the contents of the file PKGBUILD.archlinux into `<a_new_empty_dir>/PKGBUILD`
2. Run `makepkg -si` in that directory
3. Remove this directory after successful installation

### For MSYS2 on Windows ###

1. Copy the contents of the file PKGBUILD.msys2-mingw into `<a_new_empty_dir>/PKGBUILD`
2. Run `MINGW_ARCH=mingw64 makepkg-mingw -si` in that directory
(you can change `mingw64` to `mingw32`, or ommit it all together for dual installation)
3. Remove this directory after successful installation

### For Debian Based Linux ###

1. Follow the manual installation procdure with `<install_location>` as `<some_path>/GLider`
2. Before deleting GLiderTemp, copy contents of debian folder into `<install_location>/DEBIAN`:

    ```
    cp <git_local_repo>/debian/. <install_location>/DEBIAN/
    ```

4. Run the following command in `<install_location>/..` (or `<some_path>`):

    ```
    dpkg-deb --build GLider
    rm -rf GLider
    ```

5. Install GLider from the generated .deb file

### Manual Installation ###

    git clone "https://github.com/swarnavaghosh04/GLider.git" ./GLiderTemp
    cd GLiderTemp
    mkdir build && cd build
    cmake ..   # -G "generator_of_your_choice" (if needed)
    cmake --build .
    cmake --install . --prefix "<install_location>"
        # <install_location> can be something like $HOME/GLider or /usr
    cd ../..
    rm -rf GLiderTemp

To use the home build in susequent cmake builds using this library, add the following lines
to you CMakeLists.txt:

    include(GNUInstallDirs) # if not done already
    list(APPEND CMAKE_MODULE_PATH $ENV{HOME}/GLider/${CMAKE_INSTALL_LIBDIR}/cmake)
    find_package(GLider)
