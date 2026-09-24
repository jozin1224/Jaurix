#include "user.h"
User UserData[MAX_USERS];
User UserLogged;
User ReturnAtualUser()
{
    return UserLogged;
}
static DWORD index = 0;
int CreateUser(const char* Name, const char* Password, int Root)
{
    if (index > MAX_USERS)
    {
        return 101001;
    }
    User NewUser;
    NewUser.index = index;
    NewUser.IsRoot = Root;
    NewUser.Password = Password;
    NewUser.Name = Name;
    UserData[index] = NewUser;
    index++;
}
void Login(void)
{
    char Name[50];
    char Password[50];
    SetProtectedZone(0);
    printf("Jaurix Login System\n");
    printf("C is Love, C is life\n\n");
    printf("User: ");
    SetProtectedZone(1);
    while(1)
    {
        cin(Name, 50);
        SetProtectedZone(0);
        printf("Password: ");
        SetProtectedZone(1);
        cin(Password, 50);
        for (int i = 0; i < MAX_USERS; i++)
        {
            User LoginUser = UserData[i];
            if (strcmp2(Name, LoginUser.Name) == 0 && strcmp2(Password, LoginUser.Password) == 0)
            {
                printfEx("[ OK ] ", 0xA);
                printf("Logged!!\n\n");
                UserLogged = LoginUser;
                return;
            }
        }
        SetProtectedZone(0);
        printfEx("[ FALIED ] ", 0x4);
        printf("The name or password are incorrect\n");

        printf("User: ");
        SetProtectedZone(1);
    }
}