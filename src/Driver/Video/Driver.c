#include "Driver.h"
int Lines = -1;
static int cursor_row = 0;
static int cursor_col = 0;
char* video_memory = (char*)0xB8000;
const int WIDTH_SCREEN = 80;
const int HIGHT_SCREEN = 25;
void MoveCursor(int x, int y) {
	uint16_t pos = y * WIDTH_SCREEN + x;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void WriteChar(char c, uint8_t color) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        Lines++;
    } 
    else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
            int index = (cursor_row * 80 + cursor_col) * 2;
            video_memory[index] = ' ';
            video_memory[index + 1] = color;
            MoveCursor(cursor_row, cursor_col);
        } 
        else if (cursor_row > 0) {
            cursor_row--;
            cursor_col = 79;
            int index = (cursor_row * 80 + cursor_col) * 2;
            video_memory[index] = ' ';
            video_memory[index + 1] = color;
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
    MoveCursor(cursor_col, cursor_row);
}        


void printf(const char* message) {
    if (message == nullptr) {
        return;
    }
    for (int i = 0; message[i] != '\0'; ++i) {
        WriteChar(message[i], 0x07);
    }
}

void printfEx(const char* message, uint8_t Color) {
    if (message == nullptr) {
        return;
    }
    for (int i = 0; message[i] != '\0'; ++i) {
        WriteChar(message[i], Color);
    }
}

void Clean() {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x07;
    }
    cursor_row = 0;
    cursor_col = 0;
}
