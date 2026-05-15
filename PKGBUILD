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
source=()
sha256sums=()

build() {
    cd "$srcdir/$pkgname-v$pkgver"
    # Uncomment to compile with XWayland support
    sed -i -e '/-DXWAYLAND\|xcb/s/^#//' config.mk

    if [ ! -e "$srcdir/config.h" ]; then
        ln -s "$srcdir/config.h" config.h
    fi

    make
}

package() {
    cd "$srcdir/$pkgname-v$pkgver"
    make PREFIX="$pkgdir/usr/" install
}
