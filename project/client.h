#ifndef __CLIENT__
#define __CLIENT__
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int check_buff(char buff[80]); /*xac nhan nhung thong diep nhan duoc tu phia server*/
void menu();/*menu sau khi ket noi voi server*/
void lg_user();/*xu ly nhap ten dang nhap*/
void sgup_user();/*dang ky ten dang nhap*/
void sgup_pass();/*dang ky mat khau*/
void menu2();/*menu hien thi khi nhap vao tai khoan khong ton tai*/
void lg_pass();/*nhap vao mat khau dang nhap*/
void confirm_pass();/*xac nhan mat khau dang ky*/
void authenticated_menu();/*menu sau khi dang nhap thanh cong*/
void exit_program();/*xu ly thoat chuong trinh*/
void game_ready();/*xu ly chon mau quan co*/
void select_run();/*nhap duong di thong thuong*/
void select_warning();/*xu ly khi nhan duoc nuoc co chieu tuong*/
void server_run(int warning, int current);/*nhan nuoc co tu phia server va xu ly*/
void you_win();/*thong bao client da thang*/
void computer_win();/*thong bao server da thang*/
void run_error();/*xu ly khi nhap vao duong di khong hop le*/
void update_castling_client(int x1, int y1); /* xu ly nhap thanh ben quan client*/
void make_file_log();/*tao file luu tru thong tin tran dau*/
int printf_log(char str[1024]);/*luu thong tin file log*/

#endif