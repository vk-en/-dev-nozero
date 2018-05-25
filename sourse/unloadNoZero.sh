#!/bin/sh
module="nozero"
device="nozero"
mode="777"

/sbin/rmmod ./$module.ko
rm -f /dev/${device}
