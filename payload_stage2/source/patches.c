/*
*   patches.c
*/

#include "patches.h"
#include "memory.h"
#include "../build/bundled.h"

u8 *getProcess9(u8 *pos, u32 size, u32 *process9Size)
{
    u8 *off = memsearch(pos, "ess9", size, 4);

    *process9Size = *(u32 *)(off - 0x60) * 0x200;

    //Process9 code offset (start of NCCH + ExeFS offset + ExeFS header size)
    return off - 0x204 + (*(u32 *)(off - 0x64) * 0x200) + 0x200;
}

u32 patchSignatureChecks(u8 *pos, u32 size)
{
    const u16 sigPatch[2] = {0x2000, 0x4770};

    //Look for signature checks
    const u8 pattern[] = {0xC0, 0x1C, 0x76, 0xE7},
             pattern2[] = {0xB5, 0x22, 0x4D, 0x0C};

    u16 *off = (u16 *)memsearch(pos, pattern, size, 4);
    u8 *off2Tmp = memsearch(pos, pattern2, size, 4);

    if(off == NULL || off2Tmp == NULL) return 1;
    
    u16 *off2 = (u16 *)(off2Tmp - 1);

    *off = sigPatch[0];
    off2[0] = sigPatch[0];
    off2[1] = sigPatch[1];

    return 0;
}

u32 patchFirmlaunches(u8 *pos, u32 size)
{
    //Look for firmlaunch code
    const u8 pattern[] = {0xDE, 0x1F, 0x8D, 0xE2};

    u8 *offTmp = memsearch(pos, pattern, size, 4);

    if(offTmp == NULL) return 1;

    u8 *off = offTmp - 0x10;

    //Copy firmlaunch code
    memcpy(off, reboot_bin, reboot_bin_size);

    //Copy itcm stub
    memcpy((void *)0x1FFF900, itcmstub_bin, itcmstub_bin_size);

    return 0;
}

u32 patchFirmWrites(u8 *pos, u32 size)
{
    const u16 writeBlock[2] = {0x2000, 0x46C0};

    //Look for FIRM writing code
    u8 *const off1 = memsearch(pos, "exe:", size, 4);

    if(off1 == NULL) return 1;

    const u8 pattern[] = {0x00, 0x28, 0x01, 0xDA};

    u16 *off2 = (u16 *)memsearch(off1 - 0x100, pattern, 0x100, 4);

    if(off2 == NULL) return 1;

    off2[0] = writeBlock[0];
    off2[1] = writeBlock[1];

    return 0;
}

u32 patchFirmWriteSafe(u8 *pos, u32 size)
{
    const u16 writeBlockSafe[2] = {0x2400, 0xE01D};

    //Look for FIRM writing code
    const u8 pattern[] = {0x04, 0x1E, 0x1D, 0xDB};

    u16 *off = (u16 *)memsearch(pos, pattern, size, 4);

    if(off == NULL) return 1;

    off[0] = writeBlockSafe[0];
    off[1] = writeBlockSafe[1];

    return 0;
}

void applyLegacyFirmPatches(u8 *pos, u32 firmType)
{
    const patchData twlPatches[] = {
        {{0x1650C0, 0x165D64}, {{ 6, 0x00, 0x20, 0x4E, 0xB0, 0x70, 0xBD }}, 0},
        {{0x173A0E, 0x17474A}, { .type1 = 0x2001 }, 1},
        {{0x174802, 0x17553E}, { .type1 = 0x2000 }, 2},
        {{0x174964, 0x1756A0}, { .type1 = 0x2000 }, 2},
        {{0x174D52, 0x175A8E}, { .type1 = 0x2001 }, 2},
        {{0x174D5E, 0x175A9A}, { .type1 = 0x2001 }, 2},
        {{0x174D6A, 0x175AA6}, { .type1 = 0x2001 }, 2},
        {{0x174E56, 0x175B92}, { .type1 = 0x2001 }, 1},
        {{0x174E58, 0x175B94}, { .type1 = 0x4770 }, 1}
    },
    agbPatches[] = {
        {{0x9D2A8, 0x9DF64}, {{ 6, 0x00, 0x20, 0x4E, 0xB0, 0x70, 0xBD }}, 0},
        {{0xD7A12, 0xD8B8A}, { .type1 = 0xEF26 }, 1}
    };

    /* Calculate the amount of patches to apply. Only count the boot screen patch for AGB_FIRM
       if the matching option was enabled (keep it as last) */
    u32 numPatches = firmType == 1 ? (sizeof(twlPatches) / sizeof(patchData)) :
                                     (sizeof(agbPatches) / sizeof(patchData));
    const patchData *patches = firmType == 1 ? twlPatches : agbPatches;

    //Patch
    for(u32 i = 0; i < numPatches; i++)
    {
        switch(patches[i].type)
        {
            case 0:
                memcpy(pos + patches[i].offset[console], patches[i].patch.type0 + 1, patches[i].patch.type0[0]);
                break;
            case 2:
                *(u16 *)(pos + patches[i].offset[console] + 2) = 0;
            case 1:
                *(u16 *)(pos + patches[i].offset[console]) = patches[i].patch.type1;
                break;
        }
    }
}