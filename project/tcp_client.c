#include "interface.h"
#include "my_type.h"
#include "client.h"
#include "update_castling.h" 
#include "time_machine.h"
int client_sock;
char buff[1024];
struct sockaddr_in server_addr;
int bytes_sent,bytes_received;
int *chess[9];
int color=0;
int first_run=1;
RunType run_demo; /*bien luu su di chuyen cua quan co*/
ChessStatus chess_status;/*dung de goi ham update_castling*/
char filename[1014];
FILE *store_log;
int check_buff(char buff[80]) /* Kiem tra tin hieu ket thuc tu phia server*/
{
  if(strcmp(buff,"HELLO")==0) /*Khoi tao*/
    {
      menu();
      return 1;
    }
  if(strcmp(buff, "SELECT_ERROR") ==0) /*Nhap loi*/
    {
      printf("**ERORR** Input errors, please re-enter\n");
      menu();
      return 1;
    }
  /***********************************/
  ////////////////////////////LOGIN///////////////////////////////
  if(strcmp(buff,"READY_LOGIN")==0) /*Chuyen qua giao dien dang nhap,nhap Username*/
    {
      lg_user();
      return 1;
    }
  if(strcmp(buff, "LOGIN_USER_NOT_EXIST") ==0) /*Nhap tai khoan khong dung*/
    {
      printf("**ERORR** Wrong account\n");
      menu2();
      return 1;
    }
  if(strcmp(buff, "LOGIN_USER_ID_OK") == 0) /*Giao dien nhap password*/
    {
      lg_pass();
      return 1;
    }
  if(strcmp(buff, "PASS_NOT_MATCH") ==0)
    {
      printf("**ERORR** Password incorrect, please re-enter\n");
      lg_pass();
      return 1;
    }
  /************************************/
  if(strcmp(buff, "BLOCK") ==0) /*Huy ket noi*/
    {
      printf(">>>>You disconnected<<<<\n");
      return 0;
    }
  ////////////////////////////SIGNUP////////////////////////////////
  if(strcmp(buff, "READY_SIGNUP") == 0) /*Chuyen qua giao dien signup*/
    {
      sgup_user();
      return 1;
    }
  if(strcmp(buff, "USER_ID_NOT_INVALID") == 0) /*Tai khoan nhap vao khong hop le*/
    {
      printf("**ERORR** Invalid account, please re-enter\n");
      sgup_user();
      return 1;
    }
  if(strcmp(buff, "SIGNUP_USER_ID_OK") ==0) /*Nhap password*/
    {
      sgup_pass();
      return 1;
    }
  if(strcmp(buff, "PASS_SHORT") ==0) /*Password qua ngan*/
    {
      printf("**ERORR** Password too short, please re-enter\n");
      sgup_pass();
      return 1;
    }
  if(strcmp(buff, "CONFIRM_PASS") ==0) /*confirm password*/
    {
      confirm_pass();
      return 1;
    }
  if(strcmp(buff, "CONFIRM_NOT_MATCH") ==0) /*Xac nhan mat khau chua dung*/
    {
      printf("**ERORR** Confirmation password do not match, please re-enter\n");
      confirm_pass();
      return 1;
    }
  if(strcmp(buff, "SIGNUP_USER_SUCCESS") ==0) /*Dang ki thanh cong, chuyen qua giao dien menu*/
    {
      menu();
      return 1;
    }
    if(strcmp(buff, "LOGIN_SUCCESS") ==0) /*Dang ki thanh cong, chuyen qua giao dien menu*/
    {
      authenticated_menu();
      return 1;
    }

    if(strcmp(buff, "READY_GAME") ==0) /*Chon mau quan co de chuan bi choi*/
    {
      game_ready();
      return 1;
    } 

    if(strcmp(buff, "LOGOUT_SUCCESS") ==0) /*Dang ki thanh cong, chuyen qua giao dien menu*/
    {
      printf("You have successfully logout.\n");
      menu();
      return 1;
    }
    
    if(strcmp(buff, "COLOR_OK") ==0) /*Nhap vao nuoc co cua phia client*/
    {
      select_run();
      return 1;
    }    
    if(buff[strlen(buff)-1]=='|'){
      /*server run: tham so truyen vao dau tien: 1- nuoc co binh thuong, 2- nuoc co chieu tuong*/
      /*tham so thu 2: yeu cau thuc hien ngoai le:
      + 0: binh thuong
      + 20: nhap thanh ben client
      + 21: nhap thanh ben server
      + 22: nhap thanh ca ben server lan client 
      + 3: phong tot*/
      char str[1024];
      char *p;
      strcpy(str, buff);
      p = strtok(str,"|");
      if(strcmp(p,"RUN")==0){ /*day la nuoc co binh thuong ma server gui den*/
        server_run(1, 0); /*hien thi nuoc co cua phia server*/
        return 1;
      }
      if(strcmp(p,"RUN_W")==0){ /*day la nuoc co chieu tuong ma server gui den*/
        server_run(2, 0); /*hien thi nuoc co cua phia server*/
        return 1;
      }
      if(strcmp(p,"RUN_C_W")==0){ /*day la nuoc co sau khi nhap thanh thi se bi chieu tuong*/
        server_run(2, 2); /*hien thi nuoc co cua phia server*/
        return 1;
      }
      if(strcmp(p,"RUN_C_CLIENT")==0){ /*day la nuoc co ma truoc do client da yeu cau nhap thanh*/
        server_run(1, 20); /*hien thi nuoc co cua phia server*/
        return 1;
      }
      if(strcmp(p,"RUN_U_W")==0){ /*day la nuoc co sau khi phong tot thi se bi chieu tuong*/
        server_run(2, 3); /*hien thi nuoc co cua phia server*/
        return 1;
      }
      if(strcmp(p,"RUN_U")==0){ /*day la nuoc co phong tot*/
        server_run(1, 3); /*hien thi nuoc co cua phia server*/
        return 1;
      }
       if(strcmp(p,"RUN_C_SERVER")==0){ /*day la nuoc co nhap thanh ben server*/
        server_run(1, 21); /*hien thi nuoc co cua phia server*/
        return 1;
      }
      if(strcmp(p,"RUN_C_SERVER_CLIENT")==0){ /*day la nuoc co nhap thanh ca ben server va client*/
        server_run(1, 22); /*hien thi nuoc co cua phia server*/
        return 1;
      }
      if(strcmp(p,"FILE_LOG")==0){ /*luu thong tin tran dau vao file log*/
        return printf_log(buff);
      }
    }

    if(strcmp(buff, "RUN_ERROR") == 0) /*Duong di phia client nhap bi loi*/
    {
      printf("Vaop run error %d\n",strcmp(buff, "RUN_ERROR"));
      paint(chess,color);
      run_error();
      return 1;
    } 
    if(strcmp(buff, "YOU_WIN") == 0) /*Client chien thang*/
    {
      you_win();
      return 1;
    }
    if(strcmp(buff, "COMPUTER_WIN") == 0) /*Server chien thang*/
    {
      computer_win();
      return 1;
    }
    if(strcmp(buff, "OK_EXIT") == 0) /*Huy ket noi thanh cong*/
    {
      exit_program();
      return 0;
    }
    if(strcmp(buff, "EXIT_FILE_LOG") == 0) /*Huy ket noi thanh cong*/
    {
      authenticated_menu();
      return 1;
    }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
void menu(){
  char choice[10];
  printf("=====================================\n");
  printf("1. Login.\n");
  printf("2. Create new account.\n");
  printf("3. Exit.\n");
  printf("=====================================\n");

  printf("=>>You enter into the selection:");
  gets(choice);
  printf("-------------------------------------\n");
  //printf("ban da chon %s\n",choice);
  strcpy(buff,"SELECT_WORK|");
  strcat(buff,choice);
  strcat(buff,"|");
  /*khuon dang gui SELECT|1|*/
  //buff[strlen(buff)]='\0';
  //printf("%s\n",buff);
}
////////////////////////////////////////////////////////////////////////////////
void menu2(){
  int choice;
  int dd=0;
  printf("=====================================\n");
  printf("1. Re-login.\n");
  printf("2. Create new account.\n");
  printf("3. Exit.\n");
  printf("=====================================\n");
  do
  {
    printf("=>>You enter into the selection:");
    scanf("%d", &choice);
    while(getchar()!='\n');
    switch(choice){
      case 1: {
        lg_user();
        dd=1;
        break;
      }
      case 2: {
        sgup_user();
        dd=1;
        break;
      }
      case 3: {
        strcpy(buff,"EXIT|");
        dd=1;
        break;
      }
      default: {
        printf("**ERORR** Please re-enter your selection.\n");
        break;
      }
    }
  }while(dd==0);
}
////////////////////////////////////////////////////////////////////////////////
void lg_user(){
  char s[80];
  printf("=>>Enter your username:");
  gets(s);
  printf("-------------------------------------\n");
  strcpy(buff, "LOGIN_USER|");
  strcat(buff, s);
  strcat(buff,"|");
  printf("%s\n",buff);
}
////////////////////////////////////////////////////////////////////////////////

void lg_pass(){
  char s[80];
  printf("=>>Enter your password:");
  gets(s);
  printf("-------------------------------------\n");
  strcpy(buff, "LOGIN_PASS|");
  strcat(buff, s);
  strcat(buff,"|");

}
////////////////////////////////////////////////////////////////////////////////
void sgup_user(){
  char s[80];
  printf("=>>Enter your account name register:");
  gets(s);
  printf("-------------------------------------\n");
  strcpy(buff, "SIGNUP_USER|");
  strcat(buff, s);
  strcat(buff,"|");
}
////////////////////////////////////////////////////////////////////////////////
void sgup_pass(){
  char s[80];
  printf("=>>Enter your password register:");
  gets(s);
  printf("-------------------------------------\n");

  strcpy(buff, "SIGNUP_PASS|");
  strcat(buff, s);
  strcat(buff,"|");
}
////////////////////////////////////////////////////////////////////////////////
void confirm_pass(){
  char s[80];
  printf("=>>Confirm password:");
  gets(s);
  printf("-------------------------------------\n");

  strcpy(buff, "CONFIRM_PASS|");
  strcat(buff, s);
  strcat(buff,"|");
}
////////////////////////////////////////////////////////////////////////////////
void authenticated_menu(){
  int choice;
  int dd=0;
  printf("=====================================\n");
  printf("1|- Start game.\n");
  printf("2|- Logout.\n");
  printf("3|- Exit.\n");
  printf("=====================================\n");
  do
  {
    printf("=>>You enter into the selection:");
    scanf("%d", &choice);
    while(getchar()!='\n');
    switch(choice){
      case 1: {
        strcpy(buff,"START_GAME|");
        dd=1;
        break;
      }
      case 2: {
        strcpy(buff,"LOGOUT|");
        dd=1;
        break;
      }
      case 3: {
        strcpy(buff,"EXIT|");
        dd=1;
        break;
      }
      default: {
        printf("**ERORR** Please re-enter your selection.\n");
        break;
      }
    }
  }while(dd==0);

}
////////////////////////////////////////////////////////////////////////////////
void exit_program(){
  printf("=>>You have successfully exited.\n");
}
////////////////////////////////////////////////////////////////////////////////
void game_ready(){
  int dd=0;
  int choice=0;
  for(int i = 0; i < 9; i++)
    chess[i] = (int*)malloc(9*sizeof(int)); 
  make_chess(chess);
  paint(chess,3);
  printf("=====================================\n");
  printf("1. White.\n");
  printf("2. Black.\n");
  printf("=====================================\n");
  do{
    printf("=>>You enter into the selection:");
    scanf("%d",&choice);
    while(getchar()!='\n');
    switch(choice){
      case 1:
      {
        strcpy(buff,"COLOR|1|");
        color = 1;
        dd = 1;
        break;
      }
      case 2:
      {
        strcpy(buff,"COLOR|2|");
        color = 2;
        dd = 1;
        break;
      }
      case 3:
      {
        printf("**ERORR** Please re-enter your selection.\n");
        break;
      }
    }
  }while(dd==0);
}
////////////////////////////////////////////////////////////////////////////////
void server_run(int warning, int current){
  /* warning = 0 nuoc co binh thuong
    warning = 1  nuoc co chieu tuong
  */
  char *p;
  int x,y,x1,y1;
  x = run_demo.x2; /*Loi x khong luu gia tri*/
  y = run_demo.y;
  x1 = run_demo.x1;
  y1 = run_demo.y1;
  if(first_run==1){
    /*neu la nuoc co dau tien thi khong can cap nhap nuoc co truoc do*/
    first_run = 0;
  }else
  {
   /*Cap nhat nuoc co ma client danh truoc do*/
    chess[x1][y1]=chess[x][y];
    chess[x][y]='_';
  }

  
  p = strtok(buff,"|");
  p = strtok(NULL,"|");
  x = atoi(p);
  p = strtok(NULL,"|");
  y = atoi(p);
  p = strtok(NULL,"|");
  x1 = atoi(p);
  p = strtok(NULL,"|");
  y1 = atoi(p);
  /*cap nhat nuoc co ma server danh tra*/
  chess[x1][y1]=chess[x][y];
  chess[x][y]='_';

 /*tham so current: yeu cau thuc hien ngoai le:
      + 0: binh thuong
      + 20: nhap thanh ben client
      + 21: nhap thanh ben server
      + 22: nhap thanh ca ben server lan client 
      + 3: phong tot*/


  switch(current){
    case 20:
    {
      update_castling_client(run_demo.x1, run_demo.y1);
      break;
    }
    case 21:
    {
      update_castling_client(x1,y1);
      break;
    }
    case 22:
    {
      update_castling_client(run_demo.x1, run_demo.y1);
      update_castling_client(x1,y1);
      break;
    }
  }


  paint(chess,color);
 
  switch(warning){
    case 1:
    {
      select_run();
      break;
    }
    case 2:
    {
      select_warning();
      break;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
void run_error(){
  /*Xu ly khi nuoc co nhap vao bi loi*/
  printf("**ERROR**Move invalid, please re-enter.\n");
  select_run();
}

////////////////////////////////////////////////////////////////////////////////
void select_run(){
  char x1[2],y1[2],x[2],y[2];
  /*x, y la toa do chon
  x1, y1 la toa do di den*/
  if(first_run==1){
    /*xoa di trang thai chua danh nuoc co nao*/
    first_run = 0;
  }
  printf("Enter the location you choose.\n");
  printf("=>>Coordinates row:");
  gets(x);
  printf("=>>Coordinates column:");
  gets(y);
  printf("Enter the location you want to go.\n");
  printf("=>>Coordinates row:");
  gets(x1);
  printf("=>>Coordinates column:");
  gets(y1);
  /*luu lai duong di truoc khi gui qua server kiem tra*/
  run_demo.x=atoi(x);
  run_demo.y=atoi(y);
  run_demo.x1=atoi(x1);
  run_demo.y1=atoi(y1);
  run_demo.x2=atoi(x); /*loi x khong luu gia tri*/

  strcpy(buff,"RUN|");
  strcat(buff,x);
  strcat(buff,"|");
  strcat(buff,y);
  strcat(buff,"|");
  strcat(buff,x1);
  strcat(buff,"|");
  strcat(buff,y1);
  strcat(buff,"|");
}
////////////////////////////////////////////////////////////////////////////////
void select_warning(){
  int choice;
  int dd=0;
  printf(">>>WARNING<<<King is in danger, you have to solve it?\n");

  printf("=====================================\n");
  printf("1. Yes.\n");
  printf("2. No.\n");
  printf("=====================================\n");
  do{
    printf("=>>You enter into the selection:");
    scanf("%d",&choice);
    switch(choice){
      case 2:
      {
        strcpy(buff,"END_RUN");
        dd=1;
        break;
      }
      case 1:
      {
        select_run();
        dd=1;
        break;
      }
      default:
      {
        printf("**ERORR** Please re-enter your selection.\n");
        break;
      }
    }

  }while(dd==0);
}
////////////////////////////////////////////////////////////////////////////////
void update_castling_client(int x1_c, int y1_c){
  /*cap nhat them nuoc co nhap thanh cua client*/
  /*truyen vao vi tri cua quan vua hien tai*/
  int x, y, x1, y1;
  RunType r_type = update_castling(x1_c, y1_c, &chess_status);
  x = r_type.x;
  y = r_type.y;
  x1 = r_type.x1;
  y1 = r_type.y1;
  printf("%d %d %d %d\n", x, y, x1 ,y1);
  chess[x1][y1] = chess[x][y];
  chess[x][y]= '_';

}
////////////////////////////////////////////////////////////////////////////////
void you_win(){
  printf("************************************\n");
  printf("************* YOU_WIN **************\n");
  printf("************************************\n");
  strcpy(buff,"RESULT|1|"); /*Yeu cau nhan file ket qua tu phai server*/
  make_file_log();
}
////////////////////////////////////////////////////////////////////////////////
void computer_win(){
  printf("************************************\n");
  printf("********** COMPUTER_WIN ************\n");
  printf("************************************\n");
  strcpy(buff,"RESULT|2|"); /*Yeu cau nhan file ket qua tu phai server*/
  make_file_log();
}
////////////////////////////////////////////////////////////////////////////////
int printf_log(char str[1024]){
  char str2[1024];
  char *p;
  if((store_log = fopen(filename,"a+"))==NULL)
    {
      printf("**ERROR** Open file error.\n");
        return 0;
    }
    else{
      strcpy(str2,str);
      p = strtok(str2,"|");
      p = strtok(NULL,"|");
      fprintf(store_log,"%s",p);
    }
    fclose(store_log);
    strcpy(buff,"RECV_OK");
    return 1;

}
////////////////////////////////////////////////////////////////////////////////
void make_file_log(){
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
  strcpy(filename,make_name_file(stemp,1)); /*Tao file luu thong tin tran dau*/
}
////////////////////////////////////////////////////////////////////////////////
int main(){
  
  client_sock=socket(AF_INET,SOCK_STREAM,0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5500);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int dd=1;
  
  if(connect(client_sock,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))!=0){
    printf("\nError!Can not connect to sever!Client exit imediately! ");
    return 0;
  }
  
  do
    {		
      bytes_received = recv(client_sock,buff,1024,0);
      if(bytes_received == -1){
    	printf("\nError!Cannot receive data from sever!\n");
    	close(client_sock);
    	exit(-1);
      }
      //buff[bytes_received] = '\0';
      //printf("***From Sever: %s\n", buff);
      if(check_buff(buff) == 1){
        bytes_sent = send(client_sock,buff,strlen(buff),0);
        if(bytes_sent == -1){
          printf("\nError!Cannot send data to sever!\n");
          close(client_sock);
          exit(-1);
        }
      }
      else {
          dd=0;
        }
    }while(dd==1);	
  close(client_sock);
  return 0;
}
