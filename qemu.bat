@echo off

qemu-system-%HOST%.exe -cdrom banshee.iso -serial file:serial.log
