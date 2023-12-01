#ifndef __SERVER__
#define __SERVER__
#include "my_type.h"

int Check_Mess(char recv_data[1024], int conn_soc);/*Xac thuc nhung yeu cau cua ben client gui toi*/
void sig_chld(int signo); /*xu ly goi tin sig*/
void Clear();/*xoa bien luu tai khoan hien hanh*/
int Exit_Connect(int conn_sock);/*huy ket noi voi client*/
int Select_Work(char str[1024], int conn_soc);/*kiem tra tuy chon ban dau cua client gui toi server*/

#endif 