#include "CheckersGame.h"
#include <cmath>
using namespace std;

/****************************************/
/*            AI functions!!!           */
/*                                      */
/*  key value 1: can double jump        */
/*  key value 2: will be double jumped  */
/*  key value 3: can jump               */
/*  key value 4: will be jumped         */
/*  key value 5: safe move              */
/*  key value 6: risky move             */
/*                                      */
/****************************************/

// determines if the Player X can double jump Player O
pair<double, vector<pair<int,int>> > det_DJ(const vector<vector<int>>& board, pair<double, vector<pair<int,int>> >& stuff){
    // if recursion has NOT happened...
    if (stuff.first < 8){
        // set the key value to 1!
        stuff.first = 1;
    }
    else {
        stuff.first = 8.1;
    }
    // potential future moves
    pair<int,int> mid;
    pair<int,int> end;
    // get the current location
    int row = stuff.second[0].first;
    int col = stuff.second[0].second;
    
    /***** if the piece is a K *****/
    
    if (board[row][col] == 7) {
        
        // if the piece is in the bottom left quarter of the board:
        if (row > 3 && col < 4){
            // check up right 2jump
            if ((board[row-1][col+1] == 8 || board[row-1][col+1] == 6) && board[row-2][col+2] == 1 && (board[row-3][col+3] == 8 || board[row-3][col+3] == 6) && board[row-4][col+4] == 1){ // get the moves, store them, return them
                mid = make_pair(row-2, col+2);
                end = make_pair(row-4, col+4);
                stuff.second.push_back(mid);
                stuff.second.push_back(end);
                return stuff;
            } // check straight up right 2jump
            if ((board[row-1][col+1] == 8 || board[row-1][col+1] == 6) && board[row-2][col+2] == 1 && (board[row-3][col+1] == 8 || board[row-3][col+1] == 6) && board[row-4][col] == 1){ // get the moves, store them, return them
                mid = make_pair(row-2, col+2);
                end = make_pair(row-4, col);
                stuff.second.push_back(mid);
                stuff.second.push_back(end);
                return stuff;
            } // if the piece is in the third or fourth column:
            if (col == 3 || col == 2){
                // check straight up left 2jump
                if ((board[row-1][col-1] == 8 || board[row-1][col-1] == 6) && board[row-2][col-2] == 1 && (board[row-3][col-1] == 8 || board[row-3][col-1] == 6) && board[row-4][col] == 1){ // get the moves, store them, return them
                    mid = make_pair(row-2, col-2);
                    end = make_pair(row-4, col);
                    stuff.second.push_back(mid);
                    stuff.second.push_back(end);
                    return stuff;
                }
            }
        }
        
        // if the piece is in the bottom right quarter of the board:
        if (row > 3 && col > 3){
            // check up left 2jump
            if ((board[row-1][col-1] == 8 || board[row-1][col-1] == 6) && board[row-2][col-2] == 1 && (board[row-3][col-3] == 8 || board[row-3][col-3] == 6) && board[row-4][col-4] == 1){ // get the moves, store them, return them
                mid = make_pair(row-2, col-2);
                end = make_pair(row-4, col-4);
                stuff.second.push_back(mid);
                stuff.second.push_back(end);
                return stuff;
            } // check straight up left 2jump
            if ((board[row-1][col-1] == 8 || board[row-1][col-1] == 6) && board[row-2][col-2] == 1 && (board[row-3][col-1] == 8 || board[row-3][col-1] == 6) && board[row-4][col] == 1){ // get the moves, store them, return them
                mid = make_pair(row-2, col-2);
                end = make_pair(row-4, col);
                stuff.second.push_back(mid);
                stuff.second.push_back(end);
                return stuff;
            } // if the piece is in the fifth or sixth column
            if (col == 4 || col == 5){
                // check straight up right 2jump
                if ((board[row-1][col+1] == 8 || board[row-1][col+1] == 6) && board[row-2][col+2] == 1 && (board[row-3][col+1] == 8 || board[row-3][col+1] == 6) && board[row-4][col] == 1){ // get the moves, store them, return them
                    mid = make_pair(row-2, col+2);
                    end = make_pair(row-4, col);
                    stuff.second.push_back(mid);
                    stuff.second.push_back(end);
                    return stuff;
                }
            }
        }
    } /***** if the piece is a K OR an X *****/
    
    // if the piece is in the top left quarter of the board:
    if (row < 4 && col < 4){
        // check down right 2jump
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row+2][col+2] == 1 && (board[row+3][col+3] == 8 || board[row+3][col+3] == 6) && board[row+4][col+4] == 1){ // get the moves, store them, return them
            mid = make_pair(row+2, col+2);
            end = make_pair(row+4, col+4);
            stuff.second.push_back(mid);
            stuff.second.push_back(end);
            return stuff;
        } // check straight down right 2jump
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row+2][col+2] == 1 && (board[row+3][col+1] == 8 || board[row+3][col+1] == 6) && board[row+4][col] == 1){ // get the moves, store them, return them
            mid = make_pair(row+2, col+2);
            end = make_pair(row+4, col);
            stuff.second.push_back(mid);
            stuff.second.push_back(end);
            return stuff;
        } // if the piece is in the third or fourth column
        if (col == 3 || col == 2){
            // check straight down left 2jump
            if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row+2][col-2] == 1 && (board[row+3][col-1] == 8 || board[row+3][col-1] == 6) && board[row+4][col] == 1){ // get the moves, store them return them
                mid = make_pair(row+2, col-2);
                end = make_pair(row+4, col);
                stuff.second.push_back(mid);
                stuff.second.push_back(end);
                return stuff;
            }
        }
    }
    
    // if the piece is in the top right quarter of the board:
    if (row < 4 && col > 3){
        // check down left 2jump
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row+2][col-2] == 1 && (board[row+3][col-3] == 8 || board[row+3][col-3] == 6) && board[row+4][col-4] == 1){ // get the moves, store them, return them
            mid = make_pair(row+2, col-2);
            end = make_pair(row+4, col-4);
            stuff.second.push_back(mid);
            stuff.second.push_back(end);
            return stuff;
        } // check straight down left 2jump
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row+2][col-2] == 1 && (board[row+3][col-1] == 8 || board[row+3][col-1] == 6) && board[row+4][col] == 1){ // get the moves, store them, return them
            mid = make_pair(row+2, col-2);
            end = make_pair(row+4, col);
            stuff.second.push_back(mid);
            stuff.second.push_back(end);
            return stuff;
        } // if the piece is in the fifth or sixth column
        if (col == 4 || col == 5){
            // check straight down right 2jump
            if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row+2][col+2] == 1 && (board[row+3][col+1] == 8 || board[row+3][col+1] == 6) && board[row+4][col] == 1){ // get the moves, store them, return them
                mid = make_pair(row+2, col+2);
                end = make_pair(row+4, col);
                stuff.second.push_back(mid);
                stuff.second.push_back(end);
                return stuff;
            }
        }// if the piece cannot double jump,
    }// go on to see if it will get double jumped
    return det_WGDJ(board, stuff);
}




