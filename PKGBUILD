pkgname=dwlalt
pkgver=0.8
pkgrel=0
pkgdesc="Yubo's simple, hackable dynamic tiling Wayland compositor (dwm for Wayland)"
arch=('x86_64')
url="https://codeberg.org/dwl/dwl"
license=('GPL')
depends=('wlroots0.19')
makedepends=('wayland-protocols')
optdepends=('xorg-xwayland: for XWayland support')
source=("$pkgname-v$pkgver.tar.gz"
        config.h)
sha256sums=(SKIP
            SKIP)

prepare() {
	cd "$srcdir/$pkgname-v$pkgver"
	# Use a custom config.h if the file is not empty
	if [ -s "$srcdir/config.h" ]; then
		cp -f "$srcdir/config.h" config.h
	fi
	# Uncomment to compile with XWayland support
	sed -i -e '/-DXWAYLAND\|xcb/s/^#//' config.mk
}

build() {
	cd "$srcdir/$pkgname-v$pkgver"
	make
}

package() {
	cd "$srcdir/$pkgname-v$pkgver"
	make PREFIX="$pkgdir/usr/" install
}
