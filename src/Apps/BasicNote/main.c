#include "Note.h"
int NoteMain()
{
    Clean();
    DisableScroll();
    PrintSerial("[BASIC NOTE] Loaded!!\n");
    PrintAt("JOZIN BASIC NOTE 1.0        TO EXIT PRES CTRL + C                               ", 0, 0, 0x70);
    printf("\n");
    while(1)
    {
        PrintAt("JOZIN BASIC NOTE 1.0        TO EXIT PRES CTRL + C                               ", 0, 0, 0x70);
        CHAR Key = GetPressedKey();
        if (ctrl && Key == 'c')
        {
            return 0;
        }
        if (IsValid(Key))
        {
            WriteChar(Key, 0xF);
        }
    }
}