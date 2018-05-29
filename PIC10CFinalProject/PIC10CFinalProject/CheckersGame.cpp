#include "CheckersGame.h"
#include <iostream>
using namespace std;

Player::Player(int sym, int roy, const CheckBoard& check) : pieceCount(12), symbol(sym), royal(roy), royalCount(0), startRow(0) {
    if (sym == 8){
        startRow = 7;
    }
    else {
        startRow = 0;
    }
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if (check.taken(i, j, getSym())){
                pair<int, int> p = make_pair(i, j);
                location.push_back(p);
            }
        }
    }
    
}

int Player::avaliableSpots(const CheckBoard& board) const{
    int count = 0;
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if (board.taken(i, j, 1)){
                ++count;
            };
        }
    }
    return count;
}

int Player::getSym() const {
    return symbol;
}

int Player::getRoy() const {
    return royal;
}

void Player::Move(int Crow, int Ccol, int Nrow, int Ncol) {
    for (int i = 0; i < location.size(); ++i){
        if (location[i].first == Crow && location[i].second == Ccol){
            location[i].first = Nrow;
            location[i].second = Ncol;
        }
    }
}

void Player::ate(const pair<int,int>& coord){
    for (int i = 0; i < location.size(); ++i){
        if (location[i] == coord){
            location.erase(location.begin()+i);
            
        }
    }
}

CheckBoard::CheckBoard() : nineCount(12), eightCount(12) {
    vector<int> row1 = {0,9,0,9,0,9,0,9};
    vector<int> row2 = {9,0,9,0,9,0,9,0};
    vector<int> row3 = {0,9,0,9,0,9,0,9};
    vector<int> row4 = {1,0,1,0,1,0,1,0};
    vector<int> row5 = {0,1,0,1,0,1,0,1};
    vector<int> row6 = {8,0,8,0,8,0,8,0};
    vector<int> row7 = {0,8,0,8,0,8,0,8};
    vector<int> row8 = {8,0,8,0,8,0,8,0};
    board.push_back(row1);
    board.push_back(row2);
    board.push_back(row3);
    board.push_back(row4);
    board.push_back(row5);
    board.push_back(row6);
    board.push_back(row7);
    board.push_back(row8);
}

char CheckBoard::dis(int input) const{
    switch (input) {
        case 0:
            return ' ';
        case 1:
            return ' ';
        case 8:
            return 'O';
        case 9:
            return 'X';
        case 7:
            return 'K';
        case 6:
            return 'Q';
        default:
            return ' ';
    }
}

void CheckBoard::display() const{
    cout << "    0   1   2   3   4   5   6   7\n";
    for (size_t i = 0; i < board.size(); ++i){
        cout << "  +---+---+---+---+---+---+---+---+\n";
        cout << i << " ";
        for (size_t j = 0; j < board.size(); ++j){
            cout << "| " << dis(board[i][j]) << " ";
        }
        cout << "|\n";
    }
    cout << "  +---+---+---+---+---+---+---+---+\n";
}

bool CheckBoard::taken(int row, int col, int sym) const{
    return board[row][col] == sym;
}

void CheckBoard::didKill(int Crow, int Ccol, int Nrow, int Ncol, Player& player){
    if (!((Nrow-Crow) == 1 || Nrow-Crow == -1)){
        grave(Crow, Ccol, Nrow, Ncol, player);
    }
}

void CheckBoard::move(int Crow, int Ccol, int Nrow, int Ncol, Player& player){
    int sym = board[Crow][Ccol];
    
    if (sym == 8 && Nrow == 0){
        sym = 6;
        ++player.royalCount;
    }
    if (sym == 9 && Nrow == 7){
        sym = 7;
        ++player.royalCount;
    }
    
    
    if (board[Crow][Ccol] == player.getSym() || board[Crow][Ccol] == player.getRoy()){
        board[Crow][Ccol] = 1;
    }
    if (board[Nrow][Ncol] == 1){
        board[Nrow][Ncol] = sym;
    }
    player.Move(Crow, Ccol, Nrow, Ncol);
}

void CheckBoard::RIP(int row, int col, Player& player){
    int sym = board[row][col];
    cout << "RIP spot: (" << row << "," << col << ")\n";
    board[row][col] = 1;
    pair<int, int> p = make_pair(row, col);
    switch (sym) {
        case 8:
            --eightCount;
            player.ate(p);
            break;
        case 9:
            --nineCount;
            player.ate(p);
            break;
        case 6:
            --eightCount;
            --player.royalCount;
            player.ate(p);
            break;
        case 7:
            --nineCount;
            --player.royalCount;
            player.ate(p);
            break;
    }
}

void CheckBoard::grave(int Crow, int Ccol, int Nrow, int Ncol, Player& player){
    int RIProw = 0;
    int RIPcol = 0;
    if ((Nrow - Crow) >= 0){ // moved straight
        RIProw = Crow + 1;
    }
    if ((Nrow - Crow) < 0){ // moved backward
        RIProw = Crow - 1;
    }
    if ((Ncol - Ccol) >= 0) { // moved right
        RIPcol = Ccol + 1;
    }
    if ((Ncol - Ccol) < 0) { // moved left
        RIPcol = Ccol - 1;
    }
    RIP(RIProw, RIPcol, player);
}
