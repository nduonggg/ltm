#ifndef __ACCOUNT__
#define __ACCOUNT__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BLOCKED 0
#define ACTIVE 1

#define ONLINE 1
#define OFFLINE 0

typedef struct
{
    char username[30];
    char password[30];
    int position;
    int status;
    int accountStatus;
    int countSignIn;
    struct Account *next;
} Account;

Account **createLinkList();                                                                       //Init link list NULL
Account *findUserNameAccount(Account **head, char *username);                                     // find Account By Username
Account *findUserNameAccountByPosition(Account **head, int position);                             // find account by position
Account *newAccount(char *username, char *password, int accountStatus, int position);             // create node
void addAccount(Account **head, char *username, char *password, int accountStatus, int position); //add node to link list
int countMemberOnline(Account **head, int *numberPLayerArray);                                    //count member online and save position into array
void printListAccount(Account **head);                                                            // print link list

void blockAccount(Account **head, char *username);  //change status of account to block
void signinAccount(Account **head, char *username); //change status to login
#endif