#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

int** createGrid(int x, int y)
{
	int** board;
	board = malloc(x * sizeof(int*));
	int k;
	for(k=0;k<x;k++)
	{
		board[k] = malloc(y * sizeof(int));
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

int* getneighborsX(int x, int rows)
{
	int * arr;
	arr = malloc(8*sizeof(int));

	int x1,x2,x3,x4,x5,x6,x7,x8;
	x1=x-1;	x2=x; x3=x+1; x4=x-1; x5=x+1; x6=x-1; x7=x; x8=x+1;
	if(x1<0)
		x1+=rows;
	if(x2<0)
		x2+=rows;
	if(x3<0)
		x3+=rows;
	if(x4<0)
		x4+=rows;
	if(x5<0)
		x5+=rows;
	if(x6<0)
		x6+=rows;
	if(x7<0)
		x7+=rows;
	if(x8<0)
		x8+=rows;

	if(x1>rows-1)
		x1-=rows;
	if(x2>rows-1)
		x2-=rows;
	if(x3>rows-1)
		x3-=rows;
	if(x4>rows-1)
		x4-=rows;
	if(x5>rows-1)
		x5-=rows;
	if(x6>rows-1)
		x6-=rows;
	if(x7>rows-1)
		x7-=rows;
	if(x8>rows-1)
		x8-=rows;
	arr[0]=x1;arr[1]=x2;arr[2]=x3;arr[3]=x4;arr[4]=x5;arr[5]=x6;arr[6]=x7;arr[7]=x8;
	return arr;
	
}

int* getneighborsY(int y, int columns)
{
	int * arr;
	arr = malloc(8*sizeof(int));

	int y1,y2,y3,y4,y5,y6,y7,y8;
	y1=y-1; y2=y-1; y3=y-1; y4=y; y5=y; y6=y+1; y7=y+1; y8=y+1;

	if(y1<0)
		y1+=columns;
	if(y2<0)
		y2+=columns;
	if(y3<0)
		y3+=columns;
	if(y4<0)
		y4+=columns;
	if(y5<0)
		y5+=columns;
	if(y6<0)
		y6+=columns;
	if(y7<0)
		y7+=columns;
	if(y8<0)
		y8+=columns;

	if(y1>columns-1)
		y1-=columns;
	if(y2>columns-1)
		y2-=columns;
	if(y3>columns-1)
		y3-=columns;
	if(y4>columns-1)
		y4-=columns;
	if(y5>columns-1)
		y5-=columns;
	if(y6>columns-1)
		y6-=columns;
	if(y7>columns-1)
		y7-=columns;
	if(y8>columns-1)
		y8-=columns;

	arr[0]=y1;arr[1]=y2;arr[2]=y3;arr[3]=y4;arr[4]=y5;arr[5]=y6;arr[6]=y7;arr[7]=y8;
	return arr;
}

int neighborsum(int** board, int* xarr, int* yarr)
{
	int sum = board[xarr[1]][yarr[1]] + board[xarr[2]][yarr[2]] + board[xarr[3]][yarr[3]] + board[xarr[4]][yarr[4]] + board[xarr[5]][yarr[5]] + board[xarr[6]][yarr[6]] + board[xarr[7]][yarr[7]] + board[xarr[0]][yarr[0]];
	return sum;
}


bool ruleOne(int** board, int rows, int columns, int x, int y)
{
	bool live;
	int* xarr = getneighborsX(x, rows);
	int* yarr = getneighborsY(y, columns);
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

bool ruleTwo(int** board, int rows, int columns, int x, int y)
{
	int* xarr = getneighborsX(x,rows);
	int* yarr = getneighborsY(y,rows);
	int sum = neighborsum(board, xarr, yarr);
	
	if(sum>3||sum<2)
		return false;
	else
		return true;
}

bool ruleThree(int** board, int rows, int columns, int x, int y)
{
	int* xarr = getneighborsX(x,rows);
	int* yarr = getneighborsY(y,rows);
	int sum = neighborsum(board, xarr, yarr);
	
	if(sum==3)
		return true;
	return false;
	
}


int** onestep(int** board, int rows, int columns)
{
	int** newgen = createGrid(rows, columns);

	int i,j;
	for (i=0;i<rows;i++)
	{
		for (j=0;j<columns;j++)
		{
			newgen[i][j]=board[i][j];
			if(board[i][j]==1)
				newgen[i][j]= ruleTwo(board,rows,columns,i,j);
			else
				newgen[i][j]=ruleThree(board, rows, columns, i, j);
		}
	}
	return newgen;
}

void printGrid(int** board, int rows, int columns)
{
	int i,j;
	for(i=0;i<columns;i++)
	{
		for(j=0;j<rows;j++)
		{
			printf("%d", board[j][i]);printf("|");
		}
		printf("\n");
	}
}

main()
{
	setvbuf (stdout, NULL, _IONBF, 0);
	printf("asds \n");
	int rows= 10;
	int columns= 10;
	int** grid = createGrid(rows,columns);

	/*grid[2][2]=1;grid[3][2]=1;grid[2][1]=1;grid[2][3]=1;*//*grid[1][2]=1;*/
	grid[1][0]=1;grid[0][2]=1;grid[1][2]=1;grid[2][2]=1;grid[2][1]=1;

	printGrid(grid, rows, columns);
	int** newgrid;
	int o = 0;
	while(o<100)
	{
	usleep(125000);
	
	newgrid = onestep(grid, rows, columns);
	int i;
	for(i=0;i<rows;i++)
		free(grid[i]);
	free(grid);
	printf("\n");
	printGrid(newgrid, rows, columns);
	o++;
	grid = newgrid;
	}

	

	return 0;
}