// determines if the Player X will get double jumped by Player O
pair<double, vector<pair<int,int>> > det_WGDJ(const vector<vector<int>>& board, pair<double, vector<pair<int,int>>>& stuff){
    // if recursion has NOT happened...
    if (stuff.first == 1){
        // set the key value to 2
        stuff.first = 2;
    }
    else if (stuff.first == 7){
        stuff.first = 0;
    }
    else {
        stuff.first = 8.2;
    }
    // free spots
    pair<int,int> freeMid;
    pair<int,int> freeEnd;
    pair<int,int> midPiece;
    // get the current location
    int row = stuff.second[0].first;
    int col = stuff.second[0].second;
    
    // if the piece is at the bottom left quarter of the board:
    if (row > 2 && row < 7 && col > 0 && col < 5){
        // if the piece can get up right 2jumped
        if((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col+2] == 9 || board[row-2][col+2] == 7) && board[row-3][col+3] == 1){
            freeMid = make_pair(row-1, col+1);
            freeEnd = make_pair(row-3, col+3);
            midPiece = make_pair(row-2, col+2);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
        // if the piece can get straight up right 2jumped
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col-1] == 1){
            freeMid = make_pair(row-1, col+1);
            freeEnd = make_pair(row-3, col-1);
            midPiece = make_pair(row-2, col);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
        // if the piece can get straight up left 2jumped
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col+1] == 1){
            freeMid = make_pair(row-1, col-1);
            freeEnd = make_pair(row-3, col+1);
            midPiece = make_pair(row-2, col);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
    }
    // if the piece is at the bottom right quarter of the board:
    if (row > 2 && row < 7 && col < 7 && col > 2){
        // if the piece can get up left 2jumped
        if((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col-2] == 9 || board[row-2][col-2] == 7) && board[row-3][col-3] == 1){
            freeMid = make_pair(row-1, col-1);
            freeEnd = make_pair(row-3, col-3);
            midPiece = make_pair(row-2, col-2);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
        // if the piece can get straight up left 2jumped
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col+1] == 1){
            freeMid = make_pair(row-1, col-1);
            freeEnd = make_pair(row-3, col+1);
            midPiece = make_pair(row-2, col);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
        // if the piece can get straight up right 2jumped
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col-1] == 1){
            freeMid = make_pair(row-1, col+1);
            freeEnd = make_pair(row-3, col-1);
            midPiece = make_pair(row-2, col);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
    }
    /////////////////////////////////////////////////////////////
    // if there is a Q behind the piece, need to check the opposite direction!
        
    // if the piece is at the top left quarter of the board:
    if (row > 0 && row < 5 && col > 0 && col < 5){
        // if the piece can get down right 2jumped
        if(board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col+2] == 9 || board[row+2][col+2] == 7) && board[row+3][col+3] == 1){
            freeMid = make_pair(row+1, col+1);
            freeEnd = make_pair(row+3, col+3);
            midPiece = make_pair(row+2, col+2);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
        // if the piece can get straight down right 2jumped
        if (board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col-1] == 1){
            freeMid = make_pair(row+1, col+1);
            freeEnd = make_pair(row+3, col-1);
            midPiece = make_pair(row+2, col);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
        // if the piece can get straight down left 2jumped
        if (board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col+1] == 1){
            freeMid = make_pair(row+1, col-1);
            freeEnd = make_pair(row+3, col+1);
            midPiece = make_pair(row+2, col);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
    }
    // if the piece is at the bottom right quarter of the board:
    if (row > 0 && row < 5 && col < 7 && col > 2){
        // if the piece can get down left 2jumped
        if(board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col-2] == 9 || board[row+2][col-2] == 7) && board[row+3][col-3] == 1){
            freeMid = make_pair(row+1, col-1);
            freeEnd = make_pair(row+3, col-3);
            midPiece = make_pair(row+2, col-2);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
        // if the piece can get straight down left 2jumped
        if (board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col+1] == 1){
            freeMid = make_pair(row+1, col-1);
            freeEnd = make_pair(row+3, col+1);
            midPiece = make_pair(row+2, col);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
        // if the piece can get straight down right 2jumped
        if (board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col-1] == 1){
            freeMid = make_pair(row+1, col-1);
            freeEnd = make_pair(row+3, col-1);
            midPiece = make_pair(row+2, col);
            stuff.second.push_back(freeMid);
            stuff.second.push_back(freeEnd);
            stuff.second.push_back(midPiece);
            return find_best_move(board, stuff);
        }
    }
    if (stuff.first == 0){
        stuff.first = 7;
        //return det_WGJ(board, stuff);
        return stuff;
    }
    else {
        return det_J(board, stuff);
    }
}

