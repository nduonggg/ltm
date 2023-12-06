#ifndef __UPDATE_CASTLING__
#define __UPDATE_CASTLING__

#include "my_type.h"


RunType update_castling(int x_king, int y_king, ChessStatus *chess_status){
	/*Nhan vao mot quan co va toa do cua quan co do*/
	/*Tim  vi tri nhap thanh tuong ung*/
	/*xu ly voi ca 2 truong hop chess la quan tuong va quan xe*/
	RunType run_type;
	ChessStatus chess_status2;

	chess_status2 = *chess_status;

	int x, y, x1, y1;
	/*Than chuong trinh*/
	if (x_king == 7 && y_king == 2)
	{
		x = 7;
		y = 0;
		x1 = 7;
		y1 = 3;
		chess_status2.status_rock_white1 = 1;
	}
	else if (x_king == 7 && y_king == 6)
	{
		x = 7;
		y = 7;
		x1 = 7;
		y1 = 5;
		chess_status2.status_rock_white2 = 1;

	}
	else if (x_king == 0 && y_king == 2)
	{
		x = 0;
		y = 0;
		x1 = 0;
		y1 = 3;
		chess_status2.status_rock_black1 = 1;

	}
	else if (x_king == 0 && y_king == 6)
	{
		x = 0;
		y = 7;
		x1 = 0;
		y1 = 5;
		chess_status2.status_rock_black2 = 1;
	}
	/*Than chuong trinh*/

	run_type.x = x;
	run_type.y = y;
	run_type.x1 = x1;
	run_type.y1 = y1;

	*chess_status = chess_status2;

	return run_type;
}

#endif