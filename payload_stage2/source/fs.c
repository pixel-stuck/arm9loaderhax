/*
*   fs.c
*/

#include "fs.h"
#include "fatfs/ff.h"

static FATFS fs;

bool mountSd(void)
{
    return f_mount(&fs, "0:", 1) == FR_OK;
}

u32 fileRead(void *dest, const char *path)
{
    FIL file;
    u32 ret = 0;

    if(f_open(&file, path, FA_READ) == FR_OK)
    {
        f_read(&file, dest, f_size(&file), (unsigned int *)&ret);
        f_close(&file);
    }

    return ret;
}