pair<double, vector<pair<int,int>> > det_J(const vector<vector<int>>& board, pair<double, vector<pair<int,int>>>& stuff){
    if (stuff.first < 8){
        stuff.first = 3;
    }
    else {
        stuff.first = 8.3;
    }
    
    pair<int,int> end;
    
    int row = stuff.second[0].first;
    int col = stuff.second[0].second;
    
    // check for down right and left jumps:
    if (row < 6){
        if (col < 6){ // right jumps
            if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row+2][col+2] == 1){
                end = make_pair(row+2, col+2);
                stuff.second.push_back(end);
                return stuff;
            }
        }
        if (col > 1){ // left jumps
            if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row+2][col-2] == 1){
                end = make_pair(row+2, col-2);
                stuff.second.push_back(end);
                return stuff;
            }
        }
    }
    /////////////////////////////////////////////////////////////
    // if the piece is a K, need to check the opposite direction!
    
    // check for up right and left jumps:
    if (board[row][col] == 7 && row > 1){
        if (col < 6){ //right jumps
            if ((board[row-1][col+1] == 8 || board[row-1][col+1] == 6) && board[row-2][col+2] == 1){
                end = make_pair(row-2, col+2);
                stuff.second.push_back(end);
                return stuff;
            }
        }
        if (col > 1){ // left jumps
            if ((board[row-1][col-1] == 8 || board[row-1][col-1] == 6) && board[row-2][col-2] == 1){
                end = make_pair(row-2, col-2);
                stuff.second.push_back(end);
                return stuff;
            }
        }
    }
    return det_WGJ(board, stuff);
}

pair<double, vector<pair<int,int>> > det_WGJ(const vector<vector<int>>& board, pair<double, vector<pair<int,int>>>& stuff){
    if (stuff.first < 8){
        stuff.first = 4;
    }
    else {
        stuff.first = 8.4;
    }
    
    int row = stuff.second[0].first;
    int col = stuff.second[0].second;
    
    // if the piece is in range to get jumped:
    if (row > 0 && row < 7 && col > 0 && col < 7){
        // can it get up right jumped
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1){
            return find_best_move(board, stuff);
        } // can it get up left jumped
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1){
            return find_best_move(board, stuff);
        } // can it get down right jumped
        if (board[row-1][col-1] == 6 && board[row+1][col+1] == 1){
            return find_best_move(board, stuff);
        } // can it get down left jumped
        if (board[row-1][col+1] == 6 && board[row+1][col-1] == 1){
            return find_best_move(board, stuff);
        }
    }
    if (stuff.first == 7) {
        return stuff;
    }
    else {
        return det_SM(board, stuff);
    }
}

