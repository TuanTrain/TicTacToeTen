#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include "play.h"

using namespace std;

Board::Board(void)
{
    for (int i = 0; i < 9; i++)
    {
        pos[i] = ' ';
    }
    win = 0; 
    spaces = 9; 
}

// copy constructor
Board::Board(volatile Board& other )
{
    win = other.win;
    spaces = other.spaces;
    for (int i = 0; i < 9; i++)
        pos[i] = other.pos[i];
}

// adds X or O to position
bool Board::set(char piece, int place)
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


bool Board::remove(int place)
{
	if (place < 0 || place > 8)
	{
		printf("error in remove\n");
		return false;
	}
	else if (pos[place] == ' ')
	{
		printf("removing nonexistant piece\n");
		return false;
	}
	else
	{
		pos[place] = ' ';
		spaces++;
		return true;
	}
}

// prints out a particular line of a board, using [] if available, and () if not
char * Board::getLine(int num, bool available)
{
    char * buffer = new char[18];
    std::string format;
    
    if (available) format = "[%c] [%c] [%c]";
    else format = "(%c) (%c) (%c)";
    
	snprintf(buffer, 12, format.c_str(), pos[3 * num], pos[3 * num + 1], pos[3 * num + 2]);
    return buffer;
}


bool Board::exists(int p)
{
    return (pos[p] != ' ');

}

char Board::piece(int p)
{
	return (pos[p]);
}

// checks to see if the player with the symbol p has won
bool Board::checkwin(char p) 
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

bool Board::isSpace()
{
    return spaces != 0;
}

// prints out the individual 3x3 game board
void Board::printGame()
{
    for (int i = 0; i < 3; i++)
        printf("%s\n",getLine(i, false));
}

int Board::hasWin(char p)
{
    for (int i = 0; i < 9; i++)
    {
        Board new_board = *this;
        if (new_board.set(p, i) && new_board.checkwin(p))
            return i;
    }
    
    return -1;
}

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

pair<char, int> readInput(Board boards[], string file_name)
{
    string STRING;
    ifstream infile;
    infile.open (file_name.c_str());
    
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
    
    pair<char,int> output;
    output.first = turn; 
    output.second = move;
    
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

// b: board, p: piece (X or O)
void getWin(Board b, char p, int points[], int weight)
{
	for (int i = 0; i < 9; i++)
	{
		if (!b.exists(i))
		{
			b.set(p,i);
			if (b.checkwin(p))
			{
				points[i] += weight;
			}
			b.remove(i);
		}
	}
}

// will balance winning boards, blocking wins, and sending opponent to board with least of opponent's pieces
pair<int, int> computerAntuan(Board boards[], Board large, char player, int active)
{

	if (active < 0)
	{
		printEntireBoard(boards, active);
		do
		{
			active = rand() % 9;
			printf("%d\n", active);
		} while (large.exists(active));

		printf("AIntuan randomly chose board %d\n", active);
	}

	int points[9] = {50, 50, 50, 50, 50, 50, 50, 50, 50};

	printEntireBoard(boards, active);

	// disqualifies taken spots
	for (int i = 0; i < 9; i++)
	{
		if (boards[active].exists(i))
		{
			points[i] = -10;
		}
	}

	// adds point if move wins the board
	getWin(boards[active], player, points, 7);

	char other = (player == 'X') ? 'O': 'X';
	// adds point if move prevents opponent from winning board
	getWin(boards[active], other, points, 4);

	// adds points for every spot without opposing piece
	for (int i = 0; i < 9; i++)
	{
		if (points[i] > 0)
		{
			for (int j = 0; j < 9; j++)
			{
				if (boards[i].piece(j) == other)
				{
					points[i]-= 3;
				}
			}
		}
	}

	int move = -1;
	int max = 0;
	for (int i = 0; i < 9; i++)
	{
		if (points[i] > max)
		{
			move = i;
		}
	}

	printf("AIntuan chose square %d\n", move);

    boards[active].set(player, move);
    
    pair<int,int> result; 
    result.first = move; 
    result.second = active; 

	return result;
}

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
    
    pair<int,int> result; 
    result.first = move; 
    result.second = next; 

    return result;
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
        cout << "Random's Move: " << move << endl; 
    } while (!boards[next].set(player, move));
    
    pair<int,int> result; 
    result.first = move; 
    result.second = next; 

    return result;
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
    pair<int,int> (*player1)(Board[], Board, char, int) = &randomComputerMove;
    pair<int,int> (*player2)(Board[], Board, char, int) = &randomComputerMove;
    
    char results[10];
    
    for (int i = 0; i < 1; i++)
        results[i] = playGame(player1, player2);
    for (int i = 0; i < 1; i++)
        printf("Winner: %c\n", results[i]);
}