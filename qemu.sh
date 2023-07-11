#!/bin/sh
set -e

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom banshee.iso \
  -serial file:serial.log
