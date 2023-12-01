#include "my_type.h"
#include "ai.h"
#include "server.h"
#include "database.h"
#include "check_login.h"
#include "check_signup.h"
#include "status_game.h"
#include "check_game.h"
#include "interface.h"
#include <errno.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#define PORT 5500
#define BACKLOG 20

UserType user; // luu thong tin cua user
StatusType status = unauthenticated; // trang thai he thong
PlayStatus play_status = not_play; // trang thai cua game
ChessStatus chess_status;
int data[9][9]; //  du lieu ban co
char *username;
char password[1024]; 
int retry = 0; // dem so lan nhap sai
int listen_sock, conn_sock; /* file descriptors */
char recv_data[1024];
int bytes_sent, bytes_received;
struct sockaddr_in server; /* server's address information */
struct sockaddr_in client; /* client's address information */
pid_t pid;
int sin_size;
FILE *f1;
int color; // luu mau quan co ben phia client
int *chess[9]; // ban co 
char file_name[1024]; /*luu thong tin cua */
char stemp[1024];
char ip_address[1024];
FILE *store_run;
char *server_run;
char *client_run;
int flag;

void sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("[ForkingServer] Child %d terminated\n",pid);
}
int Check_Mess(char recv_data[1024], int conn_soc){
	char *p;
	char str[1024];
	strcpy(str,recv_data);
	p = strtok(str,"|");
	if(strcmp(p,"SELECT_WORK")==0){
		// lua chon cong viec khi moi vao
		return(Select_Work(recv_data, conn_soc));
	}
	if(strcmp(p,"LOGIN_USER")==0){
		// tim user trong he thong
		return Check_User(recv_data, conn_soc, username, &user); 
	}
	if(strcmp(p,"LOGIN_PASS")==0){
		// kiem tra pass co trung khop hay khong
		printf("Login: %s\n", user.username);
		return Check_Login_Pass(recv_data, conn_soc, user, &retry);
	}
	if(strcmp(p,"SIGNUP")==0){
		// chuan bi cho viec tao tai khoan moi
		printf("Dang ki tai khoan\n");
		return Ready_Signup(conn_soc);
	}
	if(strcmp(p,"SIGNUP_USER")==0){
		// kiem tra ten tai khoan dang ky moi
		return Signup_User(recv_data, conn_soc, &user);
	}
	if(strcmp(p,"SIGNUP_PASS")==0){
		//	tao mat khau cho tai khoan dang ki moi
		return Signup_Pass(recv_data, conn_soc, 0, &retry, &user);
	}
	if(strcmp(p,"CONFIRM_PASS")==0){
		// xac nhan lai mat khau dang ki
		printf("Vao confirm roi, pass la:%s\n", username);
		return Signup_Pass(recv_data, conn_soc, 1, &retry, &user);
	}
	if(strcmp(p,"LOGOUT")==0){
		// nguoi dung muon thoat dang nhap
		// suy tinh xem co nen bat nguoi dung truyen user muon thoat khong nhi
		return Check_Logout(recv_data,conn_soc);
	}
	if(strcmp(p,"START_GAME")==0){
		// nhan yeu cau bat dau tro choi cua nguoi dung
		/*khoi tao ban co*/
		printf("IP adress %s\n",inet_ntoa(client.sin_addr) ); /* prints client's IP */
		for(int i = 0; i < 9; i++)
   	    chess[i] = (int*)malloc(9*sizeof(int));
   		make_chess(chess);
   		chess_status.king_x_white = 7;
   		chess_status.king_y_white = 4;
   		chess_status.king_x_black = 0;
   		chess_status.king_y_black = 4;
		return Start_Game(conn_soc);
	}
	if(strcmp(p,"COLOR")==0){
		// nguoi choi da chon mau quan co, bat dau tro choi
		char stemp[1024];
		char stemp2[1024];
		//strcpy(stemp,scan_time()); /*lay thoi gian he thong*/
		char *p;
	    time_t rawtime; 
	    // struct tm *timeinfo; 
	    time(&rawtime); 
	    // timeinfo = localtime(&rawtime); 
	    strcpy(stemp,asctime(localtime(&rawtime)));
		strcpy(stemp2,stemp);
		strcpy(file_name,make_name_file(stemp,0)); /*Tao file luu thong tin tran dau*/
		if((store_run = fopen(file_name,"w+"))==NULL)
		    {
		      printf("**ERROR** Open file error.\n");
			      return 0;
		    }
	    else{
	    	fprintf(store_run,"Start time: %s",stemp2);
	    	fprintf(store_run,"Your IP: %s\n",ip_address);
	    	int a = Check_Color(recv_data, conn_soc, chess, &color, &chess_status);
	    	printf("-----------\n");
	    	printf("%d %d %d %d\n",chess_status.status_rock_black1,chess_status.status_rock_black2,chess_status.status_rock_white1,chess_status.status_rock_white2);
	    	printf("------------\n");
	    	//if(color == 2) printf("124: %s\n",server_run);
	    	if(a>0){
	    		if(color == 1){
					fprintf(store_run,"Your chess of color: White.\n"); /*luu thong tin vao file log*/
					printf("128.\n");
					fprintf(store_run,"===============================================\n");
				}else
				if(color == 2)
				{
					fprintf(store_run,"Your chess of color: Black.\n"); /*luu thong tin vao file log*/
					fprintf(store_run,"===============================================\n");
				}
				fclose(store_run);
	    	return a;
	    }	
	    }		
	}
	if(strcmp(p,"RUN")==0){
		// nhan nuoc co tu phia client
		char stem[1024];
		char *p;
		int x, y, x1, y1;
		strcpy(stem,recv_data);
		int a = Check_Run(recv_data, conn_soc, chess, color, &chess_status);
		printf("-----------\n");
    	printf("%d %d %d %d\n",chess_status.status_rock_black1,chess_status.status_rock_black2,chess_status.status_rock_white1,chess_status.status_rock_white2);
    	printf("------------\n");
		if(a>0 && a!=2){
			p = strtok(stem,"|");
			p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/
			x = atoi(p); 
			p = strtok(NULL,"|");/* lay toa do hang cua quan co chon*/ 
			y = atoi(p); 
			p = strtok(NULL,"|");
			x1 = atoi(p); /* lay toa do hang cua nuoc toi*/ 
		    p = strtok(NULL,"|");
		    y1 = atoi(p); /* lay toa do cot cua nuoc toi*/ 
		    if((store_run = fopen(file_name,"a+"))==NULL)
		    {
		      printf("**ERROR** Open file error.\n");
			      return 0;
		    }
		    fprintf(store_run,"%c - %d,%d -> %d,%d\n",chess[x1][y1],x,y,x1,y1);


		    fclose(store_run);
		}
		return a;
	}

	if(strcmp(p,"END_RUN")==0){
		// nhan duoc thong bao chiu thua tu phia client
		return End_Game(conn_soc);
	}
	if(strcmp(p,"RESULT")==0){
		// nhan duoc thong bao chiu thua tu phia client
		p = strtok(NULL,"|");
		char stemp[1024];
		//strcpy(stemp,scan_time()); /*lay thoi gian he thong*/
		 time_t rawtime; 
	    // struct tm *timeinfo; 
	    time(&rawtime); 
	    // timeinfo = localtime(&rawtime); 
	    strcpy(stemp,asctime(localtime(&rawtime)));

	    if((store_run = fopen(file_name,"a+"))==NULL)
		    {
		      printf("**ERROR** Open file error.\n");
			      return 0;
		    }
		    
		fprintf(store_run,"======================================\n");
		fprintf(store_run,"End time: %s\n",stemp);
		fprintf(store_run,"************************************\n");
		if(atoi(p)==1){
			/*client thang*/
  			fprintf(store_run,"************* YOU_WIN **************\n");
  			fprintf(store_run,"************************************\n");
		}else
		{
			fprintf(store_run,"********** COMPUTER_WIN ************\n");
  			fprintf(store_run,"************************************\n");
		}
		fclose(store_run);
		return Send_Result(conn_soc,file_name);
	}

	if(strcmp(p,"EXIT")==0){
		// nguoi dung muon huy ket noi voi server
		return Exit_Connect(conn_soc);
	}
}


