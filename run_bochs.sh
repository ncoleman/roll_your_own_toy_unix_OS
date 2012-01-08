#!/bin/bash

# run_bochs.sh
# mounts the correct loopback device, runs bochs, then unmounts.
DIRECTORY="$(readlink -e $(dirname $0))"	    # readlink gives the full path
DIRECTORY="${DIRECTORY/src/}"			    # remove src if present

sudo /sbin/losetup /dev/loop0 "$DIRECTORY"/floppy.img
sudo bochs -q -f "$DIRECTORY"/bochsrc.txt
sudo /sbin/losetup -d /dev/loop0

