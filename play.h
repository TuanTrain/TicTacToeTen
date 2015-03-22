class Board {
private:
    char pos[9];
    char win;
    int spaces;
    
public:
    // constructor
    Board(void);
    
    // copy constructor
    Board(volatile Board& other);

    // adds X or O to position
    bool set(char piece, int place);
    
    bool remove(int place);
    
    // prints out a particular line of a board, using [] if available, and () if not
    char * getLine(int num, bool available);
    
    bool exists(int p);
    
    char piece(int p);
    
    // checks to see if the player with the symbol p has won
    bool checkwin(char p);
    
    bool isSpace();
    
    // prints out the individual 3x3 game board
    void printGame();
    
    int hasWin(char p);
};
