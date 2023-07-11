#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

if [ ! -z $(which grub2-mkrescue)]; then
	MKRESCUE=grub2-mkrescue
else
	MKRESCUE=grub-mkrescue
fi

cp sysroot/boot/banshee.kernel isodir/boot/banshee.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "banshee" {
	multiboot /boot/banshee.kernel
}
EOF
$MKRESCUE -o banshee.iso isodir
