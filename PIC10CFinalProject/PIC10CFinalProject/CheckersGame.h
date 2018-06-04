#ifndef __CHECKERS_GAME__
#define __CHECKERS_GAME__

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>

using namespace std;

class CheckBoard;

// should make this derivated ... later
class Player {
private:
    int pieceCount;
    int symbol;
    int royal;
    int royalCount;
    int startRow;
    vector<pair<int, int>> location;
    multimap<int, vector<pair<int,int>> > moves;
    
    void ate(const pair<int,int>& coord);
public:
    Player(int sym, int roy, const CheckBoard& check);
    int avaliableSpots(const CheckBoard& board) const;
    int getSym() const;
    int getRoy() const;
    void Move(int Crow, int Ccol, int Nrow, int Ncol);
    void det_moves(const vector<vector<int>>& board);
    
    void getMoves() const;
    void displayPieceLoc() const;
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
    void didKill(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
    void move(int Crow, int Ccol, int Nrow, int Ncol, Player& player);
    bool taken(int row, int col, int sym) const;
public:
    CheckBoard();
    //void updateBoard(int row, int col, int sym);
    void display() const;
    bool validMove(int Crow, int Ccol, int Nrow, int Ncol, Player& curPlayer, Player& opponent);
    vector<vector<int>> getBoard() const;
    
    friend Player;
};




pair<int, vector<pair<int,int>> > det_DJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);
pair<int, vector<pair<int,int>> > det_WGDJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);
pair<int, vector<pair<int,int>> > det_J(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);
pair<int, vector<pair<int,int>> > det_WGJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);
pair<int, vector<pair<int,int>> > det_SM(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff);
pair<int, vector<pair<int,int>> > det_NM(const vector<vector<int>>& board, const pair<int,int>& piece);

pair<int, vector<pair<int,int>> > find_best_move(vector<vector<int>> board, pair<int, vector<pair<int,int>>>& stuff);
//pair<int,int> safeMove(const vector<vector<int>>& board, const pair<int,int>& piece);
ostream& operator<<(ostream& out, const pair<int,int>& coord);
ostream& operator<<(ostream& out, const vector<pair<int,int>>& pieces);

#endif 
