#include <cstdio>
#include <iostream>

class board {
private:
	/* 0 | 1 | 2
	 * ---------
	 * 3 | 4 | 5
	 * ---------
	 * 6 | 7 | 8
	**/
	char pos[9];
	char win = 0;

public:
	// adds X or O to position
	bool set(const char piece, const int place) 
	{
		printf("%d\n"), place;
		if (place < 0 || place > 8)
		{
			printf("invalid move\n");
			return false;
		}
		else if (pos[place] == NULL)
		{
			printf("invalid move\n");
			return false;
		}
		else
		{
			pos[place] = piece;
			return true;
		}
	}
	void line1()
	{
		printf("%c | %c | %c\n", pos[0], pos[1], pos[2]);
	}
	void line2()
	{
		printf("%c | %c | %c\n", pos[3], pos[4], pos[5]);
	}
	void line3()
	{
		printf("%c | %c | %c\n", pos[6], pos[7], pos[8]);
	}
	bool checkwin(const char p) 
	{ 
		if ((pos[0] == p && pos[1] == p && pos[2] == p) || (pos[3] == p && pos[4] == p && pos[5] == p) ||
			(pos[6] == p && pos[7] == p && pos[8] == p) || (pos[0] == p && pos[3] == p && pos[6] == p) ||
			(pos[1] == p && pos[4] == p && pos[7] == p) || (pos[2] == p && pos[5] == p && pos[8] == p) ||
			(pos[0] == p && pos[4] == p && pos[8] == p) || (pos[2] == p && pos[4] == p && pos[6] == p))
		{
			win = p;
			return true;
		}
		else return false;
	}
	bool isspace()
	{
		if (pos[0] && pos[1] && pos[2] && pos[3] && pos[4] &&
			pos[5] && pos[6] && pos[7]  && pos[8] )
			return false;
		else
			return true;
	}
};

void example()
{
	printf("Positions are as follows:\n");
	printf("0 | 1 | 2\n");
	printf("---------\n");
	printf("3 | 4 | 5\n");
	printf("---------\n");
	printf("6 | 7 | 8\n\n");
}

int main(void)
{
	// initialize instructions
	board b1;
	example();

	// prep for game
	char winner = 0;
	char turn = 'X';
	

	while (!winner)
	{
		// next moev
		printf("%c 's turn\n", turn);
		int move;
		do
		{
			// gets input, makes it usable
			move = getchar();
			move = move - '0';
			fflush(stdin);
		} while (!b1.set(turn, move));

		// places mark and displays
		b1.line1();
		b1.line2();
		b1.line3();
		// flushes stdin for next player
		

		// checks if winning move
		if (b1.checkwin(turn))
			winner = turn; 

		// checks if space left to play
		if (!b1.isspace())
			break;

		// readies for next turn
		if (turn == 'X')
			turn = 'O';
		else
			turn = 'X';
	}

	// if winner exists
	if (winner == 'X' || winner == 'O')
	{
		printf("%c wins!\n", winner);
	}

	// otherwise, tie
	else
	{
		printf("Tie!");
	}


	return 0;
}