int Select_Work(char str[1024], int conn_soc){  /*tuy chon ban dau giua client va server*/
	// co 2 tuy chon
	// 1: dang nhap
	// 2: tao tai khoan moi
	// 3: huy ket noi
	// if(status != unauthenticated){
	// 	 nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay 
	// 	return 0; 
	// }
	char *p;
	int check;
	p = strtok(str,"|");
	p = strtok(NULL,"|"); // lay phan du lieu ma client gui ve
	if(p==NULL){
		check = 4; /* truong hop client khong nhap gi*/
	}
	else check = atoi(p); // lua chon cua client gui ve
	switch(check){
		case 1: // lua chon dang nhap
		{
			retry = 0;
			//send("LOGIN");
			printf("READY_LOGIN\n");
			bytes_sent = send(conn_sock,"READY_LOGIN",22,0);
			return Check_Send(bytes_sent);
		}
		case 2: // lua chon dang ki
		{
			retry = 0;
			//send("READY_SIGNUP");
			bytes_sent = send(conn_sock,"READY_SIGNUP",22,0);
			return Check_Send(bytes_sent);
		}
		case 3:
		{
			retry = 0;
			bytes_sent = send(conn_sock,"OK_EXIT",32,0);
			return 0; // lua chon huy ket noi
		}
		default:
		{
			retry++;
			if(retry<5) // cho nhap sai toi da 5 lan
			{
				//send("SELECT_ERROR");
				bytes_sent = send(conn_sock,"SELECT_ERROR",22,0);
				return Check_Send(bytes_sent);
			}
			else
				//send("BLOCK");// huy ket noi
				bytes_sent = send(conn_sock,"BLOCK",22,0);
				return 0; // nhap sai qua nhieu, huy ket noi
		}
	}
}

