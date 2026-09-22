#pragma once

#include "../../Kernel/kernel.h"
#define PORT 0x3F8
int InitSerial();
int IsEmpty();
void WriteSerial(char c);
void PrintSerial(const char* str);
