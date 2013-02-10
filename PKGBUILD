# $Id: PKGBUILD 60970 2011-12-19 21:33:58Z spupykin $
# Maintainer: Sergej Pupykin <pupykin.s+arch@gmail.com>
# Contributor: Dag Odenhall <dag.odenhall@gmail.com>
# Contributor: Grigorios Bouzakis <grbzks@gmail.com>

pkgname=dwm
pkgver=6.0
pkgrel=1
pkgdesc="A dynamic window manager for X"
url="http://dwm.suckless.org"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama')
install=dwm.install
source=(http://dl.suckless.org/dwm/dwm-$pkgver.tar.gz
        config.h
        dwm.desktop
        dwm-6.0-pertag.diff
        dwm-6.0-systray.diff
        dwm-5.9-uselessgap.diff
        dwm-5.9-statuscolors.diff
        dwm-6.0-statuscolors-systray-fix.diff)

md5sums=('8bb00d4142259beb11e13473b81c0857'
         '6f5c46e8039fc26340efffb07f29587f'
         '939f403a71b6e85261d09fc3412269ee'
         'be94530c8592342bd99c7b5eeafdd176'
         '0a527af3bcfbf628ed118bdf86521161'
         'bf8bf3ed1edc0a72ab77135b73a0c8cc'
         '76706fdeda50e0a9f8367079efee7149'
         'f19e11f0ac11a1fbde29234e3b73e18f')

build() {
  cd $srcdir/$pkgname-$pkgver
  cp $srcdir/config.h config.h
  patch -p1 < ../dwm-6.0-pertag.diff
  patch -p1 < ../dwm-6.0-systray.diff
  patch -p1 < ../dwm-5.9-uselessgap.diff
  patch -p1 < ../dwm-5.9-statuscolors.diff
  patch -p1 < ../dwm-6.0-statuscolors-systray-fix.diff
  sed -i 's/CPPFLAGS =/CPPFLAGS +=/g' config.mk
  sed -i 's/^CFLAGS = -g/#CFLAGS += -g/g' config.mk
  sed -i 's/^#CFLAGS = -std/CFLAGS += -std/g' config.mk
  sed -i 's/^LDFLAGS = -g/#LDFLAGS += -g/g' config.mk
  sed -i 's/^#LDFLAGS = -s/LDFLAGS += -s/g' config.mk
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd $srcdir/$pkgname-$pkgver
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}
