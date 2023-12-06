#include "../libs/gameplay.h"
//get lucky member
int luckyMember(Account **head)
{
    int memberArray[BUFF_SIZE];
    int length = 0;
    Account *ptr = NULL;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->status == ONLINE)
            memberArray[length++] = ptr->position;
    }
    return randomNumberInArray(memberArray, length);
}
// calculator score
float calculateScore(int countPlayerPlaying, int countPlayerLoser)
{
    return 1000 / countPlayerPlaying * countPlayerLoser;
}
Help **createHelpList()
{
    Help **head = (Help **)malloc(sizeof(Help *));
    *head = NULL;
    return head;
}
// read file help.txt, get data to Help **help
void readHelpFromFile(Help **head)
{
    FILE *fin;
    fin = fopen("../data/help.txt", "r");
    char input[BUFF_SIZE];
    char stt[BUFF_SIZE];
    char key[BUFF_SIZE];
    char value[BUFF_SIZE];
    while (1)
    {
        if (feof(fin))
            break;
        fgets(input, BUFF_SIZE, fin);
        splitHelpFromFile(input, stt, key, value);
        addHelp(head, stt, key, value);
    }
    fclose(fin);
}
//create node 
Help *newHelp(char *stt, char *key, char *value)
{
    Help *new = (Help *)malloc(sizeof(Help));
    new->stt = atoi(stt);
    strcpy(new->key, key);
    new->value = atof(value);
    return new;
}
//add node with input:Help **head, char *stt, char *key, char *value
void addHelp(Help **head, char *stt, char *key, char *value)
{
    Help *new = newHelp(stt, key, value);
    Help *current = (*head);
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
/*
input: Help **head, int stt
output: delete node 
*/
void deleteHelp(Help **head, int stt)
{
    Help *tmp;
    Help *result = searchHelpByStt(head, stt);
    Help *current;
    if (*head == result)
    {
        current = *head;
        *head = (*head)->next;
    }
    else
        for (tmp = *head; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->next == result)
            {
                current = tmp->next;
                tmp->next = current->next;
            }
        }
    free(current);
}
/*
input: Help **head, int stt
output: Help *node
*/
Help *searchHelpByStt(Help **head, int stt)
{
    Help *ptr;
    for (ptr = *head; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->stt == stt)
            return ptr;
    }
    return NULL;
}