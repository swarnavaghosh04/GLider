# Installation Procedure #

## For Arch Based Linux ##

1. Copy the contents of PKGBUILD.archlinux into `a_new_empty_dir/PKGBUILD`
2. Run `makepkg -si` in that directory
3. Remove this directory after successful installation

## For MSYS2 on Windows ##

1. Copy the contents of PKGBUILD.msys2-mingw into `a_new_empty_dir/PKGBUILD`
2. Run `MINGW_ARCH=mingw64 makepkg-mingw -si` in that directory
(you can change `mingw64` to `mingw32`, or ommit it all together for dual installtion)
3. Remove this directory after successful installation

## Manual Installation on Linux ##

    git clone "https://github.com/swarnavaghosh04/HermyGL.git" ~/HermyGLTemp
    cd ~/HermyGLTemp
    mkdir build && cd build
    cmake ..   # -G "generator_of_your_choice" (if needed)
    cmake --build .
    cmake --install . --prefix "/usr"    # or --prefix "$HOME/HermyGL"
    cd ~
    rm -rf HermyGLTemp