pair<double, vector<pair<int,int>> > det_SM(const vector<vector<int>>& board, pair<double, vector<pair<int,int>>>& stuff){
    if (stuff.first < 8){
        stuff.first = 5;
    }
    else {
        stuff.first = 8.5;
    }
    
    pair<int,int> end;
    
    int row = stuff.second[0].first;
    int col = stuff.second[0].second;
    
    
    /////////////////////////////////////////////////////////////
    // if the piece is a K, need to check the opposite direction!
    // check the bottom edges:
    if (board[row][col] == 7) {
        if (row == 1 && col == 0 && board[row-1][col+1] == 1){
            end = make_pair(row-1, col+1);
            stuff.second.push_back(end);
            return stuff;
        }
        if (row == 1 && col > 0 && board[row-1][col+1] == 1){
            end = make_pair(row-1, col+1);
            stuff.second.push_back(end);
            return stuff;
        }
        if (row == 1 && col > 0 && board[row-1][col-1] == 1){
            end = make_pair(row-1, col-1);
            stuff.second.push_back(end);
            return stuff;
        } // check safe move right in middle of board:
        if (row > 1 && col < 6 && board[row-1][col+1] == 1 && (board[row-2][col+2] == 1 || board[row-2][col+2] == 8)) {
            if (board[row-2][col] == 1 && board[row][col+2] == 1){
                end = make_pair(row-1, col+1);
                stuff.second.push_back(end);
                return stuff;
            }
            if (board[row-2][col] != 1 && board[row][col+2] != 1){
                end = make_pair(row-1, col+1);
                stuff.second.push_back(end);
                return stuff;
            }
            if (board[row-2][col] == 1 && (board[row][col+2] == 9 || board[row][col+2] == 7)){
                end = make_pair(row-1, col+1);
                stuff.second.push_back(end);
                return stuff;
            }
            if ((board[row-2][col] == 9 || board[row-2][col] == 7) && board[row][col+2] == 1){
                end = make_pair(row-1, col+1);
                stuff.second.push_back(end);
                return stuff;
            }
        } // check safe move left in middle of board
        if (row > 1 && col > 1 && board[row-1][col-1] == 1 && (board[row-2][col-2] == 1 || board[row-2][col-2] == 8)) {
            if (board[row-2][col] == 1 && board[row][col-2] == 1){
                end = make_pair(row-1, col-1);
                stuff.second.push_back(end);
                return stuff;
            }
            if (board[row-2][col] != 1 && board[row][col-2] != 1){
                end = make_pair(row-1, col-1);
                stuff.second.push_back(end);
                return stuff;
            }
            if (board[row-2][col] == 1 && (board[row][col-2] == 9 || board[row][col-2] == 7)){
                end = make_pair(row-1, col-1);
                stuff.second.push_back(end);
                return stuff;
            }
            if ((board[row-2][col] == 9 || board[row-2][col] == 7) && board[row][col-2] == 1){
                end = make_pair(row-1, col-1);
                stuff.second.push_back(end);
                return stuff;
            }
        }
    }
    
    // check the bottom edges:
    if (row == 6 && col == 7 && board[row+1][col-1] == 1){
        end = make_pair(row+1, col-1);
        stuff.second.push_back(end);
        return stuff;
    }
    if (row == 6 && col < 7 && board[row+1][col+1] == 1){
        end = make_pair(row+1, col+1);
        stuff.second.push_back(end);
        return stuff;
    }
    if (row == 6 && col < 7 && board[row+1][col-1] == 1){
        end = make_pair(row+1, col-1);
        stuff.second.push_back(end);
        return stuff;
    } // check the left edge:
    if (row < 7 && col == 1 && board[row+1][col-1] == 1) {
        end = make_pair(row+1, col-1);
        stuff.second.push_back(end);
        return stuff;
    } // check the right edge:
    if (row < 7 && col == 6 && board[row+1][col+1] == 1) {
        end = make_pair(row+1, col+1);
        stuff.second.push_back(end);
        return stuff;
    } ////////// NEW
    if (row < 6 && col == 6 && board[row+1][col-1] == 1 && board[row+2][col-2]%2 != 0 && board[row+1][col+1] == 1) {
        end = make_pair(row+1, col+1);
        stuff.second.push_back(end);
        return stuff;
    } ///////////////
    // check safe move right in middle of board:
    if (row < 6 && col < 6 && board[row+1][col+1] == 1 && board[row+2][col+2]%2 != 0) {
        if (board[row+2][col] == 1 && board[row][col+2] == 1){
            end = make_pair(row+1, col+1);
            stuff.second.push_back(end);
            return stuff;
        }
        if (board[row+2][col] != 1 && board[row][col+2] != 1){
            end = make_pair(row+1, col+1);
            stuff.second.push_back(end);
            return stuff;
        }
        if (board[row+2][col] == 1 && (board[row][col+2] == 9 || board[row][col+2] == 7)){
            end = make_pair(row+1, col+1);
            stuff.second.push_back(end);
            return stuff;
        }
        if ((board[row+2][col] == 9 || board[row+2][col] == 7) && board[row][col+2] == 1){
            end = make_pair(row+1, col+1);
            stuff.second.push_back(end);
            return stuff;
        }
    }
//    if (row < 6 && col < 6 && board[row+1][col+1] == 1 && (board[row+2][col+2] == 9 || board[row+2][col+2] == 7)){
//        if ((board[row+2][col] != 8 || board[row+2][col] != 6) && board[row][col+2] != 6){
//            end = make_pair(row+1, col+1);
//            stuff.second.push_back(end);
//            return stuff;
//        }
//    }
    
    // check safe move left in middle of board
    if (row < 6 && col > 1 && board[row+1][col-1] == 1 && board[row+2][col-2]%2 != 0) {
        if (board[row+2][col] == 1 && board[row][col-2] == 1){
            end = make_pair(row+1, col-1);
            stuff.second.push_back(end);
            return stuff;
        }
        if (board[row+2][col] != 1 && board[row][col-2] != 1){
            end = make_pair(row+1, col-1);
            stuff.second.push_back(end);
            return stuff;
        }
        if (board[row+2][col] == 1 && (board[row][col-2] == 9 || board[row][col-2] == 7)){
            end = make_pair(row+1, col-1);
            stuff.second.push_back(end);
            return stuff;
        }
        if ((board[row+2][col] == 9 || board[row+2][col] == 7) && board[row][col-2] == 1){
            end = make_pair(row+1, col-1);
            stuff.second.push_back(end);
            return stuff;
        }
    }
    
    // if there are no good moves, return 6 to suggest finding the best move
    if (stuff.first < 8){
        stuff.first = 6;
    }
    else {
        stuff.first = 8.6;
    }
    return find_best_move(board, stuff);
}

