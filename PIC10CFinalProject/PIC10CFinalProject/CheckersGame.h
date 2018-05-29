#ifndef __CHECKERS_GAME__
#define __CHECKERS_GAME__

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class CheckBoard;

class Player {
private:
    int pieceCount;
    int symbol;
    int royal;
    int royalCount;
    int startRow;
    vector<pair<int, int>> location;
    
    void ate(const pair<int,int>& coord);
public:
    Player(int sym, int roy, const CheckBoard& check);
    int avaliableSpots(const CheckBoard& board) const;
    int getSym() const;
    int getRoy() const;
    void Move(int Crow, int Ccol, int Nrow, int Ncol);
    
    friend CheckBoard;
};

class CheckBoard{
private:
    int nineCount;
    int eightCount;
    vector<vector<int>> board;
    
    char dis(int input) const;
    void RIP(int row, int col, Player& player);
    void grave(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
public:
    CheckBoard();
    void updateBoard(int row, int col, int sym);
    void display() const;
    bool taken(int row, int col, int sym) const;
    void didKill(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
    void move(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
    bool validMove(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
    
    friend Player;
};


#endif 
