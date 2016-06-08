#include "types.h"
#include "memory.h"
#include "i2c.h"
#include "fatfs/ff.h"
#include "../build/bundled.h"

#define PAYLOAD_ADDRESS 0x23F00000
#define A11_PAYLOAD_LOC 0x1FFF4C80 //Keep in mind this needs to be changed in the ld script for arm11 too
#define A11_ENTRY       0x1FFFFFF8

static void ownArm11(void)
{
    memcpy((void *)A11_PAYLOAD_LOC, arm11_bin, arm11_bin_size);
    *(vu32 *)A11_ENTRY = 1;
    *(vu32 *)0x1FFAED80 = 0xE51FF004;
    *(vu32 *)0x1FFAED84 = A11_PAYLOAD_LOC;
    *(vu8 *)0x1FFFFFF0 = 2;
    while(*(vu32 *)A11_ENTRY);
}

static void clearScreens(void)
{
    memset32((void *)0x18300000, 0, 0x46500);
    memset32((void *)0x18346500, 0, 0x38400);
}

void main(void)
{
    FATFS fs;

    f_mount(&fs, "0:", 0); //This never fails due to deferred mounting

    FIL payload;

    if(f_open(&payload, "arm9loaderhax.bin", FA_READ) == FR_OK)
    {
        ownArm11();
        clearScreens();
        i2cWriteRegister(3, 0x22, 0x2A); //Turn on backlight
        unsigned int read;
        f_read(&payload, (void *)PAYLOAD_ADDRESS, f_size(&payload), &read);
        ((void (*)())PAYLOAD_ADDRESS)();
    }

    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1);
}