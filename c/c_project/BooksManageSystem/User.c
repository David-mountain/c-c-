#include "User.h"
#include "Configure.h"

User* createEmptyUser()
{
    User* user = calloc(1, sizeof(User));
    if (!user)
    {
        printf("createEmptyUser failed \n");
        return NULL;
    }
    return user;
}

void user_print(User* user)
{
    printf("%-10llu %-10s %d \n", user->number, user->password, user->type);
}
