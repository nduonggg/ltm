#ifndef __CHECK_USER__
#define __CHECK_USER__

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <string.h>

int Select_Work(char string[1024], int conn_soc){  /*tuy chon ban dau giua client va server*/
	// co 2 tuy chon
	// 1: dang nhap
	// 2: tao tai khoan moi
	// 3: huy ket noi
	if(status != unauthenticated){
		/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
		return 0; 
	}
	char *p;
	p = strtok(string,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	int check = atoi(p); // lua chon cua client gui ve
	switch(check){
		case 1: // lua chon dang nhap
		{
			retry = 0;
			send("LOGIN");
			return 1; 
		}
		case 2: // lua chon dang ki
		{
			retry = 0;
			send("READY_SIGNUP");
			return 1; 
		}
		case 3:
		{
			retry = 0;
			return 0; // lua chon huy ket noi
		}
		default:
		{
			retry++;
			if(retry<5) // cho nhap sai toi da 5 lan
			{
				send("SELECT_ERROR");
				return 1;
			}
			else
				send("BLOCK");// huy ket noi
				return 0; // nhap sai qua nhieu, huy ket noi
		}
	}

}

#endif