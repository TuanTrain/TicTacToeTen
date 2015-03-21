#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

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
	board(void)
	{
        for (int i = 0; i < 9; i++)
        {
            pos[i] = ' ';
        }
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
	bool exists(int p)
	{
        return (pos[p] != ' ');

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
    
	bool isSpace()
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
    /*
    0 1 2
    3 4 5
    6 7 8
    */
    
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

int getUserInput(board boards[], board large, char player, int active)
{
    int next = active;
    
    if (active < 0)
    {
        printEntireBoard(boards, active);
        printf("Choose a board:\n");
        do
        {
            next = getmove();
            printf("%d\n", next);
        } while (large.exists(next));
    }
    
    printEntireBoard(boards, next);
    
    int move;
    
    do
    {
        move = getmove();
    } while (!boards[next].set(player, move));
    
    return move;
}

pair<int, int> computerMove(board boards[], board large, char player, int active)
{
    int next = active;
    
    if (active < 0)
    {
        printEntireBoard(boards, active);
        printf("Choose a board:\n");
        do
        {
            next = rand() % 9;
            printf("%d\n", next);
        } while (large.exists(next));
        
        printf("The computer chose board %d\n", next);
    }
    
    
    printEntireBoard(boards, next);
    
    int move;
    
    do
    {
        move = rand() % 9;
    } while (!boards[next].set(player, move));
    
    printf("The computer chose square %d\n", move);
    
    return {move, next};
}

pair<char, int> readInput(board boards[])
{
    string STRING;
    ifstream infile;
    infile.open ("setupboard.txt");
    
    int line_number = -1;
    char turn = 'X';
    int move = -1;
    
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,STRING); // Saves the line in STRING.
        
        const char * this_line = STRING.c_str();
        
        if (line_number == -1)
        {
            turn = this_line[0];
            move = atoi(& this_line[2]);
        }
        else
        {
            for (int pos = 0; pos < 9; pos++)
            {
                if (this_line[pos] != '.')
                {
                    boards[line_number / 3 * 3 + pos / 3].set(this_line[pos], line_number % 3 * 3 + pos % 3);
                }
            }
        }
        
        cout<<STRING<<endl; // Prints our STRING.
        
        line_number++;
    }
    printEntireBoard(boards, move);
    
    pair<char,int> output = {turn, move};
    
    
    cout << "Turn is: " << turn << endl;
    cout << "Active is: " << move << endl;
    
    infile.close();
    
    return output;
}

void makeLargeBoard(board boards[], board & large)
{
    for (int i = 0; i < 9; i++)
    {
        if (boards[i].checkwin('O'))
            large.set('O', i);
        else if (boards[i].checkwin('X'))
            large.set('X', i);
    }
}


int main(void)
{
	board b[9];
    
    puts("Reading Input");
    
    pair<char, int> turn_active = readInput(b);
    
    board large;
    makeLargeBoard(b, large);
    
    large.printGame();

	// show numbers to play
	example();

	// prep for game
	char winner = 0;
	char turn = turn_active.first;
    int move;

	// choose next board;
	int next = turn_active.second;
	
	while (true)
	{
        srand((int)time(NULL));
        usleep(5000);
        
        pair<int,int> move_next;
        
        if (turn == 'X')
        {
            move_next = computerMove(b, large, turn, next);
        }
        else
        {
            move_next = computerMove(b, large, turn, next);
        }
        
        move = move_next.first;
        next = move_next.second;

		// places mark and displays
        
        printf("Next is %d\n", next);

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
        
        if (! b[next].isSpace())
            large.set('E', next);
        
        puts("large is:");
        large.printGame();
		
		// checks if space left to play
		if (!large.isSpace())
			break;
		// readies for next turn
		if (turn == 'X')
			turn = 'O';
		else
			turn = 'X';

		// changes to next board
		if (large.exists(move))
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