// return 7 if the piece cannot move, or else call det_safe_move
pair<double, vector<pair<int,int>> > det_NM(const vector<vector<int>>& board, pair<int,int>& piece){
    pair<double, vector<pair<int,int>> > stuff;
    if (piece.first < 8){
        stuff.first = 7;
    }
    else {
        piece.first = piece.first - 80;
        stuff.first = 8.7;
    }
    vector<pair<int,int>> coords = {piece};
    stuff.second = coords;
    
    int row = piece.first;
    int col = piece.second;
    
    if (row > 0 && row < 7 && col > 0 && col < 7){
        if (board[row][col] == 9 || board[row][col] == 7){
            if (board[row+1][col+1] == 1 || board[row+1][col-1] == 1){
                return det_DJ(board, stuff);
            }
        }
        if (board[row][col] == 7){
            if (board[row-1][col+1] == 1 || board[row-1][col-1] == 1){
                return det_DJ(board, stuff);
            }
        }
    }
     
    if (row == 0 && col > 1 && col < 6 && board[row][col] == 9){
        if (board[row+1][col+1] == 1 || board[row+1][col-1] == 1){
            return det_DJ(board, stuff);
        }
    }
    
    // if the piece is in the middle of the board:
    if (row < 6 && col > 1 && col < 6) {
        // if there is an X or a K to the left and right
        if ( (board[row+1][col+1] == 9 || board[row+1][col+1] == 7) && (board[row+1][col-1] == 9 || board[row+1][col-1] == 7) ){
            return det_WGDJ(board, stuff);
        } // if there is an O or Q to the left and right AND the piece cannot be jumped
        if ( (board[row+1][col+1] != 9 || board[row+1][col+1] != 7) && (board[row+1][col-1] != 9 || board[row+1][col-1] != 7) && board[row+2][col+2] != 1 && board[row+2][col-2] != 1){
            return det_WGDJ(board, stuff);
        }
    }
    // if the piece is on the left edge:
    if (row < 6 && col == 0){
        // if there is an X or K to the right
        if (board[row+1][1] == 9 || board[row+1][1] == 7){
            return stuff;
        } // if there is an O or Q to the right and cannot be jumped
        if ((board[row+1][1] == 8 && board[row+2][2] != 1) || (board[row+1][1] == 6 && board[row+2][2] != 1)){
            return det_WGDJ(board, stuff);
        }
    }
    // if the piece is on the right edge:
    if (row < 6 && col == 7){
        // if there is an X or K to the left
        if (board[row+1][6] == 9 || board[row+1][6] == 7){
            return det_WGDJ(board, stuff);
        } // if there is an O or Q to the left and cannot be jumped
        if ((board[row+1][6] == 8 && board[row+2][5] != 1) || (board[row+1][6] == 6 && board[row+2][5] != 1)){
            return det_WGDJ(board, stuff);
        }
    }
    // if the piece is on inner left edge:
    if (row < 6 && col == 1){
        // if there is an X or K to the left or right
        if ((board[row+1][2] == 9 || board[row+1][2] == 7) && (board[row+1][0] == 9 || board[row+1][0] == 7)){
            return det_WGDJ(board, stuff);
        } // if there is an O or Q to the right and cannot be jumped AND the left is not free
        if ((board[row+1][2] == 8 || board[row+1][2] == 6) && board[row+2][3] != 1 && board[row+1][0] != 1){
            return det_WGDJ(board, stuff);
        }
    }
    // if the piece is on inner right edge:
    if (row < 6 && col == 6){
        // if there is an X or K to the left or right
        if ((board[row+1][7] == 9 || board[row+1][7] == 7) && (board[row+1][5] == 9 || board[row+1][5] == 7)){
            return det_WGDJ(board, stuff);
        } // if there is an O or Q to the left and cannot be jumped AND the right is not free
        if ((board[row+1][5] == 8 || board[row+1][5] == 6)  && board[row+2][4] != 1 && board[row+1][7] != 1){
            return det_WGDJ(board, stuff);
        }
    }
    // if the piece is in the second to last row:
    if (row == 6 && col < 7){
        // if the right or left is not free
        if (board[row+1][col+1] != 1 && board[row+1][col-1] != 1){
            return det_WGDJ(board, stuff);
        }
    }
    // if the piece is in the second to last row on the end:
    if (row == 6 && col == 7){
        // if the left isn't free
        if (board[7][6] != 1){
            return det_WGDJ(board, stuff);
        }
    }
    /////////////////////////////////////////////////////////////
    // if the piece is a K, need to check the opposite direction!
    if (board[row][col] == 7){
        // if the piece is in the middle of the board:
        if (row > 1 && col > 1 && col < 6) {
            // if there is an X or a K to the left and right
            if ( (board[row-1][col+1] == 9 || board[row-1][col+1] == 7) && (board[row-1][col-1] == 9 || board[row-1][col-1] == 7) ){
                return det_WGDJ(board, stuff);
            } // if there is an O or Q to the left and right AND the piece cannot be jumped
            if ( (board[row-1][col+1] != 9 || board[row-1][col+1] != 7) && (board[row-1][col-1] != 9 || board[row-1][col-1] != 7) && board[row-2][col+2] != 1 && board[row-2][col-2] != 1 && board[row-1][col+1] != 1 && board[row-1][col] != 1){
                return det_WGDJ(board, stuff);
            }
        }
        // if the piece is on the left edge:
        if (row > 2 && col == 0){
            // if there is an X or K to the right
            if (board[row-1][1] == 9 || board[row-1][1] == 7){
                return det_WGDJ(board, stuff);
            } // if there is an O or Q to the right and cannot be jumped
            if ((board[row-1][1] == 8 && board[row-2][2] != 1) || (board[row-1][1] == 6 && board[row-2][2] != 1)){
                return det_WGDJ(board, stuff);
            }
        }
        // if the piece is on the right edge:
        if (row > 2 && col == 7){
            // if there is an X or K to the left
            if (board[row-1][6] == 9 || board[row-1][6] == 7){
                return det_WGDJ(board, stuff);
            } // if there is an O or Q to the left and cannot be jumped
            if ((board[row-1][6] == 8 && board[row-2][5] != 1) || (board[row-1][6] == 6 && board[row-2][5] != 1)){
                return det_WGDJ(board, stuff);
            }
        }
        // if the piece is on inner left edge:
        if (row > 2 && col == 1){
            // if there is an X or K to the left or right
            if ((board[row-1][2] == 9 || board[row-1][2] == 7) && (board[row-1][0] == 9 || board[row+1][0] == 7)){
                return det_WGDJ(board, stuff);
            } // if there is an O or Q to the right and cannot be jumped AND the left is not free
            if ((board[row-1][2] == 8 || board[row-1][2] == 6) && board[row-2][3] != 1 && board[row-1][0] != 1){
                return det_WGDJ(board, stuff);
            }
        }
        // if the piece is on inner right edge:
        if (row > 2 && col == 6){
            // if there is an X or K to the left or right
            if ((board[row-1][7] == 9 || board[row-1][7] == 7) && (board[row-1][5] == 9 || board[row-1][5] == 7)){
                return det_WGDJ(board, stuff);
            } // if there is an O or Q to the left and cannot be jumped AND the right is not free
            if ((board[row-1][5] == 8 || board[row-1][5] == 6)  && board[row-2][4] != 1 && board[row-1][7] != 1){
                return det_WGDJ(board, stuff);
            }
        }
        // if the piece is in the third row:
        if (row == 2 && col < 7){
            // if the right or left is not free
            if (board[row-1][col+1] != 1 && board[row-1][col-1] != 1){
                return det_WGDJ(board, stuff);
            }
        }
        // if the piece is in the second row on the end:
        if (row == 1 && col == 0){
            // if the left isn't free
            if (board[0][1] != 1){
                return det_WGDJ(board, stuff);
            }
        }
    } // if the piece can move:
    return det_DJ(board, stuff);
}

