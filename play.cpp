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
    char pos[9] = {' ' , ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	char win = 0;
    int spaces = 9;

public:
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
    
	bool checkwin(char p) 
	{ 
        bool board_p[9] = {false, false, false, false, false, false, false, false, false};
        
        for (int i = 0; i < 9; i++)
        {
            if (pos[i] == p)
            {
                board_p[i] = true;
            }
        }
        
        if ((board_p[0] && board_p[1] && board_p[2]) ||
            (board_p[3] && board_p[4] && board_p[5]) ||
            (board_p[6] && board_p[7] && board_p[8]) ||
            (board_p[0] && board_p[3] && board_p[6]) ||
            (board_p[1] && board_p[4] && board_p[7]) ||
            (board_p[2] && board_p[5] && board_p[8]) ||
            (board_p[0] && board_p[4] && board_p[8]) ||
            (board_p[2] && board_p[4] && board_p[6]) )
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

int main(void)
{
	// initialize instructions
	board b1;
	example();

	// prep for game
	char winner = 0;
	char turn = 'X';
	
	while (true)
	{
		// next moev
		printf("%c 's turn\n", turn);
		char move;
		do
		{
            // gets input, makes it usable
			move = getchar();
            printf("%c", move);
			move = move - '0';
            
            // flushing the buffer
            char ch;
            while ((ch = std::cin.get()) != '\n' && ch != EOF);
            
		} while (!b1.set(turn, (int)move));

		// places mark and displays
		b1.line1();
		b1.line2();
		b1.line3();

		// checks if winning move
		if (b1.checkwin(turn))
        {
			winner = turn;
            break;
        }

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