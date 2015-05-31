#define _X_OPEN_SOURCE_EXTENDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncursesw/ncurses.h>
#include <curses.h>
#include <locale.h>
#include <wchar.h>


int** createGrid(int x, int y)
{
	int** board;
	board = malloc(y * sizeof(int*));
	int k;
	for(k=0;k<y;k++)
	{
		board[k] = malloc(x * sizeof(int));
		if(board[k] == NULL)
		{
			/* I sure hope not */
			return;
		}
	}


	int i,j;

	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			board[i][j]=0;
		}
	}

	return board;
}

char** createCharGrid(int x, int y)
{
	char** board;
	board = malloc(y * sizeof(char*));
	int k;
	for(k=0;k<y;k++)
	{
		board[k] = malloc(x * sizeof(char));
		if(board[k] == NULL)
		{
			/* I sure hope not */
			return;
		}
	}


	int i,j;

	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			board[i][j]=0;
		}
	}

	return board;
}


int* getneighborsX(int x, int gridWidth)
{
	int * arr;
	arr = malloc(8*sizeof(int));

	int x1,x2,x3,x4,x5,x6,x7,x8;
	x1=x-1;	x2=x; x3=x+1; x4=x-1; x5=x+1; x6=x-1; x7=x; x8=x+1;
	if(x1<0)
		x1+=gridWidth;
	if(x2<0)
		x2+=gridWidth;
	if(x3<0)
		x3+=gridWidth;
	if(x4<0)
		x4+=gridWidth;
	if(x5<0)
		x5+=gridWidth;
	if(x6<0)
		x6+=gridWidth;
	if(x7<0)
		x7+=gridWidth;
	if(x8<0)
		x8+=gridWidth;

	if(x1>gridWidth-1)
		x1-=gridWidth;
	if(x2>gridWidth-1)
		x2-=gridWidth;
	if(x3>gridWidth-1)
		x3-=gridWidth;
	if(x4>gridWidth-1)
		x4-=gridWidth;
	if(x5>gridWidth-1)
		x5-=gridWidth;
	if(x6>gridWidth-1)
		x6-=gridWidth;
	if(x7>gridWidth-1)
		x7-=gridWidth;
	if(x8>gridWidth-1)
		x8-=gridWidth;
	arr[0]=x1;arr[1]=x2;arr[2]=x3;arr[3]=x4;arr[4]=x5;arr[5]=x6;arr[6]=x7;arr[7]=x8;
	return arr;
	
}

int* getneighborsY(int y, int gridHeight)
{
	int * arr;
	arr = malloc(8*sizeof(int));

	int y1,y2,y3,y4,y5,y6,y7,y8;
	y1=y-1; y2=y-1; y3=y-1; y4=y; y5=y; y6=y+1; y7=y+1; y8=y+1;

	if(y1<0)
		y1+=gridHeight;
	if(y2<0)
		y2+=gridHeight;
	if(y3<0)
		y3+=gridHeight;
	if(y4<0)
		y4+=gridHeight;
	if(y5<0)
		y5+=gridHeight;
	if(y6<0)
		y6+=gridHeight;
	if(y7<0)
		y7+=gridHeight;
	if(y8<0)
		y8+=gridHeight;

	if(y1>gridHeight-1)
		y1-=gridHeight;
	if(y2>gridHeight-1)
		y2-=gridHeight;
	if(y3>gridHeight-1)
		y3-=gridHeight;
	if(y4>gridHeight-1)
		y4-=gridHeight;
	if(y5>gridHeight-1)
		y5-=gridHeight;
	if(y6>gridHeight-1)
		y6-=gridHeight;
	if(y7>gridHeight-1)
		y7-=gridHeight;
	if(y8>gridHeight-1)
		y8-=gridHeight;

	arr[0]=y1;arr[1]=y2;arr[2]=y3;arr[3]=y4;arr[4]=y5;arr[5]=y6;arr[6]=y7;arr[7]=y8;
	return arr;
}

int neighborsum(int** board, int* xarr, int* yarr)
{
	int sum = board[xarr[1]][yarr[1]] + board[xarr[2]][yarr[2]] + board[xarr[3]][yarr[3]] + board[xarr[4]][yarr[4]] + board[xarr[5]][yarr[5]] + board[xarr[6]][yarr[6]] + board[xarr[7]][yarr[7]] + board[xarr[0]][yarr[0]];
	return sum;
}

bool ruleTwo(int** board, int gridHeight, int gridWidth, int x, int y)
{
	int* xarr = getneighborsX(x,gridWidth);
	int* yarr = getneighborsY(y,gridHeight);
	int sum = neighborsum(board, xarr, yarr);
	
	if(sum>3||sum<2)
		return false;
	else
		return true;
}

