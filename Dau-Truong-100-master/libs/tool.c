#include "../libs/tool.h"

void splitMessage(char *input, char *code, char *data)
{
	int i, codeLength = 0, dataLength = 0;
	for (i = 0; input[i] != ' '; i++)
	{
		code[codeLength++] = input[i];
	}
	code[codeLength] = '\0';
	i++;
	for (i; i < strlen(input); i++)
	{
		data[dataLength++] = input[i];
	}
	data[dataLength] = '\0';
}

void splitMessageData(char *input, char *username, char *password)
{
	int i, usernameLength = 0, passwordLength = 0;
	for (i = 0; input[i] != ' '; i++)
	{
		username[usernameLength++] = input[i];
	}
	username[usernameLength] = '\0';
	i++;
	for (i; i < strlen(input); i++)
	{
		password[passwordLength++] = input[i];
	}
	password[passwordLength] = '\0';
}

void splitQuestionFromFile(char *input, char *stt, char *level, char *question, char *answer1, char *answer2, char *answer3, char *answer4, char *answerTrue)
{
	int sttLength = 0;
	int levelLength = 0;
	int questionLength = 0;
	int answer1Length = 0;
	int answer2Length = 0;
	int answer3Length = 0;
	int answer4Length = 0;
	int answerTrueLength = 0;
	int i;
	//split stt
	for (i = 0; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		stt[sttLength++] = input[i];
	}
	i++;
	stt[sttLength] = '\0';
	//split level
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		level[levelLength++] = input[i];
	}
	i++;
	level[levelLength] = '\0';
	//split question
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		question[questionLength++] = input[i];
	}
	i++;
	question[questionLength] = '\0';
	//split answer1
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answer1[answer1Length++] = input[i];
	}
	i++;
	answer1[answer1Length] = '\0';
	//split answer2
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answer2[answer2Length++] = input[i];
	}
	i++;
	answer2[answer2Length] = '\0';
	//split answer3
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answer3[answer3Length++] = input[i];
	}
	i++;
	answer3[answer3Length] = '\0';
	//split answer4
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		answer4[answer4Length++] = input[i];
	}
	i++;
	answer4[answer4Length] = '\0';
	//split answer true
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '\n')
			break;
		answerTrue[answerTrueLength++] = input[i];
	}
	answerTrue[answerTrueLength] = '\0';
}
void splitHelpFromFile(char *input, char *stt, char *key, char *value)
{
	int sttLength = 0;
	int keyLength = 0;
	int valueLength = 0;
	int i;
	//split stt
	for (i = 0; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		stt[sttLength++] = input[i];
	}
	i++;
	stt[sttLength] = '\0';
	//split key
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		key[keyLength++] = input[i];
	}
	i++;
	key[keyLength] = '\0';
	//split value
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '\n')
			break;
		value[valueLength++] = input[i];
	}
	value[valueLength] = '\0';
}
void splitAccountFromFile(char *input, char *position, char *username, char *password, char *account, char *score)
{
	int positionLentgh = 0;
	int usernameLength = 0;
	int passwordLength = 0;
	int accountLength = 0;
	int scoreLength = 0;
	int i;
	//split position
	for (i = 0; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		position[positionLentgh++] = input[i];
	}
	i++;
	position[positionLentgh] = '\0';
	//split username
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		username[usernameLength++] = input[i];
	}
	i++;
	username[usernameLength] = '\0';
	//split password
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		password[passwordLength++] = input[i];
	}
	i++;
	password[passwordLength] = '\0';
	//split account
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '|')
			break;
		account[accountLength++] = input[i];
	}
	i++;
	account[accountLength] = '\0';
	//split score
	for (i; i < strlen(input); i++)
	{
		if (input[i] == '\n')
			break;
		score[scoreLength++] = input[i];
	}
	score[scoreLength] = '\0';
}
int randomNumberInArray(int *numberArray, int length)
{
	srand(time(NULL));
	return numberArray[rand() % (length-1) + 1];
}
