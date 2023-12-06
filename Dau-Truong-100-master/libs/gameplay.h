#ifndef __GAMEPLAY__
#define __GAMEPLAY__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "account.h"
#include "tool.h"
#include "valid.h"

#define GAME_PLAYING 1
#define GAME_END 0

#define WIN 1
#define LOSE 0

typedef struct
{
    float score;
    int playerAnswerWrong;
    int playerPlaying;
    int status;
} Information;
typedef struct
{
    int stt;
    float score;
    char key[BUFF_SIZE];
    float value;
    struct Help *next;
} Help;
typedef enum
{
    UNAUTH,
    WAITING_PLAYER,
    WAITING_QUESTION,
    PLAYING,
    END_GAME,
} GAMEPLAY_STATUS;

int luckyMember(Account **head);                                    //get luckyPlayer
float calculateScore(int countPlayerPlaying, int countPlayerLoser); //calculator score

Help **createHelpList();                                      //make link list null
void readHelpFromFile(Help **head);                           // read file help.txt
Help *newHelp(char *stt, char *key, char *value);             // create node help
void addHelp(Help **head, char *stt, char *key, char *value); // add node help
void deleteHelp(Help **head, int stt);                        // delete node
Help *searchHelpByStt(Help **head, int stt);                  //search help by stt
#endif