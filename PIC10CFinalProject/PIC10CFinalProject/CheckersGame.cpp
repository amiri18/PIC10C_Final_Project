#include "CheckersGame.h"
#include <iostream>
using namespace std;

CheckBoard::CheckBoard() : blackCount(12), whiteCount(12) {
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
            break;
        case 1:
            return ' ';
            break;
        case 8:
            return 'O';
            break;
        case 9:
            return '*';
            break;
        default:
            return ' ';
            break;
    }
}

void CheckBoard::display() const{
    for (size_t i = 0; i < board.size(); ++i){
        cout << "+---+---+---+---+---+---+---+---+\n";
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
    cout << "+---+---+---+---+---+---+---+---+\n";
    
    
}
