#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

class Board {
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
	// constructor
	Board(void)
	{
        for (int i = 0; i < 9; i++)
        {
            pos[i] = ' ';
        }
	}
    
    // copy constructor
    Board(volatile Board& other )
    {
        win = other.win;
        spaces = other.spaces;
        for (int i = 0; i < 9; i++)
            pos[i] = other.pos[i];
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
        char * buffer = new char[18];
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
    
    int hasWin(char p)
    {
        for (int i = 0; i < 9; i++)
        {
            Board new_board = *this;
            if (new_board.set(p, i) && new_board.checkwin(p))
                return i;
        }
        
        return -1;
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
void printRow(Board boards[], int row, int active, bool all)
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
    snprintf(buffer, 50, "%s  |  %s  |  %s \n",
             boards[3 * group_row + 0].getLine(row % 3, all || ((group_row == active_row) && (active_col == 0))),
             boards[3 * group_row + 1].getLine(row % 3, all || ((group_row == active_row) && (active_col == 1))),
             boards[3 * group_row + 2].getLine(row % 3, all || ((group_row == active_row) && (active_col == 2))));
    printf("%s", buffer);
}

// prints the entire 9x9 board
void printEntireBoard(Board boards[], int active_number)
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

pair<int, int> randomComputerMove(Board boards[], Board large, char player, int active);

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

pair<char, int> readInput(Board boards[], char * file_name)
{
    string STRING;
    ifstream infile;
    infile.open (file_name);
    
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

void makeLargeBoard(Board boards[], Board & large)
{
    for (int i = 0; i < 9; i++)
    {
        if (boards[i].checkwin('O'))
            large.set('O', i);
        else if (boards[i].checkwin('X'))
            large.set('X', i);
    }
}

/*
 * AI Functions
 *
 * Return (move,next) where move is the square chosen within the 3x3 
 * and next is the board that the current move was played on. It will be 
 * the same as the parameter active, unless a choice of boards was given.
 *
 * Don't forget to modify the corresponding board in boards too!!
*/

pair<int, int> computerEvan(Board boards[], Board large, char player, int active)
{
    if (active -1)
    {
        for (int i = 0; i < 9; i++)
        {
            int choice = boards[i].hasWin(player);
            if (choice != -1)
            {
                boards[i].set(player, choice);
                return {i, choice};
            }
        }
        
        return randomComputerMove(boards, large, player, active);
    }
    
    int choice = boards[active].hasWin(player);
    if ( choice != -1)
    {
        boards[active].set(player, choice);
    }
    
    int safe_moves[10];
    int counter = 0;
    
    for (int i = 0; i < 9; i++)
    {
        if (!boards[active].exists(i) && !boards[i].hasWin((player == 'X') ? 'O' : 'X'))
        {
            safe_moves[counter] = i;
            counter++;
        }
    }
    
    if (counter == 0)
    {
        return {0, active};
    }
    
    int random_move = safe_moves[rand() % counter];
    
    boards[active].set(player, random_move);
    
    return {random_move, active};
}

pair<int, int> computerAntuan(Board boards[], Board large, char player, int active);

pair<int, int> getUserInput(Board boards[], Board large, char player, int active)
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
    
    return {move, next};
}

pair<int, int> randomComputerMove(Board boards[], Board large, char player, int active)
{
    int next = active;
    
    if (active < 0)
    {
        do
        {
            next = rand() % 9;
            printf("%d\n", next);
        } while (large.exists(next));
    }
    
    
    printEntireBoard(boards, next);
    
    int move;
    
    do
    {
        move = rand() % 9;
    } while (!boards[next].set(player, move));
    
    return {move, next};
}

char playGame(pair<int,int>(*alg1)(Board[], Board, char, int),
              pair<int,int>(*alg2)(Board[], Board, char, int))
{
    Board b[9];
    
    puts("Reading Input");
    
    pair<char, int> turn_active = readInput(b, "emptyboard.txt");
    
    Board large;
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
            move_next = (*alg1)(b, large, turn, next);
        }
        else
        {
            move_next = (*alg2)(b, large, turn, next);
        }
        
        move = move_next.first;
        next = move_next.second;
        
        printf("Move is %d, Next is %d\n", move, next);
        printEntireBoard(b, next);
        
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
        return winner;
    }
    // otherwise, tie
    return 'T';

}

int main(void)
{
    pair<int,int> (*player1)(Board[], Board, char, int) = &computerEvan;
    pair<int,int> (*player2)(Board[], Board, char, int) = &randomComputerMove;
    printf("Game Result: %c\n", playGame(player1, player2));
}