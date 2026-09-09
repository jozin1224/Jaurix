#pragma once
/*

 _____                   _             _   _____             _            
|_   _|__ _ __ _ __ ___ (_)_ __   __ _| | | ____|_ __   __ _(_)_ __   ___ 
  | |/ _ \ '__| '_ ` _ \| | '_ \ / _` | | |  _| | '_ \ / _` | | '_ \ / _ \
  | |  __/ |  | | | | | | | | | | (_| | | | |___| | | | (_| | | | | |  __/
  |_|\___|_|  |_| |_| |_|_|_| |_|\__,_|_| |_____|_| |_|\__, |_|_| |_|\___|
                                                       |___/              
                        BY JOZIN1224                                                            

*/
#ifndef COMMAND_BUFFERSIZE
#define COMMAND_BUFFERSIZE 25
#endif // COMMAND_BUFFERSIZE

#include "../Driver/Video/Driver.h"
#include "../Driver/Keyboard/Driver.h"

char GetPressedKey(void);
int IsValid(char Char);
int strcmp(const char *s1, const char *s2);
VOID CommandProcesser(char* Command);
void TerminalMain(void);
