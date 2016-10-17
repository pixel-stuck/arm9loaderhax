# arm9loaderhax for 3DS

## What this is

This is a fork of delebile's A9LH implementation, this exploit is documented [here](http://3dbrew.org/wiki/3DS_System_Flaws) and also presented [in this conference](https://media.ccc.de/v/32c3-7240-console_hacking), and provides ARM9 code execution directly at boot, exploiting a vulnerability present in the 9.6+ version of the New3DS arm9loader.  
The exploit was found by **plutoo** and **yellows8**.

## Usage

It loads an **arm9loaderhax.bin** (does not init the screens) or **arm9loaderhax_si.bin** (inits the screens) ARM9 payload from the root of the SD card or CTRNAND at address 0x23F00000.  
This means that it offers a BRAHMA-like setup, and as such has compatibility with every payload BRAHMA can run.  
You can also run code on the ARM11 by writing its memory address to 0x1FFFFFF8.

## Installation

This fork is specifically meant to work with [Safe A9LH installer](https://github.com/AuroraWright/SafeA9LHInstaller).

## Setup

Compilation needs devkitARM r45.

## Credits

Copyright 2016, Jason Dellaluce/Aurora Wright

* Normmatt for sdmmc.c and .h, and also for .ld files and the log from 3dmoo9 that provided some of the information needed to get screen init
* Christophe Devine for the SHA code
* Archshift for i2c.c and .h
* Megazig for crypto.c and .h
* Patois for original BRAHMA code
* Smealum, Derrek, Plutoo for publishing the exploit
* Yellows8 and Plutoo as the for discovering it
* bilis/b1l1s and dark_samus for the screen init code, and for fixing shutdown when no SD is inserted
* TuxSH for the screen clearing code and caches code (from Luma3DS)
* [3dbrew community](http://3dbrew.org/)

## Licensing

This code is licensed under GPLv2 or any later version, refer to the included LICENSE.txt file.