#ifndef __CHECK_CHESS_RUN__
#define __CHECK_CHESS_RUN__

#include "my_type.h"

int check_knight(int **chess, int color, int x, int y, int x1, int y1);/*kiem tra quan ma*/
int check_pawn(int **chess, int color, int x, int y, int x1, int y1);/*kiem tra quan tot*/
int check_rock(int **chess, int color, int x, int y, int x1, int y1);/*kiem tra quan xe*/
int check_king(int **chess, int color, int x, int y, int x1, int y1);/*kiem tra quan vua*/
int check_bishop(int **chess, int color, int x, int y, int x1, int y1);/*kiem tra quan tuong*/
int check_queen(int **chess, int color, int x, int y, int x1, int y1);/*kiem tra quan hau*/
int castling(int **chess, int color, int x, int y, int x1, int y1, ChessStatus *chess_status);/*nhap thanh*/
int check_checkmate(int **chess, int color,  int x, int y); /*ham kiem tra chieu tuong*/
int check_checkmate_reverse(int **chess, int color, ChessStatus *chess_status); /*Kiem tra xem nuoc co cua minh co chieu 
tuong doi phuong khong*/
int check_endgame(int **chess, int color);/*kiem tra quan tuong con hay khong*/


int check_knight(int **chess, int color, int x, int y, int x1, int y1){
  int count=0;/*dem so nuoc toi da ma quan ma co the di*/
  int i;
  int j;
  i = y + 2;
  j = y - 2;
  if((i==y1 && i<=7 && i>=0)||(j == y1 && j<=7 && j>=0)){
  // printf("Quan ma di theo phuong ngang.\n");
      i = x + 1;
      j = x - 1;
      if((i==x1 && i<=7 && i>=0)||(j==x1 && j<=7 && j>=0)){
        return 1; /*duong di hop le*/
      }else{
        return 0; /*duong di khong hop le*/
      }
  }else
  {
    i = x + 2;
    j = x - 2;
    if((i==x1 && i<=7 && i>=0)||(j == x1 && j<=7 && j>=0)){
    //  printf("Quan ma di theo phuong doc.\n");
      i = y + 1;
      j = y - 1;
      if((i==y1 && i<=7 && i>=0)||(j==y1 && j<=7 && j>=0)){
        return 1; /*duong di hop le*/
      }else{
        return 0; /*duong di khong hop le*/
      }
    }
    else
    {
      /*duong di cua quan ma khong hop le*/
      return 0; 
    }
  }
}


