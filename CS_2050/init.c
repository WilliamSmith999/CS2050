#include "minesweeper.h"


int main(int argc, char** argv) {
    srand(time(NULL));

	if(argc != 4)
	{
		printf("Correct usage: ./a.out <number of rows> <number of columns> <number of mines>\n");
		return -1;
	}

	Board* b = randomizeBoard(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
#ifdef DEBUG
	printUncoveredBoard(b); 
	freeBoard(b); 
	return (0);
#endif
	while(b->s == PLAYING)
	{
		printBoard(b);
		printf("\nSelect a row: ");
		int r;
		scanf("%d", &r);
		while(r < 0 || r > b->numRows - 1)
		{
			printf("Invalid entry. Try again: ");
			scanf("%d", &r);
		}

		printf("Select a column: ");
		int c;
		scanf("%d", &c);
		while(c < 0 || c > b->numColumns - 1)
		{
			printf("Invalid entry. Try again: ");
			scanf("%d", &c);
		}

		//not technically needed, but in reality if the game is windowed you can't
		//select a square already chosen.
		if(b->squares[r][c].C == UNCOVERED)
		{
			printf("\nThat square is already uncovered!\n");
		}
		else
		{
			updateBoard(b, r, c);
		}
	}

	if(b->s == WON) printf("\nYou won! Congrats!\n");
	else printf("\nYou hit a mine! Oh no!\n");
	printUncoveredBoard(b);

	freeBoard(b);

	return 0;
}

void freeBoard(Board* board)
{
	//First, you need to free the field of squares.
	int i;
	for(i = 0; i < board->numRows; i++)
	{
		//The double pointer is pointing to an array of pointers, each of those have to be freed.
		free(board->squares[i]);
	}
	//Free the double pointer
	free(board->squares);
	//Free the board
	free(board);
}
Board* randomizeBoard(int rows, int columns, int numMines)
{
	//So step one is to put together the field of squares. 
	//This will be an array of pointers (rows) that will each handle
	//a single column
	//
	//This method will sync up with the print functions below. If i and j were 
	//reversed throughout, the print functions will show inverted boards.
    Square** squares = malloc(sizeof(Square*)*rows);
    int i, j;
    for(i = 0; i < rows; i++)
    {
        squares[i] = malloc(sizeof(Square)*columns);
    }
    
	//Hold the number of mines, because I will be decrementing numMines later
	int tmp = numMines;

	//Initialize each square to default values. 
	//-2 will be used in countMines
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			squares[i][j].T = NOTAMINE;
			squares[i][j].C = COVERED;
			squares[i][j].surroundingMines = -2;
		}
	}

	//Randomly select certain squares to be mines. 
	//Reselects a square if the one randomly chosen is already a mine.
    while(numMines > 0)
    {
        i = rand() % rows;
        j = rand() % columns;
        while(squares[i][j].T == MINE)
        {
            i = rand() % rows;
            j = rand() % columns;
        }
        squares[i][j].T = MINE;
        numMines--;
    }
    
	//Make the board, set up the values
	Board* b = malloc(sizeof(Board));
	b->numRows = rows;
	b->numColumns = columns;
	b->numMines = tmp;
	b->numRemaining = rows*columns - tmp;
	b->s = PLAYING;
	b->squares = squares;

   
   	//Find the first square that isn't a mine, and start the 
	//Recursion that is countMines()
	//Note the check for -2. The double for loop goes through each square to 
	//make sure all squares that aren't mines are caught. 
	//If the double for loop was left out and countMines was called once, squares completely
	//surrounded by mines will still show surroundingMines as -2.
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			if(squares[i][j].T == NOTAMINE && squares[i][j].surroundingMines == -2)
			{
				countMines(b, i, j);
			}
		}
	}
    
	return b;
}
