#include "../libs/account.h"
//Init link list
Account **createLinkList()
{
    Account **head = (Account **)malloc(sizeof(Account *));
    *head = NULL;

    return head;
}
//find account by username
Account *findUserNameAccount(Account **head, char *username)
{
    Account *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp(ptr->username, username) == 0)
            return ptr;
    }
    return NULL;
}
//create node
Account *newAccount(char *username, char *password, int accountStatus, int position)
{
    Account *new = (Account *)malloc(sizeof(Account));
    strcpy(new->username, username);
    strcpy(new->password, password);
    new->accountStatus = accountStatus;
    new->position = position;
    new->status = OFFLINE;
    new->countSignIn = 0;
    new->next = NULL;
    return new;
}
//add node
void addAccount(Account **head, char *username, char *password, int accountStatus, int position)
{
    Account *new = newAccount(username, password, accountStatus, position);
    Account *current = (*head);

    if (*head == NULL)
    {
        (*head) = new;
    }
    else
    {
        while (current->next != NULL)
            current = current->next;
        current->next = new;
    }
}
//printf all account
void printListAccount(Account **head)
{
    Account *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        printf("STT: %d\n", ptr->position);
        printf("Username: %s\n", ptr->username);
        printf("Pass: %s\n", ptr->password);
        printf("Account: %s\n", ptr->accountStatus == ACTIVE ? "Active" : "Blocked");
        printf("Status : %s\n", ptr->status == ONLINE ? "Online" : "Offline");
        printf("Count wrong password: %d\n", ptr->countSignIn);
        printf("\n");
    }
}

void blockAccount(Account **head, char *username)
{
    Account *ptr = findUserNameAccount(head, username);
    ptr->accountStatus = BLOCKED;
}
void signinAccount(Account **head, char *username)
{
    Account *ptr = findUserNameAccount(head, username);
    ptr->status = ONLINE;
}

Account *findUserNameAccountByPosition(Account **head, int position)
{
    Account *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->position == position)
            return ptr;
    }
    return NULL;
}
/*
input: Account **head, int *numberPlayerArray
output: number of member online and array playerNumber
*/
int countMemberOnline(Account **head, int *numberPlayerArray)
{
    int members = 0;
    Account *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->status == ONLINE)
        {
            numberPlayerArray[members++] = ptr->position;
        }
    }
    return members;
}