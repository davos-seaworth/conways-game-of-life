/*Conway's Game of Life in C!
By: Andrew Braunlich and EIGHTman (http://i.imgur.com/eMUq9IQ.png), 2015
*/

#define _X_OPEN_SOURCE_EXTENDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncursesw/ncurses.h>
#include <curses.h>
#include <locale.h>
#include <wchar.h>

//https://www.youtube.com/watch?v=TIIWJ5q3NVo
int const EIGHT=8;
//http://throbs.net/fun/swf.asp?rgb.swf
int const fortyEIGHT=48;
/*
*	Creates the logical grid that the rules are executed on
*/
char** createGrid(int height, int width)
{
	char** board;
	board = malloc(width * sizeof(char*));
	int i;
	for(i=0;i<width;i++)
	{
		board[i] = malloc(height * sizeof(char));
		if(board[i] == NULL)
		{
			/* I sure hope not */
			return;
		}
	}

	return board;
}


/*
* Retrireves X coordinates of surrounding cells
*/
int* getneighborsX(int x, int gridWidth)
{
	int * arr;
	arr = malloc(EIGHT*sizeof(int));

	arr[0]=x-1;	arr[1]=x; arr[2]=x+1; arr[3]=x-1; arr[4]=x+1; arr[5]=x-1; arr[6]=x; arr[7]=x+1;
	
	for ( i = 0; i < EIGHT; i++ ) {
		if(arr[i]<0)
			arr[i]+=gridWidth;
		if(arr[i]>gridWidth-1)
			arr[i]-=gridWidth;
    }
	return arr;
	
}

/*
*	Retrieves Y coordinates of surrounding cells
*/
int* getneighborsY(int y, int gridHeight)
{
	int * arr;
	arr = malloc(EIGHT*sizeof(int));

	arr[0]=y-1; arr[1]=y-1; arr[2]=y-1; arr[3]=y; arr[4]=y; arr[5]=y+1; arr[6]=y+1; arr[7]=y+1;

	for ( i = 0; i < EIGHT; i++ ) {
		if(arr[i]<0)
			arr[i]+=gridHeight;
		if(arr[i]>gridHeight-1)
			arr[i]-=gridHeight;
    }
	return arr;
}

/*
*	Returns sum of surrounding cells
*/
int neighborsum(char** board, int* xarr, int* yarr)
{
	return board[xarr[1]][yarr[1]] + board[xarr[2]][yarr[2]] + board[xarr[3]][yarr[3]] + board[xarr[4]][yarr[4]] + board[xarr[5]][yarr[5]] + board[xarr[6]][yarr[6]] + board[xarr[7]][yarr[7]] + board[xarr[0]][yarr[0]];
}

/*
*	IF the sum of surrdounging cells is less than 2 or greater than 3, return 0(death)
*/
bool bringDeath(char** board, int gridHeight, int gridWidth, int x, int y)
{
	int* xarr = getneighborsX(x,gridWidth);
	int* yarr = getneighborsY(y,gridHeight);
	int sum = neighborsum(board, xarr, yarr);
	
	return !(sum>3||sum<2);
}
/*
*	If the sum of surrounding cells is equal to 3, return 1(life)
*/
bool createLife(char** board, int gridHeight, int gridWidth, int x, int y)
{
	int* xarr = getneighborsX(x,gridWidth);
	int* yarr = getneighborsY(y,gridHeight);
	int sum = neighborsum(board, xarr, yarr);

	return (sum==3);
	
}

/*
*	Perform one tick- applying both rules to every cell all at once
*/
char** onestep(char** board, int gridHeight, int gridWidth)
{
	char** newgen = createGrid(gridHeight, gridWidth);
	int i,j;
	for (i=0;i<gridHeight;i++)
	{
		for (j=0;j<gridWidth;j++)
		{
			if(board[j][i]==1)
				newgen[j][i]= bringDeath(board,gridHeight,gridWidth,j,i);
			else
				newgen[j][i]= createLife(board, gridHeight, gridWidth, j, i);
		}
	}
	return newgen;
}

/*
*	Translates logical grid to one suited for display, and draws to screen
*/
void displayGrid(char** board, int gridHeight, int gridWidth, WINDOW *win)
{
	int i,j;
	for (i=0;i<gridHeight;i++)
	{
		for(j=0;j<gridWidth;j++)
		{wchar_t * str;
			if(board[j][i]==1)
				str=L"\u2593\u2593";
			else
				str = L"\u2592\u2592";
		mvwaddwstr(win, i+2,(2*j)+1,str);
		}
		
	}
	refresh();
	//Time between generations
	usleep(62500);
}


int numLiving(char** board, int gridHeight, int gridWidth)
{
	int living = 0;
	int i,j;
	for(i=0;i<gridHeight;i++)
		for(j=0;j<gridWidth;j++)
			if(board[j][i]==1)
				living++;
	return living;
}

