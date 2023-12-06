#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../libs/tool.h"
#include "../libs/valid.h"
#include "../libs/gameplay.h"
#include "../libs/question.h"
typedef enum
{
    USER,
    PASS,
    REGISTER,
    LOGOUT,
    CHECK,
    CHOOSE_ANWSER,
    TOPIC_LEVEL,
    HELP,
    INFORMATION,
} OPCODE;

typedef enum
{
    NOT_LOGGED_IN,
    UNAUTHENTICATE,
    AUTHENTICATED,
} PHASE;

typedef enum
{
    SYNTAX_ERROR = 02,
    INVALID_OPERATION = 03,
    USER_IS_NOT_SIGNIN = 04,
    GAME_IS_PLAYING_DONT_LOG_IN = 05,

    USER_NAME_FOUND = 11,
    USER_NAME_NOT_FOUND = 12,
    USER_NAME_BLOCKED = 13,
    USER_NAME_IS_SIGNIN = 14,

    PASSWORD_CORRECT = 21,
    PASSWORD_INCORRECT = 22,
    PASSWORD_INCORRECT_THREE_TIMES = 23,
    PASSWORD_CORRECT_BUT_ACCOUNT_IS_SIGNINED_IN_ORTHER_CLIENT = 24,

    LOGOUT_SUCCESS = 31,

    REGISTER_SUCCESSFULL = 41,
    REGISTER_USERNAME_EXISTED = 42,

    ANSWER_IS_CORRECT = 51,
    ANSWER_IS_INCORRECT = 52,
    ANSWER_IS_INVALID = 53,

    USER_USED_HINT_SUCCESS = 61,
    USER_USED_HINT_FAIL = 62,

    TOPIC_USER_CHOOSE_LEVEL = 71,
    TOPIC_TYPE_INVALID = 72,
    TOPIC_USER_DONT_CHOOSE_LEVEL = 73,

    INFORMATION_SUCCESS = 81,
    INFORMATION_ORTHER_PLAYER_ANSWERING = 82,

    GAME_READY = 91,
    GAME_NOT_READY = 92,
    GAME_END_WIN = 93,

} MESSAGE_STATUS;

typedef struct
{
    OPCODE code;
    char message[50];
} Request;

typedef struct
{
    GAMEPLAY_STATUS status;
    MESSAGE_STATUS code;
    char message[50];
    char data[50];
} Response;
//core function
int receiveRequest(int socket, Request *buff, int size, int flags);
int sendRequest(int socket, Request *buff, int size, int flags);

int sendMessage(int socket, Response *msg, int size, int flags);
int receiveMessage(int socket, Response *msg, int size, int flags);

// set message response
void setMessageResponse(Response *msg);
void readMessageResponse(Response *msg);

//set opcode request
void setOpcodeRequest(Request *request, char *input);

//send question
int sendQuestion(int socket, Question *question, int size, int flags);
int receiveQuestion(int socket, Question *question, int size, int flags);
//send information
int sendInformation(int socket, Information *infor, int size, int flags);
int receiveInformation(int socket, Information *infor, int size, int flags);
//request get
void requestGet(int socket);
void requestLogout(int socket, char *username);
void requestCheckInformation(int socket);
void requestGetHelp(int socket);
#endif