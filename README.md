
# Linux Kernel Module

A simple Linux Kernel Module for Raspberry Pi 5.

The module prints "Hello World" when loaded
and "Bye Bye World" when removed.

## Build

Run `make` inside the mymod folder.

## Test

- insmod mymod.ko - Load the module
- lsmod - Check loaded modules
- rmmod mymod - Remove the module
- dmesg - View kernel messages

## Patch

The patch folder contains the changes needed
to integrate the module into the Linux Kernel.