int numDead(char** board, int gridHeight, int gridWidth)
{
	int dead = 0;
	int i,j;
	for(i=0;i<gridHeight;i++)
		for(j=0;j<gridWidth;j++)
			if(board[j][i]==0)
				dead++;
	return dead;
}



main(int argc, char **argv)
{
//File input
	FILE* input;
	input = stdin;
	if(input==NULL)
		exit(EXIT_FAILURE);
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	int a, b, duration;
	int q=0;

	char** grid;
	/*
	Read in the seed from standard input
	*/
	while((read = getline(&line, &len, input))!=-1)
	{

		if(q==0)
			sscanf(line,"%d",&duration);
		else if(q==1)
			sscanf(line,"%d",&a);
		else if(q==2)
		{
			sscanf(line,"%d",&b);
			grid = createGrid(a, b);
		}
		else
		{
			int i,j;
			for (i=q-2;i<a;i++)
			{
				for (j=0;j<b;j++)
				{
					grid[j][i]=line[j]-fortyEIGHT;
				}
			}
		}
		q++;
	}

	int gridHeight= a;
	int gridWidth= b;

//Sets locale for displaying of unicode characters
	setlocale(LC_ALL, "en_US.UTF-8");
//Creates window which will be drawn to
	WINDOW * mainwin;

//If something goes wrong initializing ncurses, here we are
	if ( (mainwin = initscr()) == NULL )
	{
		fprintf(stderr, "Still hope not");
		exit(EXIT_FAILURE);
	}


//Calculate dimensions of window
	int height = gridHeight+2;;
	int width = (gridWidth*2)+2;

//Prepare top line for information display
	mvaddstr(0,0,"generation: ");
	mvaddstr(0,19,"live cells: ");
	mvaddstr(0,38,"dead cells: ");

//Upper border decoration
	int dash;
	mvaddstr(1,0,"+");
	for(dash=1;dash<width-1;dash++)
	{
		mvaddstr(1,dash,"-");
	}
	mvaddstr(1,width-1,"+");

//Horizontal border decoration
	int ht;
	for(ht=1;ht<height-1;ht++)
	{
		mvaddstr(ht+1,0,"|");
		for(dash=1;dash<width-1;dash++)
		{
			mvaddstr(ht+1,dash," ");
		}
		mvaddstr(ht+1,width-1,"|");
	}
//Bottom border decoration
	mvaddstr(height,0,"+");
	for(dash=1;dash<width-1;dash++)
	{
		mvaddstr(height,dash,"-");
	}
	mvaddstr(height,width-1,"+");

//Loop variables
	int i,j;


//Display the initial setting
	displayGrid(grid, gridHeight, gridWidth, mainwin);
//Calculate and display initial generation	
	int generation = 0;
	char gen[6];
	sprintf(gen,"%d",generation);
	mvaddstr(0,12,gen);
//Calculate and display initial number of live cells
	int living = numLiving(grid, gridHeight, gridWidth);
	char liv[6];
	sprintf(liv,"%d",living);
	mvaddstr(0,31,liv);
//Calculate and idsplay initial number of dead cells
	int dead = numDead(grid, gridHeight, gridWidth);
	char ded[6];
	sprintf(ded,"%d",dead);
	mvaddstr(0,50,ded);


//Prepare loop variables
	char** newgrid;
	int o = 0;
//Pause to allow user to see initial setting
	sleep(2);
//Main loop- operates for duration cycles, which is settable in your input file
	while(o<duration)
	{
//Calculate next generation and store in newgrid
		newgrid = onestep(grid, gridHeight, gridWidth);
//Free memory used by old generation
		for(i=0;i<gridHeight;i++)
			free(grid[i]);
		free(grid);
	
//Do generation calculation for this generation
		generation++;
		sprintf(gen,"%d",generation);
		mvaddstr(0,12,gen);
//Do living cell calculation for this generation
		living = numLiving(newgrid, gridHeight, gridWidth);
		sprintf(liv,"%d",living);
		mvaddstr(0,31,"       ");
		mvaddstr(0,31,liv);
//Do dead cell calculation for this generation
		dead = numDead(newgrid, gridHeight, gridWidth);
		sprintf(ded,"%d",dead);
		mvaddstr(0,50,"       ");
		mvaddstr(0,50,ded);
	

//Display new generation
		displayGrid(newgrid, gridHeight, gridWidth, mainwin);

		grid = newgrid;
		//mvaddstr(ht+2,0,">");refresh();
		o++;
	}
//Sleep to give time to view final grid
	sleep(5);

//Clean up window
	delwin(mainwin);
	endwin();
	refresh();	
//Exit
	return 0;
}
