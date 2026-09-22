#include "Driver.h"
int Lines = -1;
static int cursor_row = 0;
static int cursor_col = 0;
char* video_memory = (char*)0xB8000;
const int WIDTH_SCREEN = 80;
const int HIGHT_SCREEN = 25;
static bool Scroll = true;
int protected_col = 0;
int is_protected = 0;

void SetProtectedZone(int enable) {
    is_protected = enable;
    if (enable) {
        protected_col = cursor_col;
    }
}

void MoveCursor(int x, int y) {
	uint16_t pos = y * WIDTH_SCREEN + x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}
void PrintAt(const char* str, int x, int y, unsigned char color) {
    unsigned short* video_memory = (unsigned short*)0xB8000;
    int index = (y * 80) + x;

    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[index + i] = (color << 8) | str[i];
    }
}
void EnableScroll(void)
{
    Scroll = true;
    PrintSerial("[VIDEO] Enabled Scroll\n");
}
void DisableScroll(void)
{
    Scroll = false;
    PrintSerial("[VIDEO] Disabled Scroll\n");
}
void WriteChar(char c, uint8_t color) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        Lines++;
    } 
    else if (c == '\b') {
        int limit = (is_protected) ? protected_col : 0;

        if (cursor_col > limit) {
            cursor_col--;
            int index = (cursor_row * 80 + cursor_col) * 2;
            video_memory[index] = ' ';
            video_memory[index + 1] = color;
            MoveCursor(cursor_row, cursor_col);
        }
        else if (!is_protected && cursor_row > 0) {
            cursor_row--;
            cursor_col = 79;
        }
    }

    else {
        int index = (cursor_row * 80 + cursor_col) * 2;
        video_memory[index] = c;
        video_memory[index + 1] = color;
        cursor_col++;
    }

    if (cursor_col >= 80) {
        cursor_col = 0;
        cursor_row++;
    }

    if (cursor_row >= 25) {
        cursor_row = 0;
    }
    if (Lines >= 24)
    {
        if (Scroll)
        {
            Clean();
        }
        Lines = 0;
    }
    MoveCursor(cursor_col, cursor_row);
}        


void printf(const char* message) {
    if (message == nullptr) {
        return;
    }
    for (int i = 0; message[i] != '\0'; ++i) {
        WriteChar(message[i], 0x07);
    }
    PrintSerial("[VIDEO] Show Text \"");
    PrintSerial(message);
    PrintSerial("\"\n");
}

void printfEx(const char* message, uint8_t Color) {
    if (message == nullptr) {
        return;
    }
    for (int i = 0; message[i] != '\0'; ++i) {
        WriteChar(message[i], Color);
    }
    PrintSerial("[VIDEO] Show Text with Color \"");
    PrintSerial(message);
    PrintSerial("\"\n");
}

void Clean() {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x07;
    }
    cursor_row = 0;
    cursor_col = 0;
    Lines = 0;
    PrintSerial("[VIDEO] Clean!!\n");
}
