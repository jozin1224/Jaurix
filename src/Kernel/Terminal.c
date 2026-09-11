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
#include "Terminal.h"

char GetPressedKey(void);
int IsValid(char Char);

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return !(*(const unsigned char*)s1 - *(const unsigned char*)s2);
}
void cin(char* buffer, int bufferSize) {     
    int i = 0;      
    while(1)     
    {         
        char Key = GetPressedKey();         
        if (IsValid(Key))         
        {             
            WriteChar(Key, 0xF);                          
            if (Key == '\n')             
            {                 
                buffer[i] = '\0';
                return;
            }             
            else if (i < bufferSize - 1)             
            {                 
                buffer[i] = Key;                 
                i++;             
            }         
        }     
    } 
}

VOID CommandProcesser(char* Command)
{
    PrintSerial("[TERMIANL] Command = ");
    PrintSerial(Command);
    PrintSerial("\n");
    if (strcmp(Command, "clear"))
    {
        Clean();
        return;
    }
    else if (strcmp(Command, "Note"))
    {
        NoteMain();
        printf("\n");
        EnableScroll();
        return;
    }
    else if (strcmp(Command, "osver"))
    {
        printf("Jaurix Ver 0.01\n");
        printf("This operating system doesn't run Doom :(\n");
        return;
    }
    else if(strcmp(Command, "echo"))
    {
        char Buffer[50];
        printf("Say Message: ");
        cin(Buffer, 50);
        printf("\n");
        printf(Buffer);
        printf("\n");
        return;
    }
    else if(strcmp(Command, "TerminalEngine"))
    {
        printf("Termial Engine 1.0.0 by Jozin1224");
        printf("\n");
        return;
    }
    else if(strcmp(Command, "echoSerial"))
    {
        char Buffer[50];
        printf("Say Message: ");
        cin(Buffer, 50);
        PrintSerial("\n");
        PrintSerial(Buffer);
        PrintSerial("\n");
        return;
    }
    else if (strcmp(Command, "reboot")) { 
        char Buffer[2]; 
        printf("You Really Want Reboot???\n"); 
        
        while(1) { 
            printf("[Y/N]: "); 
            cin(Buffer, sizeof(Buffer)); 
            if (strcmp(Buffer, "y") || strcmp(Buffer, "n") ) { 
                break; 
            } 
        } 
        
        if (strcmp(Buffer, "n")) { 
            return; 
        } 
        
        Restart(); 
    }
    if (strcmp(Command, "help"))
    {
        printf("Cool commands:\n\nclear: Clear screen\nTerminalEngine: Show terminal engine info\nosver: Show Jaurix Infos\necho: Show Cool Texts\necho: Show Cool Texts on Serial\nreboot: reboot\nNote: A Basic Note app to type things\n");
        return;
    }
    else if (Command[0] == '\0')
    {
        return;
    }
    else
    {
        printf("\"");
        printf(Command);
        printf("\" Is not a valid command\n");
        PrintSerial("[TERMINAL] INVALID COMMAND\n");
        return;
    }
}

void TerminalMain(void)
{
    printfEx("[ OK ]", 0x0A);
    printfEx(" Terminal Loaded\n", 0x07);
    SetProtectedZone(0);
    printfEx("jaurix@jaurix#> ", 0x0A);
    SetProtectedZone(1);
    char Buffer[COMMAND_BUFFERSIZE] = {0};
    int i = 0;

    while(1)
    {
        char Key = GetPressedKey();
        if (IsValid(Key)) {
            WriteChar(Key, 0xF);
            
            if (Key == '\n') {
                Buffer[i] = '\0';
                CommandProcesser(Buffer);
                Buffer[0] = '\0';
                i = 0;
                SetProtectedZone(0);
                printfEx("jaurix@jaurix#> ", 0x0A);
                SetProtectedZone(1);
            } 
            else if (Key == '\b') {
                if (i > 0) {
                    i--;
                    Buffer[i] = '\0';
                }
            } 
            else if (i < COMMAND_BUFFERSIZE - 1) {
                Buffer[i] = Key;
                i++;
            }
        }
    }
}
