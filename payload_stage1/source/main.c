#include "common.h"
#include "sdmmc.h"
#include "i2c.h"

int main()
{
    // Initialize sdcard and nand
    *(vu32*)0x10000020 = 0;
    *(vu32*)0x10000020 = 0x340;
    sdmmc_sdcard_init();

    if(i2cReadRegister(I2C_DEV_MCU, 0x10) & 0x4) //if home button is pressed
    {
        //Jump to alternate stage2
        sdmmc_nand_readsectors(0x5A000, 0x20, (u8*)0x08006000);
    }
    else
    {
        //jump to normal stage2
        sdmmc_nand_readsectors(0x5C000, 0x20, (u8*)0x08006000);
    }
    
    // Jump to secondary payload
    ((void (*)())0x08006000)();
    return 0;
}

