#!/bin/bash
DIRECTORY="$(readlink -e $(dirname $0))"	    # readlink gives the full path
DIRECTORY="${DIRECTORY/src/}"			    # remove src if present

sudo losetup /dev/loop0 "$DIRECTORY"/floppy.img
sudo mount /dev/loop0 /mnt/floppy
sudo cp "$DIRECTORY"/src//kernel /mnt/floppy/kernel
sudo umount /dev/loop0
sudo losetup -d /dev/loop0

