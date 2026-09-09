#pragma once

#include "../Inc/stdint.h"





/*
Drivers:
IO
KEYBOARD
VIDEO
*/
#include "../Driver/Io.h"
#include "../Driver/Keyboard/Driver.h"
#include "../Driver/Video/Driver.h"

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
