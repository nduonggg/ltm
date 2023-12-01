#ifndef __STATUS_GAME__
#define __STATUS_GAME__

int Start_Game(int conn_sock){
	// if(status != authenticated || play_status != not_play){
	// 	phai dang nhap moi choi game duoc
	// 	/* nguoi dung dang o trang thai khong cho phep thuc hien hanh dong nay */
	// 	return 0; 
	// }
	bytes_sent = send(conn_sock,"READY_GAME",22,0);
	return Check_Send(bytes_sent);
	//send("GAME_READY"); 
	//play_status = select_color; /*dua game vao trang thai chon mau*/
	/* nhan duoc thong diep nay client cho nguoi dung chon mau quan co*/
	//return 1;
}


int End_Game(int conn_sock){
	//send("COMPUTER_WIN");
	bytes_sent = send(conn_sock,"COMPUTER_WIN",22,0);
	return Check_Send(bytes_sent);
	//play_status = not_play; /*dua game ve trang thai chua bat dau*/
	/**************************
	gui file co pho ve phia client
	***************************/
}

int Send_Result(int conn_sock, char file_name[1024]){
	/*Thao tac gui file ve phia client*/
	FILE *f1;
	char recv_data[1024];
	
	 if((f1=fopen(file_name,"r+"))==NULL)
	{
 	 printf("open file_server error!!!\n");
		}
		else
		{
			char s[1024];
			int i;
			while(fgets(s,1024,f1)!=NULL)
			{
				char str[1024];
				strcpy(str,"FILE_LOG|");
				strcat(str,s);
				strcat(str,"|");
				int bytes_sent = send(conn_sock,str,strlen(str),0); 
				int	bytes_received = recv(conn_sock,recv_data,1024,0);//nhan du lieu tu client gui toi
				if (bytes_received < 0){
						printf("\nError!Can not receive data from client!");
						close(conn_sock);
					}
			}
			bytes_sent = send(conn_sock,"EXIT_FILE_LOG",22,0); 
			return 1;
		}
}

#endif