#include "CheckersGame.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

// player constructor
Player::Player(int sym, int roy, const CheckBoard& check) : pieceCount(12), symbol(sym), royal(roy), royalCount(0) {
    // go through the whole board and push back all of the piece locations
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if (check.taken(i, j, getSym())){
                pair<int, int> p = make_pair(i, j);
                location.push_back(p);
            }
        }
    } // default locations
    Cur = location[0];
    New = Cur;
}

// retrieve sym value
int Player::getSym() const {
    return symbol;
}

// retrieve royal value
int Player::getRoy() const {
    return royal;
}

// update the class when a piece moves
void Player::Move(int Crow, int Ccol, int Nrow, int Ncol) {
    for (int i = 0; i < location.size(); ++i){
        // find the piece that moved
        if (location[i].first == Crow && location[i].second == Ccol){
            // update current location
            Cur = location[i];
            
            // put in its new location
            location[i].first = Nrow;
            location[i].second = Ncol;
            
            // update new location
            New = location[i];
        }
    }
}

// if the player got jumped
void Player::ate(const pair<int,int>& coord){
    // find the piece that got jumped
    for (int i = 0; i < location.size(); ++i){
        if (location[i] == coord){
            // removed it from the vector
            location.erase(location.begin()+i);
        }
    }
}

// determine the best moves for each piece and store them
void Player::det_moves(const vector<vector<int>>& board){
    
    moves.clear(); // clear past stored moves
    pair<double, vector<pair<int,int>> > tempP;
    
    // for each piece
    for (size_t i = 0; i < location.size(); ++i){
        // temporarily store the move and its value
        tempP = det_NM(board, location[i]);
        // then push it into the ordered map
        // which puts the best moves at the front
        moves.insert(tempP);
    }
}

// debugging function
void Player::getMoves() const {
    for (auto itr = moves.begin(); itr != moves.end(); ++itr){
        cout << itr->first << " -> " << itr->second << endl;
    }
}