int Exit_Connect(int conn_sock){
	bytes_sent = send(conn_sock,"OK_EXIT",22,0);
	return 0; // lua chon huy ket noi
}

void Clear(){
	strcpy(user.username," ");
	strcpy(user.password," ");
	user.online=0;
}

int main(){
	srand(time(NULL));
	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		exit(-1);
	}
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);   /* Remember htons() from "Conversions" section? =) */
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listen_sock,(struct sockaddr*)&server,sizeof(server))==-1){ /* calls bind() */
		printf("bind() error\n");
		exit(-1);
	}     

	if(listen(listen_sock,BACKLOG) == -1){  /* calls listen() */
		printf("listen() error\n");
		exit(-1);
	}

	while(1){
		sin_size=sizeof(struct sockaddr_in);
		if ((conn_sock = accept(listen_sock,(struct sockaddr *)&client,&sin_size))==-1){ /* calls accept() */
			printf("accept() error\n");
			exit(-1);
		}
  
		if((pid=fork())==0){
			close(listen_sock);
			strcpy(ip_address,inet_ntoa(client.sin_addr));
			printf("You got a connection from %s\n",ip_address); /* prints client's IP */
			bytes_sent = send(conn_sock,"HELLO",22,0); /* send to the client welcome message */
			if (Check_Send(bytes_sent) < 0){
				continue;
			}
			int check_status =1; /*bien kiem soat qua trinh lam viec voi client*/

			do{
				bytes_received = recv(conn_sock,recv_data,1024,0); //blocking
				if (Check_Recv(bytes_received) < 0){
					close(conn_sock);
				}
				else{
					recv_data[bytes_received] = '\0';
					//printf("*** From Cllient: %s\n",recv_data);
					if(Check_Mess(recv_data, conn_sock) <= 0){
						close(conn_sock);
						check_status=0;
					}
				}
			}while(check_status>0);
			fclose(store_run);
			exit(0);
		}
		
		status = unauthenticated;
		play_status = not_play;
		signal(SIGCHLD,sig_chld);
		close(conn_sock);
	}
	close(listen_sock);
	return 1;
}
