#ifndef __CHECK_SIGNUP__
#define __CHECK_SIGNUP__
#include "database.h"

int Ready_Signup(int conn_sock);/*Chuan bi dang ki*/
int Signup_User(char str[1024], int conn_sock, UserType *user);/*Dang khi tai khoan moi*/
int Check_Signup_Pass_Error(int conn_sock, int *retry, UserType *user);/*Dang ki mat khau cho tai khoan moi*/

int Ready_Signup(int conn_sock){

	//if(status == unauthenticated){
		/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
		// Chuan bi cho cong viec dang ki tai khoan moi
		// Dua bien luu user hien tai ve trang thai rong
		//status = signup; /* cap nhat lai trang thai dang ki */
		//send("READY_SIGNUP");
		bytes_sent = send(conn_sock,"READY_SIGNUP",22,0);
		return Check_Send(bytes_sent); 
	//}
	//return 0;
}

int Signup_User(char str[1024], int conn_sock, UserType *user){
	char *p;
	UserType user1;	
	char string[1024];
	//if(status == signup){
		printf("Username 1:%s\n",str);
		/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
		p = strtok(str,"|");
		p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
		if(p == NULL){
			bytes_sent = send(conn_sock,"USER_ID_NOT_INVALID",22,0);
			return Check_Send(bytes_sent);
		}
		strcpy(string,p);
		if(Find_User(p, &user1)==1)
		{
			//send("USER_ID_EXISTED");
			bytes_sent = send(conn_sock,"USER_ID_NOT_INVALID",22,0);
			return Check_Send(bytes_sent);
		}
		else
		{
			//send("SIGNUP_USER_ID_OK");
			//status = signup_pass; /*chuuyen qua trang thai nhap password de dang ki*/
			strcpy(user1.username,string);
			*user=user1;
			bytes_sent = send(conn_sock,"SIGNUP_USER_ID_OK",22,0);
			return Check_Send(bytes_sent);
		}

	//}
	//return 0; 
	
}

int Signup_Pass(char str[1024], int conn_sock, int confirm, int *retry, UserType *user){
	/*truyen vao username de luu tai khoan vao csdl*/
	/*password de xac thuc tai khoan*/
	char *p;
	char confirm_password[1024];
	UserType user1;
	int stempt = *retry;
	int result;

	// if(status != enter_password|| status != confirm_pass){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }

	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	if(confirm==0)// mat khau moi nhap lan dau
	{
		if(p==NULL || strlen(p)<6){
			if(stempt<5){
				stempt++;
				*retry = stempt;
				//send("PASS_SHORT");/*mat khau client nhap vao qua ngan*/
				//return 1;
				bytes_sent = send(conn_sock,"PASS_SHORT",22,0);
				return Check_Send(bytes_sent);
			}else
			{
				*retry = 0;
				strcpy(user1.username," ");
				strcpy(user1.password," ");
				*user = user1;
				//send("BLOCK"); // nhap sai qua nhieu lan
				bytes_sent = send(conn_sock,"BLOCK",22,0);
				return 0; 
			}
		}
		else
		{
			*retry = 0;
			//send("CONFIRM_PASS"); /*gui yeu cau nhap mat khau xac thuc*/
			strcpy(user1.password,p);
			*user = user1;
			//status = confirm_pass; /*dat he thong ve trang thai xac thuc mat khau*/
			//return 1;
			bytes_sent = send(conn_sock,"CONFIRM_PASS",22,0);
			return Check_Send(bytes_sent);
		}
	}
	else
	{
		// if(status != confirm_pass){
		// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
		// 	return 0; 
		// }
		// day la mat khau confirm
		if(p!=NULL)
		{
			strcpy(confirm_password,p);
			user1 = *user;
			if(strcmp(user1.password,confirm_password)==0){
				*retry = 0;
				//send("SIGNUP_USER_SUCCESS");/*thong bao cho ben client biet la da tao thanh cong tai khoan*/
				/*Client: goi lai menu giong luc moi dang nhap vao*/
				//status = unauthenticated; /*dua he thong ve trang thai ban dau*/
				//return 1;
				printf("Chuan bi ghi vao csdl:%s\n%s\n",user1.username,user1.password);
				Update_Database(user1.username,encode(user1.password));
				bytes_sent = send(conn_sock,"SIGNUP_USER_SUCCESS",22,0);
				return Check_Send(bytes_sent);
			}	
			else{
				result = Check_Signup_Pass_Error(conn_sock, &stempt, &user1);
				*retry = stempt;
				return result;
			}
		}else
		{
			result = Check_Signup_Pass_Error(conn_sock, &stempt, &user1);
			*retry = stempt;
			return result;
		}
	}
}

int Check_Signup_Pass_Error(int conn_sock, int *retry, UserType *user){
	int stempt=*retry;
	UserType user1 = *user;
	if(stempt<5){
		stempt++;
		*retry = stempt;
		// send("CONFIRM_NOT_MATCH"); gui yeu cau ben client nhap lai mat khau xac nhan
		// return 1;
		bytes_sent = send(conn_sock,"CONFIRM_NOT_MATCH",22,0);
		return Check_Send(bytes_sent);
	}else
	{
		*retry = 0;
		strcpy(user1.username," ");
		strcpy(user1.password," ");
		*user = user1;
		//send("BLOCK"); // nhap sai qua nhieu lan
		bytes_sent = send(conn_sock,"BLOCK",22,0);
		return 0; 
	}
}

#endif