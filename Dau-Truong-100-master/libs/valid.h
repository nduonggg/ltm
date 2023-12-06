#ifndef __VALID__
#define __VALID__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 2014

#define TRUE 1
#define FALSE 0

int checkValue(int value);                    //check value
int checkDigit(char character);               //check digit
int checkDotInString(char *string);           //check dot
int checkIP(char *string);                    //check IP
int checkPort(char *port);                    //check port
int checkSpace(char *input);                  //check Space
int checkIPAndPort(char *ipaddr, char *port); //check IP and dot
#endif