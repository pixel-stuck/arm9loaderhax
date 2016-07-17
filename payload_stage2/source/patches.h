/*
*   patches.h
*/

#pragma once

#include "types.h"

extern u32 console;

typedef struct patchData {
    u32 offset[2];
    union {
        u8 type0[8];
        u16 type1;
    } patch;
    u32 type;
} patchData;

u8 *getProcess9(u8 *pos, u32 size, u32 *process9Size);
u32 patchSignatureChecks(u8 *pos, u32 size);
u32 patchFirmlaunches(u8 *pos, u32 size);
u32 patchFirmWrites(u8 *pos, u32 size);
u32 patchFirmWriteSafe(u8 *pos, u32 size);
void applyLegacyFirmPatches(u8 *pos, u32 firmType);