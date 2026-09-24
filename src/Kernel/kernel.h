#pragma once

#include "../Inc/stdint.h"

/*
Drivers:
IO
KEYBOARD
VIDEO
SERIAL
*/
#include "../Driver/Io.h"
#include "../Driver/Keyboard/Driver.h"
#include "../Driver/Video/Driver.h"
#include "../Driver/Serial/Driver.h"

/*
CPU:
IDT
*/

#include "../cpu/idt.h"
/*
ASM fuinctions
*/
#include "AsmToC.h"

/*
Defines
*/
#define VOID void
#define INFINITY (*(const float *)(const unsigned int []){ 0x7F800000 })
/*
Kernel
*/
#include "../user/user.h"
#include "AppsLocate.h"
void Restart();