pair<double, vector<pair<int,int>> > find_best_move(vector<vector<int>> board, pair<double, vector<pair<int,int>>>& stuff){
    double diff = 0;
    if (stuff.first >= 8){
        return stuff;
    }
    else if (stuff.first == 0){
        stuff.first = 2;
        stuff.second[0] = stuff.second[3];
        //stuff.second.pop_back();
        pair<double, vector<pair<int,int>> > stuff1 = stuff;
        stuff1.first = 8;
        stuff1 = det_DJ(board, stuff1);
        diff = stuff1.first - 8;
        stuff.first += diff;
        return stuff;
    }
    else if (stuff.first == 2){
        int row = stuff.second[0].first;
        int col = stuff.second[0].second;
        
        pair<double, vector<pair<int,int>> > stuff1 = stuff;
        stuff1.first = 8;
        if (row < 7 && col < 7 && col > 0){
            if (board[row+1][col+1] == 1 && board[row+1][col-1] == 1){
                pair<int,int> move1 = make_pair(row+1, col+1);
                stuff1.second.pop_back();
                vector<vector<int>> board1 = board;
                board[row+1][col+1] = board[row][col];
                board[row][col] = 1;
                move1.first += 80;
                stuff1.second.push_back(move1);
                stuff1 = det_NM(board, move1);
                pair<double, vector<pair<int,int>> > stuff2 = stuff;
                stuff2.first = 8;
                pair<int,int> move2 = make_pair(row+1, col-1);
                stuff2.second.pop_back();
                board1[row+1][col-1] = board1[row][col];
                board1[row][col] = 1;
                move2.first += 80;
                stuff2.second.push_back(move2);
                stuff2 = det_NM(board, move1);
                if (stuff1.first < stuff2.first){
                    stuff.second.insert(++stuff.second.begin(), move1);
                    diff = stuff1.first - 8;
                    stuff.first += diff;
                    return stuff;
                }
                else{
                    stuff.second.insert(++stuff.second.begin(), move2);
                    diff = stuff2.first - 8;
                    stuff.first += diff;
                    return stuff;
                }
            }
            else if (board[row+1][col+1] == 1){
                pair<int,int> move = make_pair(row+1, col+1);
                stuff.second.insert(++stuff.second.begin(), move);
                
                move.first += 80;
                stuff1.second.pop_back();
                stuff1.second.push_back(move);
                board[row+1][col+1] = board[row][col];
                board[row][col] = 1;
                
                stuff1 = det_NM(board, move);
                diff = stuff1.first - 8;
                stuff.first += diff;
                return stuff;
            }
            else {
                pair<int,int> move = make_pair(row+1, col-1);
                stuff.second.insert(++stuff.second.begin(), move);
                
                move.first += 80;
                stuff1.second.pop_back();
                stuff1.second.push_back(move);
                board[row+1][col-1] = board[row][col];
                board[row][col] = 1;
                stuff1 = det_NM(board, move);
                
                diff = stuff1.first - 8;
                stuff.first += diff;
                return stuff;
            }
        }
        if (row != 7 && col == 0 && board[row+1][col+1] == 1){
            pair<int,int> move = make_pair(row+1, col+1);
            stuff.second.insert(++stuff.second.begin(), move);
            
            move.first += 80;
            stuff1.second.pop_back();
            stuff1.second.push_back(move);
            board[row+1][col+1] = board[row][col];
            board[row][col] = 1;
            stuff1 = det_NM(board, move);
            
            diff = stuff1.first - 8;
            stuff.first += diff;
            return stuff;
        }
        if (col == 7 && board[row+1][col-1] == 1){
            pair<int,int> move = make_pair(row+1, col-1);
            stuff.second.insert(++stuff.second.begin(), move);
            
            move.first += 80;
            stuff1.second.pop_back();
            stuff1.second.push_back(move);
            board[row+1][col-1] = board[row][col];
            board[row][col] = 1;
            stuff1 = det_NM(board, move);
            
            diff = stuff1.first - 8;
            stuff.first += diff;
            return stuff;
        }
        if (board[row][col] == 7){
            if (row > 0 && col < 7 && col > 0){
                if (board[row-1][col+1] == 1 && board[row-1][col-1] == 1){
                    pair<int,int> move1 = make_pair(row-1, col+1);
                    move1.first += 80;
                    stuff1.second.pop_back();
                    stuff1.second.push_back(move1);
                    vector<vector<int>> board1 = board;
                    board[row-1][col+1] = board[row][col];
                    board[row][col] = 1;
                    stuff1 = det_NM(board, move1);
                    pair<double, vector<pair<int,int>> > stuff2 = stuff;
                    pair<int,int> move2 = make_pair(row-1, col-1);
                    move2.first += 80;
                    stuff2.second.pop_back();
                    stuff2.second.push_back(move2);
                    board1[row-1][col-1] = board1[row][col];
                    board1[row][col] = 1;
                    stuff2 = det_NM(board, move1);
                    if (stuff1.first < stuff2.first){
                        stuff.second.insert(++stuff.second.begin(), move1);
                        return stuff;
                    }
                    else{
                        stuff.second.insert(++stuff.second.begin(), move2);
                        return stuff;
                    }
                }
                else if (board[row-1][col+1] == 1){
                    pair<int,int> move = make_pair(row-1, col+1);
                    stuff.second.insert(++stuff.second.begin(), move);
                    
                    move.first += 80;
                    stuff1.second.pop_back();
                    stuff1.second.push_back(move);
                    board[row-1][col+1] = board[row][col];
                    board[row][col] = 1;
                    stuff1 = det_NM(board, move);
                    
                    diff = stuff1.first - 8;
                    stuff.first += diff;
                    return stuff;
                }
                else {
                    pair<int,int> move = make_pair(row-1, col-1);
                    stuff.second.insert(++stuff.second.begin(), move);
                    
                    move.first += 80;
                    stuff1.second.pop_back();
                    stuff1.second.push_back(move);
                    board[row-1][col-1] = board[row][col];
                    board[row][col] = 1;
                    stuff1 = det_NM(board, move);
                    
                    diff = stuff1.first - 8;
                    stuff.first += diff;
                    return stuff;
                }
            }
            if (col == 0 && board[row-1][col+1] == 1){
                pair<int,int> move = make_pair(row-1, col+1);
                stuff.second.insert(++stuff.second.begin(), move);
                
                move.first += 80;
                stuff1.second.pop_back();
                stuff1.second.push_back(move);
                board[row-1][col+1] = board[row][col];
                board[row][col] = 1;
                stuff1 = det_NM(board, move);
                
                diff = stuff1.first - 8;
                stuff.first += diff;
                return stuff;
            }
            if (row != 0 && col == 7 && board[row-1][col-1] == 1){
                pair<int,int> move = make_pair(row-1, col-1);
                stuff.second.insert(++stuff.second.begin(), move);
                
                move.first += 80;
                stuff1.second.pop_back();
                stuff1.second.push_back(move);
                board[row-1][col-1] = board[row][col];
                board[row][col] = 1;
                stuff1 = det_NM(board, move);
                
                diff = stuff1.first - 8;
                stuff.first += diff;
                return stuff;
            }
        }
    }
    else{
        int row = stuff.second[0].first;
        int col = stuff.second[0].second;
        
        pair<double, vector<pair<int,int>> > stuff1 = stuff;
        stuff1.first = 8;
        if (row < 7 && col < 7 && col > 0){
            if (board[row+1][col+1] == 1 && board[row+1][col-1] == 1){
                pair<int,int> move1 = make_pair(row+1, col+1);
                stuff1.second.pop_back();
                stuff1.second.push_back(move1);
                stuff1 = det_NM(board, move1);
                vector<vector<int>> board1 = board;
                board[row+1][col+1] = board[row][col];
                board[row][col] = 1;
                pair<double, vector<pair<int,int>> > stuff2 = stuff;
                stuff2.first = 8;
                pair<int,int> move2 = make_pair(row+1, col-1);
                stuff2.second.pop_back();
                stuff2.second.push_back(move2);
                board1[row+1][col-1] = board1[row][col];
                board1[row][col] = 1;
                stuff2 = det_NM(board, move1);
                if (stuff1.first < stuff2.first){
                    stuff.second.push_back(move1);
                    return stuff;
                }
                else{
                    stuff.second.push_back(move2);
                    return stuff;
                }
            }
            else if (board[row+1][col+1] == 1){
                pair<int,int> move = make_pair(row+1, col+1);
                stuff.second.push_back(move);
                return stuff;
            }
            else {
                pair<int,int> move = make_pair(row+1, col-1);
                stuff.second.push_back(move);
                return stuff;
            }
        }
        if (row != 7 && col == 0 && board[row+1][col+1] == 1){
            pair<int,int> move = make_pair(row+1, col+1);
            stuff.second.push_back(move);
            return stuff;
        }
        if (col == 7 && board[row+1][col-1] == 1){
            pair<int,int> move = make_pair(row+1, col-1);
            stuff.second.push_back(move);
            return stuff;
        }
        if (board[row][col] == 7){
            if (row > 0 && col < 7 && col > 0){
                if (board[row-1][col+1] == 1 && board[row-1][col-1] == 1){
                    pair<int,int> move1 = make_pair(row-1, col+1);
                    stuff1.second.pop_back();
                    stuff1.second.push_back(move1);
                    vector<vector<int>> board1 = board;
                    board[row-1][col+1] = board[row][col];
                    board[row][col] = 1;
                    stuff1 = det_NM(board, move1);
                    pair<double, vector<pair<int,int>> > stuff2 = stuff;
                    pair<int,int> move2 = make_pair(row-1, col-1);
                    stuff2.second.pop_back();
                    stuff2.second.push_back(move2);
                    board1[row-1][col-1] = board1[row][col];
                    board1[row][col] = 1;
                    stuff2 = det_NM(board, move1);
                    if (stuff1.first < stuff2.first){
                        stuff.second.push_back(stuff1.second[0]);
                        return stuff;
                    }
                    else{
                        stuff.second.push_back(stuff2.second[0]);
                        return stuff;
                    }
                }
                else if (board[row-1][col+1] == 1){
                    pair<int,int> move = make_pair(row-1, col+1);
                    stuff.second.push_back(move);
                    return stuff;
                }
                else {
                    pair<int,int> move = make_pair(row-1, col-1);
                    stuff.second.push_back(move);
                    return stuff;
                }
            }
            if (col == 0 && board[row-1][col+1] == 1){
                pair<int,int> move = make_pair(row-1, col+1);
                stuff.second.push_back(move);
                return stuff;
            }
            if (row != 0 && col == 7 && board[row-1][col-1] == 1){
                pair<int,int> move = make_pair(row-1, col-1);
                stuff.second.push_back(move);
                return stuff;
            }
        }
    }
    
    
    
    return stuff;
}

