#include <cstdio>
#include <iostream>

class board {
public:
	/* 1 | 2 | 3
	 * ---------
	 * 4 | 5 | 6
	 * ---------
	 * 7 | 8 | 9
	**/
	char p1 = ' ';
	char p2 = ' ';
	char p3 = ' ';
	char p4 = ' ';
	char p5 = ' ';
	char p6 = ' ';
	char p7 = ' '; 
	char p8 = ' ';
	char p9 = ' ';
	char win = 0;
	// adds X or O to position
	bool set(const char piece, const char pos) 
	{
		switch (pos)
		{
		case 1:
			if (p1 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p1 = piece;
				return true;
			}
			break;
		case 2:
			if (p2 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p2 = piece;
				return true;
			}
			break;
		case 3:
			if (p3 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p3 = piece;
				return true;
			}
			break;
		case 4:
			if (p4 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p4 = piece;
				return true;
			}
			break;
		case 5:
			if (p5 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p5 = piece;
				return true;
			}
			break;
		case 6:
			if (p6 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p6 = piece;
				return true;
			}
			break;
		case 7:
			if (p7 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p7 = piece;
				return true;
			}
			break;
		case 8:
			if (p8 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p8 = piece;
				return true;
			}
			break;
		case 9:
			if (p9 != ' ')
			{
				printf("invalid move\n");
				return false;
			}
			else
			{
				p9 = piece;
				return true;
			}
			break;
		default:
			printf("invalid move\n");
			return false;
			break;
		};
	}
	bool checkwin(const char p) 
	{ 
		if ((p1 == p && p2 == p && p3 == p) || (p4 == p && p5 == p && p6 == p) ||
			(p7 == p && p8 == p && p9 == p) || (p1 == p && p4 == p && p7 == p) ||
			(p2 == p && p5 == p && p8 == p) || (p3 == p && p6 == p && p9 == p) ||
			(p1 == p && p5 == p && p9 == p) || (p3 == p && p5 == p && p7 == p))
		{
			win = p;
			return true;
		}
		else return false;
	}
	bool isspace()
	{
		if (p1 != ' ' && p2 != ' ' && p3 != ' ' && p4 != ' ' && p5 != ' ' && 
			p6 != ' ' && p7 != ' ' && p8 != ' ' && p9 != ' ')
			return false;
		else
			return true;
	}
};

void example()
{
	printf("Positions are as follows:\n");
	printf("1 | 2 | 3\n");
	printf("---------\n");
	printf("4 | 5 | 6\n");
	printf("---------\n");
	printf("7 | 8 | 9\n\n");
}

void show(board b)
{
	printf("%c | %c | %c\n", b.p1, b.p2, b.p3);
	printf("---------\n");
	printf("%c | %c | %c\n", b.p4, b.p5, b.p6);
	printf("---------\n");
	printf("%c | %c | %c\n\n", b.p7, b.p8, b.p9);
}

int main(void)
{
	// initialize instructions
	board ttt1;
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
		} while (!ttt1.set(turn, move));

		// places mark and displays
		show(ttt1);

		// flushes stdin for next player
		

		// checks if winning move
		if (ttt1.checkwin(turn))
			winner = turn; 

		// checks if space left to play
		if (!ttt1.isspace())
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