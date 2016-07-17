#include "firm.h"
#include "memory.h"
#include "cache.h"

void main(void)
{
    firmHeader *const firm = (firmHeader *)0x24000000;
    const firmSectionHeader *section = firm->section;

    //Determine the ARM11 entry to use
    vu32 *arm11 = *(vu8 *)0x08006005 ? (vu32 *)0x1FFFFFFC : (vu32 *)0x1FFFFFF8;

    //Copy FIRM sections to respective memory locations
    for(u32 i = 0; i < 4 && section[i].size; i++)
        memcpy(section[i].address, (u8 *)firm + section[i].offset, section[i].size);

    //Set ARM11 kernel entrypoint
    *arm11 = (u32)firm->arm11Entry;

    flushCaches();

    //Jump to ARM9 kernel
    ((void (*)())firm->arm9Entry)();
}