#ifndef __CHECKERS_GAME__
#define __CHECKERS_GAME__

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>

using namespace std;

class CheckBoard;

class Player {
private:
    // symbol value (9 or 8)
    int symbol;
    // royal value (7 or 6)
    int royal;
    // count of normal pieces
    int pieceCount;
    // count of royal pieces
    int royalCount;
    // initial location
    pair<int,int> Cur;
    // new location
    pair<int,int> New;

    // stores the location of the pieces
    vector<pair<int, int>> location;
    
    // for the AI to keep track of moves
    multimap<int, vector<pair<int,int>> > moves;
    
    /**
     updates the class when a piece is jumped
     
     @param coord , location of the piece that died
     */
    void ate(const pair<int,int>& coord);
    
public:
    /**
     player constructor
     
     @param sym , symbol (9 or 8)
     @param roy , royal (7 or 6)
     @param check , checkerboard
     */
    Player(int sym, int roy, const CheckBoard& check);
    
    /**
     retrieves the symbol
     
     @return either an 9 or 8
     */
    int getSym() const;
    
    /**
     retrieves the royal symbol
     
     @return either an 7 or 6
     */
    int getRoy() const;
    
    /**
     updates the class after a piece has been moved
     
     @param Crow , current row
     @param Ccol , current column
     @param Nrow , new row
     @param Ncol , new column
     */
    void Move(int Crow, int Ccol, int Nrow, int Ncol);
    
    /**
     determines where the AI should move (calls AI functions)
     
     @param board , the current gameboard
     */
    void det_moves(const vector<vector<int>>& board);
    
    /**
     picks a move for the AI
     
     @param check , the current gameboard
     @param playerO , player O
     */
    void pickMove(CheckBoard& check, Player& playerO);
    
    /**
     debugging fuction of the AI that display's playerX's moves
     */
    void getMoves() const;
    
    /**
     display's the player's move
     */
    void displayMove() const;
    // make the classes friends
    friend CheckBoard;
    
};

class CheckBoard{
private:
    // player X's piece count
    int nineCount;
    // player O's piece count
    int eightCount;
    // 2D vector that stores the board
    vector<vector<int>> board;
    
    /**
     helper function of display which takens in a board value and returns its respective char:
     (9->'X', 8->'O', 7->'K', 6->'Q', 0 ->'%', and 1->' '
     @param input , value
     @return the char
     */
    char dis(int input) const;
    
    /**
     takes care of the jumped piece
     
     // grave location:
     @param row , row
     @param col , column
     @param player , player of the jumped piece
     */
    void RIP(int row, int col, Player& player);
    
    /**
     determines which spot the jumped piece was at (aka the "grave")
     
     @param Crow , current row
     @param Ccol , current column
     @param Nrow , new row
     @param Ncol , new column
     @param player , the player that got jumped
     */
    void grave(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
    
    /**
     determines if a piece got jumped
     
     @param Crow , current row
     @param Ccol , current column
     @param Nrow , new row
     @param Ncol , new column
     @param player , the player that potentially got jumped
     */
    void didKill(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
    
    /**
     updates the board after a move
     
     @param Crow , current row
     @param Ccol , current column
     @param Nrow , new row
     @param Ncol , new column
     @param player , the player that moved
     */
    void move(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
    
    /**
     determines if the spot is free of taken by a certain piece
     
     @param row , row
     @param col , column
     @param sym , symbol (i.e. 1, 9, 7, 8, or 6)
     */
    bool taken(int row, int col, int sym) const;
    
public:
    /**
     checker board constructor
     */
    CheckBoard();
    
    /**
     displays the board
     */
    void display() const;
    
    /**
     determines if the move is valid
     
     @param Crow , current row
     @param Ccol , current column
     @param Nrow , new row
     @param Ncol , new column
     @param curPlayer , current player
     @param opponent , opposite player
     @return true if the move is valid, false if otherwise
     */
    bool validMove(int Crow, int Ccol, int Nrow, int Ncol, Player& curPlayer, Player& opponent);
    
    /**
     retrieves the board
     
     @return the board
     */
    vector<vector<int>> getBoard() const;
    
    /**
     determins if a player ran out of pieces (and that the other player won)
     
     @return true if either player X or O piece count = 0, otherwise return false
     */
    bool pieceCountZero() const;
    
    // make the classes friends
    friend Player;
};

//////////////////////////////////////////
//      non-class (AI) functions!!!     //
//////////////////////////////////////////

/**
 deteremines if the piece can double jump the other player's pieces
 
 @param board , current gameboard
 @param stuff , current info
 @return <1, piece location/moves> if the piece can jump, otherwise call det_WGDJ(board, stuff); and transerfer over the current info
 */
pair<int, vector<pair<int,int>> > det_DJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);

/**
 deteremines if the piece will get double jumped
 
 @param board , current gameboard
 @param stuff , current info
 @return <2, piece location/SAFE move> if the piece will get double jumped, otherwise call det_J(board, stuff); and transerfer over the current info
 */
pair<int, vector<pair<int,int>> > det_WGDJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);

/**
 deteremines if the piece can jump the other player's piece
 
 @param board , current gameboard
 @param stuff , current info
 @return <3, piece location/move> if the piece can jump, otherwise call det_WGJ(board, stuff); and transerfer over the current info
 */
pair<int, vector<pair<int,int>> > det_J(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);

/**
 deteremines if the piece will get jumped
 
 @param board , current gameboard
 @param stuff , current info
 @return <4, piece location/SAFE move> if the piece will get jumped, otherwise call det_SM(board, stuff); and transerfer over the current info
 */
pair<int, vector<pair<int,int>> > det_WGJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);

/**
 determines if there is a safe move
 
 @param board , current gameboard
 @param stuff , current info
 @return <5, piece location/move> if there is a safe move, otherwise call find_best_move(board, stuff); and transfer over the current info
 */
pair<int, vector<pair<int,int>> > det_SM(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);

/**
 find's the AI's best move
 
 @param board , COPY of the board
 @param stuff , reference of the container that holds current piece's location
 @return <6, piece location/move>, the same container with the best move
 */
pair<int, vector<pair<int,int>> > find_best_move(vector<vector<int>> board, pair<int, vector<pair<int,int>>>& stuff);

/**
 determine if there are no moves
 
 @param board , current gameboard
 @param piece , piece being evaluated
 @return <7, piece location> if the piece cannot move, otherwise call det_DJ(stuff); and transfer over the current info (i.e. board and piece location)
 */
pair<int, vector<pair<int,int>> > det_NM(const vector<vector<int>>& board, const pair<int,int>& piece);


//////////////////////////////////////////
//   non-class (overloaded) functions   //
//////////////////////////////////////////


/**
 operator overload << on std::pair<int,int> (displays coordinate pairs)
 
 @param out , ostream object
 @param coord , the coordinate pair
 @return teh ostream object
 */
ostream& operator<<(ostream& out, const pair<int,int>& coord);

/**
 operator overload << on std::vector<std::pair<int,int>> (displays several pieces)
 
 @param out , ostream object
 @param pieces , the coordinate pairs
 @return ostream object
 */
ostream& operator<<(ostream& out, const vector<pair<int,int>>& pieces);

#endif 
