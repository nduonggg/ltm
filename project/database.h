#ifndef __DATABASE__
#define __DATABASE__
#include"my_type.h"

char* encode(char* str);/*ma hoa mat khau*/
char* decode(char* str);/*giai ma mat khau*/
int Find_User(char *s1, UserType *user);/*tim kiem username trong database*/
void Update_Database(char user[1024],char pass[1024]);/*Update du lieu cua tai khoan moi*/


char* encode(char* str) {
   int i = 0;
 
   while (str[i] != '\0') {
      str[i] = str[i] - 30;  // Subtract 30 From Charcter
      i++;
   }
   return (str);
}

char* decode(char* str) {
   int i = 0;
 
   while (str[i] != '\0') {
      str[i] = str[i] + 30;  // Subtract 30 From Charcter
      i++;
   }
   return (str);
}

int Find_User(char *s1, UserType *user)
{
	// TIM KIEM USER TRONG DATABASE
	// Cap nhat mat khau va tai khoan  vao trong bien user
	// password luu lai trong bien nay la password da duoc giai ma
	char s[80];
	char username1[80];
	char *p; 
	FILE *f1;
	if((f1=fopen("password.txt","r+"))==NULL)
    {
      printf("File server error!!\n");
      return 0;
    }
	while(fgets(s,80,f1)!=NULL)
	{
		p=strtok(s,"\t"); //user va pass phan cach boi dau tab
		strcpy(username1,p);
		if(strcmp(s1,username1)==0)
		{
			strcpy(user->username, s1); /*luu lai ten dang nhap cua nguoi dung*/
			p=strtok(NULL,"\n");
			strcpy(user->password,decode(p)); // tim kiem lai mat khau
			return 1;
		}
	}
	fclose(f1);
	return 0;
}

void Update_Database(char user[1024],char pass[1024]){
	FILE *f1;
	f1=fopen("password.txt","a+");
	fputs(user,f1);
	fputs("\t",f1);
	fputs(pass,f1);
	fputs("\n",f1);
	fclose(f1);
}



#endif