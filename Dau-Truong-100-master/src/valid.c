#include "../libs/valid.h"

int checkValue(int value)
{
    if (value >= 0 && value <= 255)
        return 1;
    else
        return 0;
}

int checkDigit(char character)
{
    if (character >= '0' && character <= '9')
        return 1;
    else
        return 0;
}

int checkDotInString(char *string)
{
    int i, count = 0;
    if (string[0] == '.' || string[strlen(string) - 1] == '.') //at last address has dot?
        return 0;
    for (i = 0; i < strlen(string) - 1; i++)
    {
        if (string[i] == '.' && string[i + 1] == '.')
            return 0;
        if (string[i] == '.')
            count++;
    }
    if (count != 3)
        return 0;
    return 1;
}

int checkIP(char *string)
{
    int i, value = 0;
    if (checkDotInString(string))
    {
        for (i = 0; i < strlen(string); i++)
        {
            if (string[i] != '.')
            {
                if (checkDigit(string[i])) //
                {
                    value = value * 10 + string[i] - '0';
                    if (i == strlen(string) - 1)
                        if (!checkValue(value))
                            return 0;
                }
                else
                    return 0;
            }
            else
            {
                if (!checkValue(value))
                    return 0;
                value = 0;
            }
        }
        return 1;
    }
    else
        return 0;
}

int checkPort(char *port)
{
    int i, checkPort = 1;
    for (i = 0; i < strlen(port); i++)
    {
        if (port[i] < '0' || port[i] > '9')
            checkPort = 0;
    }
    if (checkPort == 0)
    {
        printf("Port invalid\n");
        return 0;
    }
    return 1;
}

int checkSpace(char *input)
{
    int i, count = 0;
    if (input[0] == ' ' || input[strlen(input) - 1] == ' ')
        return 0;
    else
    {
        for (i = 0; i < strlen(input); i++)
        {
            if (input[i] == ' ')
                count++;
        }
        if (count == 0)
            return 0;
        else
            return 1;
    }
}

int checkIPAndPort(char *ipaddr, char *port)
{
    if (checkIP(ipaddr) == 1)
        if (checkPort(port) == 1)
            return 1;
        else
            return 0;
    else
    {
        printf("IP address invalid\n");
        return 0;
    }
}