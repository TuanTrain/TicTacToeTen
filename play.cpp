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
	int spaces = 9;

public:
	// to get around VS error
	void init(void)
	{
		pos[0] = ' ';
		pos[1] = ' ';
		pos[2] = ' ';
		pos[3] = ' ';
		pos[4] = ' ';
		pos[5] = ' ';
		pos[6] = ' ';
		pos[7] = ' ';
		pos[8] = ' ';
	}
	// adds X or O to position
	bool set(char piece, int place)
	{
		if (place < 0 || place > 8)
		{
			printf("invalid move: 0-8 only please!\n");
			return false;
		}
		else if (pos[place] != ' ')
		{
			printf("invalid move: that space is already occupied!\n");
			return false;
		}
		else
		{
			pos[place] = piece;
			spaces--;
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

	bool exists(int p)
	{
		if (pos[p] != ' ')
		{
			return true;
		}
		else
			return false;
	}
	bool checkwin(char p) 
	{         
		if ((pos[0] == p && pos[1] == p && pos[2] == p) || 
			(pos[3] == p && pos[4] == p && pos[5] == p) ||
			(pos[6] == p && pos[7] == p && pos[8] == p) || 
			(pos[0] == p && pos[3] == p && pos[6] == p) ||
			(pos[1] == p && pos[4] == p && pos[7] == p) || 
			(pos[2] == p && pos[5] == p && pos[8] == p) ||
			(pos[0] == p && pos[4] == p && pos[8] == p) || 
			(pos[2] == p && pos[4] == p && pos[6] == p))
		{
			win = p;
			return true;
		}
        
        return false;
	}
    
	bool isspace()
	{
        return spaces != 0;
	}
    
    void printGame()
    {
        line1();
        line2();
        line3();
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

int getmove()
{
	int move;
	// gets input, makes it usable
	move = getchar();
	move = move - '0';

	// flushing the buffer
	char ch;
	while ((ch = std::cin.get()) != '\n' && ch != EOF);

	return (int) move;
}

int main(void)
{
	board large;
	large.init();
	board b[9];
	// initialize instructions
	for (int i = 0; i < 9; i++)
	{
		b[i].init();
	}
	// show numbers to play
	example();

	// prep for game
	char winner = 0;
	char turn = 'X';

	// choose next board;
	int next = -1;
	
	while (true)
	{
		if (next < 0)
		{
			printf("choose a board:\n");
			do
			{
				next = getmove();
				printf("%d\n", next);
			} while (large.exists(next));
		}
		// next move
		printf("%c 's turn\n", turn);
		int move;

		do 
		{
			move = getmove();
		} while (!b[next].set(turn, move));
		

		for (int i = 0; i < 9; i++)
		{
			printf("%d\n",i);
			b[i].line1();
			printf("----------\n");
			b[i].line2();
			printf("----------\n");
			b[i].line3();
		}
		// places mark and displays

		// checks if winning move
		if (b[next].checkwin(turn))
		{
			large.set(turn, next);
			if (large.checkwin(turn))
			{
				winner = turn;
				break;
			}
		}
		
		// checks if space left to play
		if (!large.isspace())
			break;
		// readies for next turn
		if (turn == 'X')
			turn = 'O';
		else
			turn = 'X';

		// changes to next board
		if (large.exists(next))
		{
			next = -1;
		}
		else
		{
			next = move;
		}
		
	}

	// if winner exists
	if (winner == 'X' || winner == 'O')
	{
		printf("%c wins!\n", winner);
	}
	// otherwise, tie
	else
	{
		printf("Tie!\n");
	}


	return 0;
}