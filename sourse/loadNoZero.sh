#!/bin/sh
module="nozero"
device="nozero"
major="247"
mode="777"

/sbin/insmod ./$module.ko $* || exit 1

# remove stale nodes
rm -f /dev/${device}

mknod /dev/${device} c $major 0

chmod $mode /dev/${device}
