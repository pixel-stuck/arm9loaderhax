/*
*   main.c
*/

#include "types.h"
#include "sdmmc.h"
#include "cache.h"

void main(void)
{
    //Initialize sdcard and nand
    sdmmc_sdcard_init();

    sdmmc_nand_readsectors(0x5C000, 22, (u8 *)0x08006000);

    flushCaches();

    //Jump to secondary payload
    ((void (*)())0x08006000)();
}