// pick a move and play it (For the AI)
void Player::pickMove(CheckBoard& check, Player& playerO){
    // point to the beginning of the map
    auto itr = moves.begin();
    // point to the second element of the map
    auto it = ++moves.begin();
    
    // if no pieces can move then do nothing
    if ((*itr).first == 7){
        cout << "playerX cannot move.\n";
    }
    
    // If there isn't a repeat of the key value (1,2,3..etc)
    else if ((*itr).first != (*it).first){
        if ((*itr).first == 1){
            // if its a double jump
            check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
            check.validMove(itr->second[1].first, itr->second[1].second, itr->second[2].first, itr->second[2].second, *this, playerO);
        } // if its not a double jump
        
        else if ((*itr).first >= 2 && (*itr).first < 3){
            auto iter1 =  moves.begin();
            auto iter2 =  moves.begin();
            if ((*itr).second.size() == 3){
                iter1 = Find(3, 5, itr->second[1]);
                iter2 = Find(3, 5, itr->second[2]);
            }
            else {
                iter1 = Find(3, 5, itr->second[2]);
                iter2 = Find(3, 5, itr->second[3]);
            }
            double first1 = 2+(iter1->first)*0.1;
            double first2 = 2+(iter2->first)*0.1;
            if (iter1 != moves.end() && iter2 != moves.end()){
                if ((first1 < first2 && first1 < itr->first) || first1 != 2.4){
                   check.validMove(iter1->second[0].first, iter1->second[0].second, iter1->second[1].first, iter1->second[1].second, *this, playerO);
                }
                if ((first2 < first1 && first2 < itr->first) || first2 != 2.4){
                    check.validMove(iter2->second[0].first, iter2->second[0].second, iter2->second[1].first, iter2->second[1].second, *this, playerO);
                }
            }
            else if ((iter1 != moves.end() && first1 < itr->first) || (first1 != 2.4 && iter1 != moves.end())){
                check.validMove(iter1->second[0].first, iter1->second[0].second, iter1->second[1].first, iter1->second[1].second, *this, playerO);
            }
            else if ((iter2 != moves.end() && first2 < itr->first) || (first2 != 2.4 && iter2 != moves.end())){
                check.validMove(iter2->second[0].first, iter2->second[0].second, iter2->second[1].first, iter2->second[1].second, *this, playerO);
            }
            else {
                check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
            }
        }
        else {
            cout << "hi";
            check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
        }

    } // if there are repeats of the key value
    else { // count the number of repeats
        size_t countRepeats = 0;
        while ((*itr).first == (*it).first && it != moves.end()){
            ++countRepeats;
            ++it;
        } // pick a random one and play that move
        int r = 0 + rand() % countRepeats;
        for (size_t i = 1; i <= r; ++i){
            ++itr;
        }
        if ((*itr).first == 1){ // if its a double jump
            check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
            check.validMove(itr->second[1].first, itr->second[1].second, itr->second[2].first, itr->second[2].second, *this, playerO);
        }
        else if ((*itr).first >= 2 && (*itr).first < 3){
            auto iter1 =  moves.begin();
            auto iter2 =  moves.begin();
            if ((*itr).second.size() == 3){
                iter1 = Find(3, 5, itr->second[1]);
                iter2 = Find(3, 5, itr->second[2]);
            }
            else {
                iter1 = Find(3, 5, itr->second[2]);
                iter2 = Find(3, 5, itr->second[3]);
            }
            double first1 = 2+(iter1->first)*0.1;
            double first2 = 2+(iter2->first)*0.1;
            if (iter1 != moves.end() && iter2 != moves.end()){
                if ((first1 < first2 && first1 < itr->first) || first1 != 2.4){
                    check.validMove(iter1->second[0].first, iter1->second[0].second, iter1->second[1].first, iter1->second[1].second, *this, playerO);
                }
                if ((first2 < first1 && first2 < itr->first) || first2 != 2.4){
                    check.validMove(iter2->second[0].first, iter2->second[0].second, iter2->second[1].first, iter2->second[1].second, *this, playerO);
                }
            }
            else if ((iter1 != moves.end() && first1 < itr->first)|| (first1 != 2.4 && iter1 != moves.end())){
                check.validMove(iter1->second[0].first, iter1->second[0].second, iter1->second[1].first, iter1->second[1].second, *this, playerO);
            }
            else if ((iter2 != moves.end() && first2 < itr->first)|| (first2 != 2.4 && iter2 != moves.end())){
                check.validMove(iter2->second[0].first, iter2->second[0].second, iter2->second[1].first, iter2->second[1].second, *this, playerO);
            }
            else {
                check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
            }
        }
        else { // if its not a double jump
            check.validMove(itr->second[0].first, itr->second[0].second, itr->second[1].first, itr->second[1].second, *this, playerO);
        }
    }
}

// displays player X's move to the user
void Player::displayMove() const{
    cout << "piece " << Cur << " moved to " << New << endl;
}

multimap<double, vector<pair<int,int>> >::iterator Player::Find(double key_lower_bound, double key_upper_bound, const pair<int,int>& coord){
    auto it = moves.end();
    for (auto itr = moves.begin(); itr != moves.end(); ++itr){
        if (itr->first >= key_lower_bound && itr->first <= key_upper_bound){
            for (size_t i = 0; i < itr->second.size(); ++i){
                if (itr->second[i] == coord){
                    return itr;
                }
            }
        }
    }
    return it;
}

// checkerboard constructor
CheckBoard::CheckBoard() : nineCount(12), eightCount(12) {
    // create the board
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
        case 0: // null spot
            return '%';
        case 1: // free spot
            return ' ';
        case 8: // Player O piece
            return 'O';
        case 9: // Player X piece
            return 'X';
        case 7: // Player O royal
            return 'K';
        case 6: // Player X royal
            return 'Q';
        default:
            return ' ';
    }
}

void