/***********************************************************************/
/* - Hàm kiểm tra các nước đi của quân tốt.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tốt là đúng, trả về 0 nếu nước đi là sai.
*/
int check_pawn(int **chess, int color, int x, int y, int x1, int y1){
  //quân đen
  if(color == 2){
    if((x1-x) >2 || (x1-x) <1)
      return 0;
    else if((x1-x) == 2){
      if(y1 == y && x == 1 && chess[x+1][y1] == '_' && chess[x1][y1] == '_')   /*di chuyển dọc 2 ô*/
        return 1;
      else return 0;
    }
    else {
      if(y1 == y && chess[x1][y1] == '_')                                      /*di chuyển dọc 1 ô*/
        return 1;
      else if(y1 == y-1 && chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z')       /*ăn chéo trái*/
        return 1;
      else if(y1 == y+1 && chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z')       /*ăn chéo phải*/
        return 1;
      else return 0;
    }
  }
  //quân trắng
  else {
    if((x-x1) >2 || (x-x1) <1)
      return 0;
    else if((x-x1) == 2){
      if(y == y1 && x==6 && chess[x-1][y1] == '_' && chess[x1][y1] == '_') {     /*di chuyển dọc 2 ô*/
        return 1;
      }
      else return 0;
    }
    else {
      if(y1 == y && chess[x1][y1] == '_')                                       /*di chuyển dọc 1 ô*/
        return 1;
      else if(y1 == y-1 && chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z')        /*ăn chéo trái*/
        return 1;
      else if(y1 == y+1 && chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z')        /*ăn chéo phải*/
        return 1;
      else return 0;
    }
  }
}
/************************************************************************/
/*- Hàm kiểm tra các nước đi của quân xe.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân xe là đúng, trả về 0 nếu nước đi là sai.
*/
int check_rock(int **chess, int color, int x, int y, int x1, int y1){
  int i,j;
  int start,finish;
  /*di chuyển theo hàng ngang*/
  if(x == x1){
    if(y > y1) {
      start = y1 +1;
      finish = y;
    }
    else {
      start = y +1;
      finish = y1;
    }
    for(j= start ; j<finish; j++) {
      if(chess[x1][j] != '_')
        return 0;
    }
    //quân đen
    if(color == 2) {
      if((chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
    //quân trắng
    else {
      if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
        return 1;
      else return 0;
    }
  }
  /*di chuyển theo hàng dọc*/
  else if(y == y1){
    if(x > x1) {
      start = x1 +1;
      finish = x;
    }
    else {
      start = x +1;
      finish =x1;
    }
    for(i= start ; i<finish; i++){
      if(chess[i][y1] != '_')
        return 0;
    }
    //quân đen
    if(color == 2) {
      if((chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z') || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
    //quân trắng
      else {
        if((chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z') || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
  }
  else return 0;
}
/************************************************************************/
/* - Hàm kiểm tra các nước đi của quân tướng.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tướng là đúng, trả về 0 nếu nước đi là sai.
*/
int check_king(int **chess, int color, int x, int y, int x1, int y1){
  //kiểm tra 8 ô liền kề
  if(y1 == y-1 || y1 == y || y1 == y+1) {
    if(x1 == x-1 || x1 == x || x1 == x+1) {
      //quân đen
      if(color == 2){
        if(chess[x1][y1] == '_' || (chess[x1][y1] > 'A' && chess[x1][y1] <='Z'))
          return 1;
        else return 0;
      }
      //quân trắng
      else {
        if(chess[x1][y1] == '_' || (chess[x1][y1] > 'a' && chess[x1][y1] <='z'))
          return 1;
        else return 0;
      }
    }
    else return 0;
  }
  else return 0;
}
/************************************************************************/
/* - Hàm kiểm tra các nước đi của quân tượng.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
     vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1)
   - Hàm trả về 1 nếu nước đi của quân tượng là đúng, trả về 0 nếu nước đi là sai.
*/
int check_bishop(int **chess, int color, int x, int y, int x1, int y1){
  int i,j;
  if(x > x1) {
    if(y > y1 && x-x1 == y-y1) {
      j=y-1;
      for(i=x-1 ; i>x1 ; i-- ){
        if(chess[i][j] != '_')
          return 0;
        j = j-1;
      }
      if(color == 2) {
        if(chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
      else {
        if(chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
    }
    else if(y < y1 && x-x1 == y1-y) {
      j=y+1;
      for(i=x-1 ; i>x1 ; i-- ){
        if(chess[i][j] != '_')
          return 0;
        j = j+1;
      }
      if(color == 2) {
        if(chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
      else {
        if(chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
    }
    else return 0;
  }
  else if(x1 > x){
    if(y > y1 && x1-x == y-y1) {
      j=y-1;
      for(i=x+1 ; i<x1 ; i++ ){
        if(chess[i][j] != '_')
          return 0;
        j = j-1;
      }
      if(color == 2) {
        if(chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
      else {
        if(chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
    }
    else if(y < y1 && x1-x == y1-y) {
      j=y+1;
      for(i=x+1 ; i<x1 ; i++ ){
        if(chess[i][j] != '_')
          return 0;
        j = j+1;
      }
      if(color == 2) {
        if(chess[x1][y1] >= 'A' && chess[x1][y1] <= 'Z' || chess[x1][y1] == '_')
          return 1;
        else return 0;
      }
      else {
        if(chess[x1][y1] >= 'a' && chess[x1][y1] <= 'z' || chess[x1][y1] == '_')
          return 1;
      else return 0;
      }
    }
    else return 0;
  }
  else return 0;
}
/************************************************************************/
/* - Hàm kiểm tra các nước đi của quân hậu.
   - Tham số truyền vào gồm mảng ches[8][8], màu của quân cờ color,
   vị trí hiện tại của quân cờ (x,y), vị trí cần di chuyển đến (x1,y1).
   - Hàm trả về 1 nếu nước đi của quân hậu là đúng, trả về 0 nếu nước đi là sai.
*/
int check_queen(int **chess, int color, int x, int y, int x1, int y1){
   if(x == x1 || y == y1){
    if(check_rock(chess,color,x,y,x1,y1) == 1)
      return 1;
    else return 0;
  }
  else if(x != x1){
    if(check_bishop(chess,color,x,y,x1,y1) == 1)
      return 1;
    else return 0;
  }
  else return 0;
}

/************************************************************************/
int check_checkmate(int **chess, int color, int x, int y){
  /*Kiem tra xem quan tuong ben minh co bi chieu hay khong*/
  int i, j;
  for(i=0 ;i<=7 ;i++){
    for(j=0 ; j<=7 ;j++){
      if(color == 1) {
        switch(chess[i][j]){
        case 'o':
          if(check_pawn(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 'x':
          if(check_rock(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 't':
          if(check_bishop(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 'h':
          if(check_queen(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 'w':
          if(check_king(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        case 'm':
          if(check_knight(chess,color+1,i,j,x,y) == 1)
            return 1;
          break;
        }
      }
      else {
        switch(chess[i][j]){
        case 'O':
          if(check_pawn(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        case 'X':
          if(check_rock(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        case 'T':
          if(check_bishop(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        case 'H':
          if(check_queen(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        case 'W':
          if(check_king(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
           case 'M':
          if(check_knight(chess,color-1,i,j,x,y) == 1)
            return 1;
          break;
        }
      }
    }
  }
  return 0; /*quan tuong khong bi chieu*/
}
/************************************************************************/

int check_checkmate_reverse(int **chess, int color, ChessStatus *chess_status)
{
  /*Kiem tra xem nuoc co ben minh co chieu tuon ben doi phuong hay khong*/
  int king_x_white;
  int king_y_white;
  int king_x_black;
  int king_y_black;
  ChessStatus chess_status2;

  chess_status2 = *chess_status;

  king_x_black = chess_status2.king_x_black;
  king_y_black = chess_status2.king_y_black;
  king_x_white = chess_status2.king_x_white;
  king_y_white = chess_status2.king_y_white;

  if(color == 1){
    /*kiem tra xem co chieu tuong quan den khong*/
      if(check_checkmate(chess, 2, king_x_black, king_y_black)>0){
        return 444;
        /*Day la nuoc co chieu tuong*/
      }
      else
      {
        return 0; 
      }
  }else{
       /*kiem tra xem co chieu tuong quan trang khong*/
      if(check_checkmate(chess, 1, king_x_white, king_y_white)>0){
        return 444;
        /*Day la nuoc co chieu tuong*/
      }
      else
      {
        return 0; 
      }
  }
}
/************************************************************************/

int castling(int **chess, int color, int x, int y, int x1, int y1, ChessStatus *chess_status){
  ChessStatus chess_status2;
  chess_status2 = *chess_status;
    if(color == 1 && chess_status2.status_king_white == 0){
      if(y1 == y-2 && chess[7][0] == 'X' && chess_status2.status_rock_white1 == 0){
        if(check_rock(chess,color,7,0,7,3) == 1 && check_checkmate(chess,color,x1,y1) != 1){
          /*kiem tra su di chuyen cua quan xe va quan tuong co bi chieu tuong hay khong*/
          // chess[7][0] = '_';
          // chess[7][3] = 'X'; //xu ly nuoc co nay ben phia client
          return 24; /*Nhap thanh goc phan tu thu 4*/
        }
      }
      else if(y1 == y+2 && chess[7][7] == 'X' && chess_status2.status_rock_white2 == 0){
        if(check_rock(chess,color,7,7,7,5) == 1 && check_checkmate(chess,color,x1,y1) != 1){
          // chess[7][7] = '_';
          // chess[7][5] = 'X'; //xu ly nuoc co nay ben phia client
          return 23; /*Nhap thanh goc phan tu thu 3*/
        }
      }
      return 0;
    }
    else if(color == 2 && chess_status2.status_king_black == 0){
      if(y1 == y-2 && chess[0][0] == 'x' && chess_status2.status_rock_black1 == 0){
        if(check_rock(chess,color,0,0,0,3) == 1 && check_checkmate(chess,color,x1,y1) != 1){
          // chess[0][0] = '_';
          // chess[0][3] = 'x';
          return 21; /*Nhap thanh goc phan tu thu 1*/
        }
      }
      else if(y1 == y+2 && chess[0][7] == 'x' && chess_status2.status_rock_black2 == 0){
        if(check_rock(chess,color,0,7,0,5) == 1 && check_checkmate(chess,color,x1,y1) != 1){
          // chess[0][7] = '_';
          // chess[0][5] = 'x';
          return 22; /*Nhap thanh goc phan tu thu 2*/
        }
      }
      else return 0;
    }
  else return 0;
}

int check_endgame(int **chess, int color){
  int i,j;
  for(i=0; i<=7; i++){
    for(j=0; j<=7; j++){
      if(color == 1){
        if(chess[i][j] == 'W')
          return 1;
      }
      else {
        if(chess[i][j] == 'w')
          return 1;
      }
    }
  }
  return 0;
}

#endif