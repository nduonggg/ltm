// #ifndef __QUESTION__
// #define __QUESTION__
// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>

// #include "valid.h"
// #include "tool.h"
// typedef enum
// {
//     A,
//     B,
//     C,
//     D,
//     E,
// } LIST_ANSWER;

// typedef enum
// {
//     EASY,
//     NORMAL,
//     HARD,
//     ORTHER,
// } LEVEL;

// typedef struct
// {
//     int stt;
//     char question[BUFF_SIZE];
//     char answer1[BUFF_SIZE];
//     char answer2[BUFF_SIZE];
//     char answer3[BUFF_SIZE];
//     char answer4[BUFF_SIZE];
//     LEVEL level;
//     LIST_ANSWER true_ans;
//     struct Question *next;
// } Question;

// Question **createQuestionList();                                                                                                                         //Init link list null
// void readQuestionFromFile(Question **head);                                                                                                              //read file to link list
// Question *newQuestion(char *stt, char *level, char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *answerTrue);             // create new node
// void addQuestion(Question **head, char *stt, char *level, char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *answerTrue); //add node
// void printListQuestion(Question **head);                                                                                                                 // printf list question
// void deleteQuestion(Question **head, int stt);                                                                                                           //delete node question
// //search
// Question *searchQuestionByStt(Question **head, int stt);                   //search bu stt
// int searchQuestionByLevel(Question **head, LEVEL level, int *numberArray); //search by level
// //check answer
// int checkAnswer(LIST_ANSWER node, LIST_ANSWER ans); //check answer

// LIST_ANSWER convertListAnswer(char *input); // convert string to enum
// LEVEL convertLevel(char *input);            //convert string to enum
// #endif