void pick_best_WGDJmove(vector<vector<int>> board, multimap<double, vector<pair<int,int>> > moves){
    multimap<double, vector<pair<int,int>> > tempM;
    for (auto itr = moves.begin(); itr != moves.end(); ++itr){
        if (itr->first == 2) {
            auto it = itr;
            ++it;
            for (; it != moves.end(); ++it){
                if (it->first < 7 && it->first > 2 && it->second[1] == itr->second[1]){
                    tempM.insert(*it);
                }
                if (it->first < 7 && it->first > 2 && it->second[1] == itr->second[2]){
                    tempM.insert(*it);
                }
            }
        }
    }
    
}

ostream& operator<<(ostream& out, const pair<int,int>& coord){
    out << '(' << coord.first << ',' << coord.second << ')';
    return out;
}

ostream& operator<<(ostream& out, const vector<pair<int,int>>& pieces){
    for (size_t i = 0; i < pieces.size(); ++i){
        out << pieces[i] << " ";
    }
    return out;
}

void displayIntro(){
    cout << "          Welcome to Checkers!\n\nThis is a game against the computer.\nBefore you play, remember these 3 basic rules:\n\n";
    cout << "1) O and X pieces can only move in their\n   respective 'forward' diagonal directions.\n\n";
    cout << "2) Once a piece has made it to the other side,\n   it will become a royal (O -> Q and X -> K).\n   The piece can now move in the 'forward' and\n   'backward' diagonal directions.\n\n";
    cout << "3) To kill your opponent, single or double jump\n   their piece.\n\n";
}
