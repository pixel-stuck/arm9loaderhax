/*
*   fs.h
*/

#pragma once

#include "types.h"

bool mountSd(void);
u32 fileRead(void *dest, const char *path);