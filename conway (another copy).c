#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>
#include <curses.h>

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

int* getneighborsX(int x, int height)
{
	int * arr;
	arr = malloc(8*sizeof(int));

	int x1,x2,x3,x4,x5,x6,x7,x8;
	x1=x-1;	x2=x; x3=x+1; x4=x-1; x5=x+1; x6=x-1; x7=x; x8=x+1;
	if(x1<0)
		x1+=height;
	if(x2<0)
		x2+=height;
	if(x3<0)
		x3+=height;
	if(x4<0)
		x4+=height;
	if(x5<0)
		x5+=height;
	if(x6<0)
		x6+=height;
	if(x7<0)
		x7+=height;
	if(x8<0)
		x8+=height;

	if(x1>height-1)
		x1-=height;
	if(x2>height-1)
		x2-=height;
	if(x3>height-1)
		x3-=height;
	if(x4>height-1)
		x4-=height;
	if(x5>height-1)
		x5-=height;
	if(x6>height-1)
		x6-=height;
	if(x7>height-1)
		x7-=height;
	if(x8>height-1)
		x8-=height;
	arr[0]=x1;arr[1]=x2;arr[2]=x3;arr[3]=x4;arr[4]=x5;arr[5]=x6;arr[6]=x7;arr[7]=x8;
	return arr;
	
}

int* getneighborsY(int y, int width)
{
	int * arr;
	arr = malloc(8*sizeof(int));

	int y1,y2,y3,y4,y5,y6,y7,y8;
	y1=y-1; y2=y-1; y3=y-1; y4=y; y5=y; y6=y+1; y7=y+1; y8=y+1;

	if(y1<0)
		y1+=width;
	if(y2<0)
		y2+=width;
	if(y3<0)
		y3+=width;
	if(y4<0)
		y4+=width;
	if(y5<0)
		y5+=width;
	if(y6<0)
		y6+=width;
	if(y7<0)
		y7+=width;
	if(y8<0)
		y8+=width;

	if(y1>width-1)
		y1-=width;
	if(y2>width-1)
		y2-=width;
	if(y3>width-1)
		y3-=width;
	if(y4>width-1)
		y4-=width;
	if(y5>width-1)
		y5-=width;
	if(y6>width-1)
		y6-=width;
	if(y7>width-1)
		y7-=width;
	if(y8>width-1)
		y8-=width;

	arr[0]=y1;arr[1]=y2;arr[2]=y3;arr[3]=y4;arr[4]=y5;arr[5]=y6;arr[6]=y7;arr[7]=y8;
	return arr;
}

int neighborsum(int** board, int* xarr, int* yarr)
{
	int sum = board[xarr[1]][yarr[1]] + board[xarr[2]][yarr[2]] + board[xarr[3]][yarr[3]] + board[xarr[4]][yarr[4]] + board[xarr[5]][yarr[5]] + board[xarr[6]][yarr[6]] + board[xarr[7]][yarr[7]] + board[xarr[0]][yarr[0]];
	return sum;
}


bool ruleOne(int** board, int height, int width, int x, int y)
{
	bool live;
	int* xarr = getneighborsX(x, height);
	int* yarr = getneighborsY(y, width);
	int sum = neighborsum(board, xarr, yarr);
	/*if((x==3 && y==2))	
		printf("{%d}|[%d,%d]|[%d,%d]|[%d,%d]|[%d,%d]|[%d,%d]|[%d,%d]|[%d,%d]|[%d,%d]|",sum,xarr[0],yarr[0],xarr[1],yarr[1],xarr[2],yarr[2],xarr[3],yarr[3],xarr[4],yarr[4],xarr[5],yarr[5],xarr[6],yarr[6],xarr[7],yarr[7],xarr[8],yarr[8]);*/
	if(sum<2)
		live = false;
	else
		live = true;
	/*printf("%d",live);*/
	return live;
	
}

bool ruleTwo(int** board, int height, int width, int x, int y)
{
	int* xarr = getneighborsX(x,width);
	int* yarr = getneighborsY(y,height);
	int sum = neighborsum(board, xarr, yarr);
	
	if(sum>3||sum<2)
		return false;
	else
		return true;
}

bool ruleThree(int** board, int height, int width, int x, int y)
{
	int* xarr = getneighborsX(x,width);
	int* yarr = getneighborsY(y,height);
	int sum = neighborsum(board, xarr, yarr);


	if(sum==3)
		return true;
	return false;
	
}


int** onestep(int** board, int height, int width)
{
	int** newgen = createGrid(height, width);

	int i,j;
	for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
		{
			newgen[i][j]=board[i][j];
			if(board[i][j]==1)
				newgen[i][j]= ruleTwo(board,height,width,i,j);
			else{
				newgen[i][j]= ruleThree(board, height, width, i, j);
				/*printf("3453535345");*/}
		}
	}
	return newgen;
}

void printGrid(int** board, int height, int width)
{/*char st[1];sprintf(st, "%d", width);mvaddstr(0,0,st);*/
	int i,j;
	for(i=0;i<height;i++)
	{char str[width];
		for(j=0;j<width;j++)
		{
			
			str[j] = (char)(board[j][i]+48);
			/*printf("%d|",board[i][j]);*/
			
		}/*str[width+1]='\0';*/
		/*printf("\n");*/
		mvaddstr(i+1, 1, str);
    		
	}refresh();
    	usleep(62500);
}

main()
{
	WINDOW * mainwin;
/*	initscr();	*/

 if ( (mainwin = initscr()) == NULL ) {
	fprintf(stderr, "Error initialising ncurses.\n");
	exit(EXIT_FAILURE);
    }
int heightW = 29;
int widthW = 80;

	mvaddstr(0, 0, "+------------------------------------------------------------------------------+");

	int u;
	for(u=1;u<heightW;u++)
	{
		mvaddstr(u,0,"|                                                                              |");
	}
	mvaddstr(heightW, 0, "+------------------------------------------------------------------------------+");

	/*setvbuf (stdout, NULL, _IONBF, 0);
	printf("asds \n");*/
	int height= 10;
	int width= 20;
	int** grid = createGrid(height,width);
	/*grid[2][2]=1;grid[3][2]=1;grid[2][1]=1;grid[2][3]=1;*//*grid[1][2]=1;*/
	grid[1][0]=1;grid[0][2]=1;grid[1][2]=1;grid[2][2]=1;grid[2][1]=1;
/*grid[4][4]=1;grid[4][3]=1;grid[4][5]=1;*/
	printGrid(grid, height, width);
	int** newgrid;
	int o = 0;
	while(o<50)
	{
	/*usleep(125000);*/
	
	newgrid = onestep(grid, height, width);
	int i;
	/*for(i=0;i<height;i++)
		free(grid[i]);
	free(grid);*/

	/*printf("\n");*/
	printGrid(newgrid, height, width);
	o++;
	grid = newgrid;
	}

	mvaddstr(1, 1, "H");
    	refresh();
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


/*
TODO----------
CREATE GRID OF SOLID BLOCKS INSTEAD OF NUMBERS
INFORMATION ALSO
FILE INPUT
*/


















