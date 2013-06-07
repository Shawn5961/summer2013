#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));

	int x = 32;
	int y = 24;

	char grid[32][24];
	int startX, startY, endX, endY;
	int loopcounter = 0;

	int i, j;

	do
	{
		startX = rand() % x;
		startY = rand() % y;

		endX = rand() % x;
		endY = rand() % y;

		loopcounter++;
	}while( startX == endX && startY == endY);

	for( i = 0; i < y; i++ )
	{
		grid[0][i] = '#';
		grid[x - 1][i] = '#';
	}

	for( j = 0; j < x; j++ )
	{
		grid[j][0] = '#';
		grid[j][y - 1] = '#';
	}

	grid[startX][startY] = 's';
	grid[endX][endY] = 'e';

	for( i = 0; i < y; i++ )
	{
		for( j = 0; j < x; j++ )
		{
			if( grid[j][i] == '#' )
				printf("#");
			else if( grid[j][i] == 's' )
				printf("s");
			else if( grid[j][i] == 'e' )
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

