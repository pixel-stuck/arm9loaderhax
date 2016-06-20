# arm9loaderhax for 3DS

## What this is

This is a fork of delebile's A9LH implementation, this exploit is documented [here](http://3dbrew.org/wiki/3DS_System_Flaws) and also presented [in this conference](https://media.ccc.de/v/32c3-7240-console_hacking), and provides ARM9 code execution directly at boot, exploiting a vulnerability present in the 9.6+ version of the New3DS arm9loader.  
It has no screen init and is as minimal as it can be.  
The exploit was found by **plutoo** and **yellows8**.

## Usage

It loads an **arm9loaderhax.bin** arm9 payload from the root of the sdcard at address 0x23F00000.  
This means that it offers a BRAHMA-like setup, and as such has compatibility with every payload BRAHMA can run; you can also perform a firmlaunch by writing the ARM11 kernel entrypoint at address 0x1FFFFFF8.

## Installation

This fork is specifically designed to work with [Safe A9LH installer](https://github.com/AuroraWright/SafeA9LHInstaller).

## Setup

Compilation needs devkitARM r45.

## Credits

Copyright 2016, Jason Dellaluce

sdmmc.c & sdmmc.h originally written by Normmatt

Licensed under GPLv2 or any later version, refer to the license.txt file included.

* Smealum and contributors for libctru
* Normmatt for sdmmc.c and .h, and also for .ld files and the log from 3dmoo9 that provided us with some of the information needed to get screen init
* Christophe Devine for the SHA codes
* Archshift for i2c.c and .h
* Megazig for crypto.c and .h
* Patois for original BRAHMA code
* Smealum, Derrek, Plutoo for publishing the exploit
* Yellows8 and Plutoo as ideators of it
* [3dbrew community](http://3dbrew.org/)
* bilis/b1l1s and dark_samus for the arm11 code, and for fixing no-SD shutdown