// display the game board
CheckBoard::display() const{
    cout << "         0   1   2   3   4   5   6   7\n";
    for (size_t i = 0; i < board.size(); ++i){
        cout << "       +---+---+---+---+---+---+---+---+\n";
        cout << "     " << i << " ";
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
    cout << "       +---+---+---+---+---+---+---+---+\n\n";
}

// check if a spot is taken by a particular symbol
bool CheckBoard::taken(int row, int col, int sym) const{
    return board[row][col] == sym;
}

// check if a piece got jumped
void CheckBoard::didKill(int Crow, int Ccol, int Nrow, int Ncol, Player& player){
    // if the jumped spot was not free (and there was a piece there
    if (!((Nrow-Crow) == 1 || Nrow-Crow == -1)){
        // find the location and removed the piece
        grave(Crow, Ccol, Nrow, Ncol, player);
    }
}

// update the board when a piece has moved
void CheckBoard::move(int Crow, int Ccol, int Nrow, int Ncol, Player& player){
    // get the pieces symbol
    int sym = board[Crow][Ccol];
    
    // if an O gets to the other side,
    if (sym == 8 && Nrow == 0){
        sym = 6; // Queen it
        ++player.royalCount;
    } // if an X gets to the other side
    if (sym == 9 && Nrow == 7){
        sym = 7; // King it
        ++player.royalCount;
    }
    // then update the board by making the old spot free
    // and new spot taken by the symbol
    board[Crow][Ccol] = 1;
    board[Nrow][Ncol] = sym;
    // update the player class as well with the new location
    player.Move(Crow, Ccol, Nrow, Ncol);
}

// take care of the jumped player
void CheckBoard::RIP(int row, int col, Player& player){
    // retrieve the player's symbol value
    int sym = board[row][col];
    // then free the spot
    board[row][col] = 1;
    
    pair<int, int> p = make_pair(row, col);
    switch (sym) { // depending on the symbol
    // decrease piece count and remove it from the player class
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

// calculating the grave site
void CheckBoard::grave(int Crow, int Ccol, int Nrow, int Ncol, Player& player){
    // grave location variables
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
    // take care of the jumped player
    RIP(RIProw, RIPcol, player);
}

// check if the move is valid
bool CheckBoard::validMove(int Crow, int Ccol, int Nrow, int Ncol, Player& curPlayer, Player& opponent) {
    // can't move another player's piece
    if (board[Crow][Ccol] == opponent.getRoy() || board[Crow][Ccol] == opponent.getSym()){
        cout << "The move you entered was invalid.\nPlease re-enter a valid move.\n";
        return false;
    }
    // can only move up to 2 rows at a time
    int shift = abs(Nrow-Crow);
    if (!(shift == 1 || shift == 2)){
        cout << "The move you entered was invalid.\nPlease re-enter a valid move.\n";
        return false;
    } //
    if (shift == 1 || shift == 2){
        // if the piece is not the player's symbol value (i.e. 1 or 0)
        if (!(board[Crow][Ccol] == curPlayer.getSym() || board[Crow][Ccol] == curPlayer.getRoy())){
            cout << "The move you entered was invalid.\nPlease re-enter a valid move.\n";
            return false;
        } // if the new spot is not free
        if (board[Nrow][Ncol] != 1) {
            cout << "The move you entered was invalid.\nPlease re-enter a valid move.\n";
            return false;
        }
    } // if the move is valid, update the board/player
    move(Crow, Ccol, Nrow, Ncol, curPlayer);
    didKill(Crow, Ccol, Nrow, Ncol, opponent);
    return true;
    
}

// retrieve the board
vector<vector<int>> CheckBoard::getBoard() const{
    return board;
}

// check if someone lost
bool CheckBoard::pieceCountZero() const{
    if (nineCount == 0){ // if Player X lost
        cout << "Player O won!";
        return true;
    } // if Player O lost
    else if (eightCount == 0){
        cout << "Player X won!";
        return true;
    }
    else{ // no one has lost yet
        return false;
    }
}
