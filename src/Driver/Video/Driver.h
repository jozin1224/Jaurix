#include "../../Kernel/kernel.h"

void printf(const char* message);
void printfEx(const char* message, uint8_t Color);
void Clean();
void mover_cursor(int x, int y);
void WriteChar(char c, uint8_t color);
void PrintAt(const char* str, int x, int y, unsigned char color);
void EnableScroll(void);
void DisableScroll(void);
void SetProtectedZone(int enable);