#include <cstdio>
#include <iostream>
#include <cstring>

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
    
    // prints out a particular line of a board, using [] if available, and () if not
	char * getLine(int num, bool available)
	{
        char * buffer = new char[12];
        std::string format;
        
        if (available) format = "[%c] [%c] [%c]";
        else format = "(%c) (%c) (%c)";
        
		snprintf(buffer, 12, format.c_str(), pos[3 * num], pos[3 * num + 1], pos[3 * num + 2]);
        return buffer;
	}
    
    // checks to see if the player with the symbol p has won
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
    
    // prints out the individual 3x3 game board
    void printGame()
    {
        for (int i = 0; i < 3; i++)
            printf("%s\n",getLine(i, false));
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

// prints a particular row of the large 9x9 board, given the active square
void printRow(board boards[], int row, int active, bool all)
{
    int group_row = row / 3;
    int active_row = active / 3;
    int active_col = active % 3;
    
    char buffer[100];
    snprintf(buffer, 50, "%s  |  %s  |  %s\n",
             boards[3 * group_row + 0].getLine(row % 3, all || ((group_row == active_row) && (active_col == 0))),
             boards[3 * group_row + 1].getLine(row % 3, all || ((group_row == active_row) && (active_col == 1))),
             boards[3 * group_row + 2].getLine(row % 3, all || ((group_row == active_row) && (active_col == 2))));
    printf("%s", buffer);
}

// prints the entire 9x9 board
void printEntireBoard(board boards[], int active_number)
{
    for (int i = 0; i < 9; i++)
    {
        printRow(boards, i, active_number, (active_number == -1));
        if (i % 3 == 2 && i != 8)
        {
            printf("-------------+---------------+-------------\n");
        }
    }
    
}

int main(void)
{
    board boards[9];
    
    // initialize instructions
    board * b1 = &boards[3];
    
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
            move = move - '0';
            
            // flushing the buffer
            char ch;
            while ((ch = std::cin.get()) != '\n' && ch != EOF);
            
        } while (!b1->set(turn, (int)move));
        
        // places mark and displays
        b1->printGame();
        
        puts("\n");
        
        // second argument of 0...8 means that particular 3x3 is active; -1 means all are active
        printEntireBoard(boards, 3);
        
        // checks if winning move
        if (b1->checkwin(turn))
        {
            winner = turn;
            break;
        }
        
        // checks if space left to play
        if (!b1->isspace())
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