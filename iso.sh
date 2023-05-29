#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/banshee.kernel isodir/boot/banshee.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "banshee" {
	multiboot /boot/banshee.kernel
}
EOF
grub2-mkrescue -o banshee.iso isodir
