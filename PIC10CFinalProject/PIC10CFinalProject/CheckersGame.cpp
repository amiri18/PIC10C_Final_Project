#include "CheckersGame.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

Player::Player(int sym, int roy, const CheckBoard& check) : pieceCount(12), symbol(sym), royal(roy), royalCount(0) {
    
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if (check.taken(i, j, getSym())){
                pair<int, int> p = make_pair(i, j);
                location.push_back(p);
            }
        }
    }
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

void Player::det_moves(const vector<vector<int>>& board){
    moves.clear();
    pair<int, vector<pair<int,int>> > tempP;
    for (size_t i = 0; i < location.size(); ++i){
        tempP = det_NM(board, location[i]);
        moves.insert(tempP);
    }
}

void Player::getMoves() const {
    for (auto itr = moves.begin(); itr != moves.end(); ++itr){
        cout << itr->first << " -> " << itr->second << endl;
    }
}

void Player::pickMove(CheckBoard& check, Player& playerO){
    auto itr = moves.begin();
    auto it = ++moves.begin();
    if ((*itr).first == 7){
        cout << "playerX cannot move.\n";
    }
    else if ((*itr).first != (*it).first){
        if ((*itr).first == 1){
            check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
            check.validMove(itr->second[1].first, itr->second[1].second, itr->second[2].first, itr->second[2].second, *this, playerO);
        }
        else {
            check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
        }

    }
    else {
        size_t countRepeats = 0;
        while ((*itr).first == (*it).first && it != moves.end()){
            ++countRepeats;
            ++it;
        }
        int r = 0 + rand() % countRepeats;
        for (size_t i = 0; i < r; ++i){
            ++itr;
        }
        if ((*itr).first == 1){
            check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
            check.validMove(itr->second[1].first, itr->second[1].second, itr->second[2].first, itr->second[2].second, *this, playerO);
        }
        else {
            check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
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
            return '%';
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

void


CheckBoard::display() const{
    cout << "    0   1   2   3   4   5   6   7\n";
    for (size_t i = 0; i < board.size(); ++i){
        cout << "  +---+---+---+---+---+---+---+---+\n";
        cout << i << " ";
        for (size_t j = 0; j < board.size(); ++j){
            if (board[i][j] == 0){
                cout << "|%" << dis(board[i][j]) << "%";
            }
            else {
                cout << "| " << dis(board[i][j]) << " ";
            }
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
    board[Crow][Ccol] = 1;
    board[Nrow][Ncol] = sym;
    player.Move(Crow, Ccol, Nrow, Ncol);
}

void CheckBoard::RIP(int row, int col, Player& player){
    int sym = board[row][col];
    //cout << "RIP spot: (" << row << "," << col << ")\n";
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

bool CheckBoard::validMove(int Crow, int Ccol, int Nrow, int Ncol, Player& curPlayer, Player& opponent) {
    if (board[Crow][Ccol] == opponent.getRoy() || board[Crow][Ccol] == opponent.getSym()){
        return false;
    }
    
    int shift = abs(Nrow-Crow);
    if (!(shift == 1 || shift == 2)){
        cout << "The move you entered was invalid.\nPlease re-enter a valid move.\n";
        return false;
    }
    if (shift == 1 || shift == 2){
        if (!(board[Crow][Ccol] == curPlayer.getSym() || board[Crow][Ccol] == curPlayer.getRoy())){
            cout << "The move you entered was invalid.\nPlease re-enter a valid move.\n";
            return false;
        }
        if (board[Nrow][Ncol] != 1) {
            cout << "The move you entered was invalid.\nPlease re-enter a valid move.\n";
            return false;
        }
    }
    move(Crow, Ccol, Nrow, Ncol, curPlayer);
    didKill(Crow, Ccol, Nrow, Ncol, opponent);
    return true;
    
}

vector<vector<int>> CheckBoard::getBoard() const{
    return board;
}

bool CheckBoard::pieceCountZero() const{
    if (nineCount == 0){
        cout << "Player O won!";
        return true;
    }
    else if (eightCount == 0){
        cout << "Player X won!";
        return true;
    }
    else{
        return false;
    }
}
