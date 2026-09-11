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

/*
Kernel
*/

#include "AppsLocate.h"
void Restart();