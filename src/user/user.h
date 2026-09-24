#pragma once

#include "../Kernel/kernel.h"
#include "../Kernel/Terminal.h"
#define MAX_USERS 30
typedef struct
{
    const char* Name;
    const char* Password;
    DWORD index;
    int IsRoot;
} User;
void Login(void);
int CreateUser(const char* Name, const char* Password, int Root);
User ReturnAtualUser();