## Installation Procedure ##

# Manual Installation on Linux #

    git clone "https://github.com/swarnavaghosh04/HermyGL.git" ~/HermyGLTemp
    cd ~/HermyGLTemp
    mkdir build && cd build
    cmake .. [-G "<generator>"]
    cmake --build .
    cmake --install . --prefix "/usr" [or --prefix "$HOME/HermyGL"]
    cd ~
    rm -rf HermyGLTemp
