# Installation Procedure #

Manual Installation:

    mkdir build && cd build
    cmake .. -DCMAKE_INSTALL_PREFIX="HermyGL"
    DESTDIR="$HOME" make install

Note:
The final product is installed in `DESTDIR/CMAKE_INSTALL_PREFIX/`.
Therefore, the library will be located at `DESTDIR/CMAKE_INSTALL_PREFIX/lib/libHermyGL.a`.