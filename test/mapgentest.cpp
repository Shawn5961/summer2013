#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WALL	0
#define PATH	1
#define START	2
#define END		3

int main()
{
	srand(time(NULL));

	int x, y;

	int grid[32][24];
	int startX, startY, endX, endY;
	int loopcounter = 0;

	int i, j;

	do
	{
		startX = rand() % 30 + 1;
		startY = rand() % 22 + 1 ;

		endX = rand() % 30 + 1;
		endY = rand() % 22 + 1;

		loopcounter++;
	}while( (startX == endX && startY == endY) );

	for( y = 0; y < 24; y++ )
	{
		for( x = 0; x < 32; x++ )
		{
			grid[x][y] = 1;
		}
	}

	for( x = 0; x < 32; x++ )
	{
		grid[x][0] = 0;
		grid[x][23] = 0;
	}

	for( y = 0; y < 24; y++ )
	{
		grid[0][y] = 0;
		grid[31][y] = 0;
	}

	grid[startX][startY] = 2;
	grid[endX][endY] = 3;

	for( y = 0; y < 24; y++ )
	{
		for( x = 0; x < 32; x++ )
		{
			if( grid[x][y] ==  0)
				printf("#");
			else if( grid[x][y] == 2 )
				printf("s");
			else if( grid[x][y] == 3 )
				printf("e");
			else
				printf(" ");
		}
		printf("\n");
	}

	printf("Start: %d, %d\n", startX, startY);
	printf("End:   %d, %d\n", endX, endY);
	printf("# of runs: %d\n", loopcounter);
}

