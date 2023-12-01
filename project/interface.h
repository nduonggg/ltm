#ifndef __INTERFACE__
#define __INTERFACE__
#include <stdio.h>

void make_chess(int **chess); /*Tao moi ban co*/
void paint(int **chess, int x); /*Hien thi ban co*/

void make_chess(int **chess)
{
  int i,j;
  for(i=1;i<=6;i++)
    {
      if(i==1)
    	{
      	   for(j=0;j<=7;j++)
      	{
      	  chess[i][j]='o';
      	}
    	}
      else
      if(i==6)
    	{
      	   for(j=0;j<=7;j++)
      	{
      	  chess[i][j]='O';
      	}
    	}
      else
      for(j=0;j<=7;j++)
    	{
    	  chess[i][j]='_';
    	}
    }
  chess[0][0]='x';chess[7][0]='X';chess[0][7]='x';chess[7][7]='X';
  chess[0][1]='m';chess[7][1]='M';chess[0][6]='m';chess[7][6]='M';
  chess[0][2]='t';chess[7][2]='T';chess[0][5]='t';chess[7][5]='T';
  chess[0][3]='h';chess[0][4]='w';
  chess[7][3]='H';chess[7][4]='W';
  
}
void paint(int **chess, int x){
  /* x=2 nguoi choi chon den, 1 nguoi choi chon trang */
  /* x=3 nguoi dung chua chon mau*/
  int i,j;
  printf("--------------------------------------------------------------------\n");
  printf("       0\t1\t 2\t 3\t 4\t 5\t 6\t 7\t\n");
  printf("____________________________________________________________________\t");
  if(x==2)
  {
    printf("--->Black(H)<---\n");
  }
  else if(x==1||x==3)
  {
    printf("--->Black<---\n");
  }
  for(i=0;i<=7;i++){
    printf("   ||\n");
    printf("   ||\n");
    printf("%d  ||   ",i);
    for(j=0;j<=7;j++){
    
      printf("%c\t",chess[i][j]);
      
    }
    printf("\n");
  }
  printf("____________________________________________________________________\t");
  if(x==2||x==3)
  {
    printf("--->White<---\n");    
  }
  else if(x==1)
  {
    printf("--->White(H)<---\n");    
  }
}
#endif