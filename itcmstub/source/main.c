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

    sdmmc_nand_readsectors(0x5C000, 50, (u8 *)0x08006000);

    //Copy firmlaunched FIRM data
     *(vu32 *)0x08006004 = *(vu32 *)0x1FFF904;
     *(vu32 *)0x08006008 = *(vu32 *)0x1FFF908;

    flushCaches();
    
    //Jump to secondary payload
    ((void (*)())0x08006000)();
}