bool ruleThree(int** board, int gridHeight, int gridWidth, int x, int y)
{
	int* xarr = getneighborsX(x,gridWidth);
	int* yarr = getneighborsY(y,gridHeight);
	int sum = neighborsum(board, xarr, yarr);

	if(sum==3)
		return true;
	return false;
	
}

int** onestep(int** board, int gridHeight, int gridWidth)
{
	int** newgen = createGrid(gridHeight, gridWidth);

	int i,j;
	for (i=0;i<gridHeight;i++)
	{
		for (j=0;j<gridWidth;j++)
		{
			newgen[j][i]=board[j][i];
			if(board[j][i]==1)
				newgen[j][i]= ruleTwo(board,gridHeight,gridWidth,j,i);
			else{
				newgen[j][i]= ruleThree(board, gridHeight, gridWidth, j, i);
				/*printf("3453535345");*/}
		}
	}
	return newgen;
}

void makeDisp(int** board, int gridHeight, int gridWidth)
{
	int newGridWidth = gridWidth*2;
	char** disp = createCharGrid(gridHeight, newGridWidth);
	int i,j;
	for (i=0;i<gridHeight;i++)
	{
		for (j=0;j<gridWidth;j++)
		{
			if(board[j][i]==1)
			{
				disp[2*j][i] = 178;
				disp[(2*j)+1][i] = 178;
			}
			else
			{
				disp[2*j][i] = 176;
				disp[(2*j)+1][i] = 176;
			}
		}
	}
	for (i=0;i<gridHeight;i++)
	{char str[newGridWidth];
		for(j=0;j<newGridWidth;j++)
		{
			str[j] = disp[j][i];
		}
		mvaddstr(i+1,1,str);
	}refresh();
	usleep(62500);
	
}


void printGrid(int** board, int gridHeight, int gridWidth)
{/*char st[1];sprintf(st, "%d", gridWidth);mvaddstr(0,0,st);*/
	int i,j;
	for(i=0;i<gridHeight;i++)
	{char str[gridWidth];
		for(j=0;j<gridWidth;j++)
		{
			
			str[j] = (char)(board[j][i]+48);
			/*printf("%d",board[j][i]);*/
		/*	printf("%d|",board[i][j]);*/
			
		}/*str[gridWidth+1]='\0';*/
		/*printf("\n");*/
		mvaddstr(i+1, 1, str);
    		
	}refresh();
    	usleep(62500);
}


main()
{
setlocale(LC_ALL, "en_US.UTF-8");
	WINDOW * mainwin;

 if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }
int height = 29;
int width = 80;

	mvaddstr(0, 0, "+------------------------------------------------------------------------------+");

	int u;
	for(u=1;u<height;u++)
	{
		mvaddstr(u,0,"|                                                                              |");
	}
	mvaddstr(height, 0, "+------------------------------------------------------------------------------+");

	/*setvbuf (stdout, NULL, _IONBF, 0);
	printf("asds \n");*/

	
	int gridHeight= 15;
	int gridWidth= 15;
	int** grid = createGrid(gridHeight,gridWidth);
	/*grid[2][2]=1;grid[3][2]=1;grid[2][1]=1;grid[2][3]=1;*//*grid[1][2]=1;*/
	grid[1][0]=1;grid[0][2]=1;grid[1][2]=1;grid[2][2]=1;grid[2][1]=1;
/*grid[4][4]=1;grid[4][3]=1;grid[4][5]=1;*/
	makeDisp(grid, gridHeight, gridWidth);sleep(3);
	int** newgrid;
	int o = 0;
	while(o<1)
	{
	/*usleep(125000);*/
	
	newgrid = onestep(grid, gridHeight, gridWidth);
	int i;
	/*for(i=0;i<gridHeight;i++)
		free(grid[i]);
	free(grid);*/

	/*printf("\n");*/
	printGrid(newgrid, gridHeight, gridWidth);
	o++;
	grid = newgrid;
	}


wchar_t* wstr = L"\u2593";
mvwaddwstr(mainwin, 1, 1, wstr);
    	refresh();sleep(2);
    	usleep(500000);
	mvaddstr(1, 2, "e");
    	refresh();
    	usleep(500000);
	mvaddstr(1, 3, "l");
    	refresh();
    	usleep(500000);
	mvaddstr(1, 4, "l");
    	refresh();
    	usleep(500000);
	mvaddstr(1, 5, "o");
    	refresh();
    	usleep(500000);
	mvaddstr(1, 6, "!");
    	refresh();
    	usleep(500000);


	delwin(mainwin);
	endwin();
	refresh();
	
	

	return 0;
}












































