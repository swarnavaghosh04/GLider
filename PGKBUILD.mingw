
# Maintainer: Swarnava Ghosh <swarnavaghosh04@gmail.com>
_realname=HermyGL
pkgbase=mingw-w64-${_realname}
pkgname=${MINGW_PACKAGE_PREFIX}-${_realname}
pkgver=0.1.0
pkgrel=1
pkgdesc="OpenGL Class Abstraction"
arch=('x86_64' 'i686')
url="https://github.com/swarnavaghosh04/HermyGL.git"
license=('MIT')
depends=("${MINGW_PACKAGE_PREFIX}-SDL2")
makedepends=("git" "${MINGW_PACKAGE_PREFIX}-make" "${MINGW_PACKAGE_PREFIX}-cmake" "${MINGW_PACKAGE_PREFIX}-glm") # 'bzr', 'git', 'mercurial' or 'subversion'
provides=("${pkgname}")
conflicts=("${pkgname}")
source=("git+${url}")
md5sums=('SKIP')

prepare() {
	cd "${srcdir}/${_realname}"
}

build() {
	cd "${srcdir}/${_realname}"
	mkdir build
	cd build
	MSYS2_ARG_CONV_EXCL=* \
	cmake .. -G 'MinGW Makefiles' -DCMAKE_INSTALL_PREFIX=${MINGW_PREFIX}
	mingw32-make
}

package() {
	cd "${srcdir}/${_realname}/build"
	DESTDIR=${pkgdir} mingw32-make install
}
