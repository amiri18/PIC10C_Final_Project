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
pair<int, vector<pair<int,int>> > det_DJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>> >& stuff){
    // if recursion has NOT happened...
    if (stuff.first != 8){
        // set the key value to 1!
        stuff.first = 1;
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
pair<int, vector<pair<int,int>> > det_WGDJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff){
    // if recursion has NOT happened...
    if (stuff.first == 1){
        // set the key value to 2
        stuff.first = 2;
    }
    
    // get the current location
    int row = stuff.second[0].first;
    int col = stuff.second[0].second;
    
    // if the piece is at the bottom left quarter of the board:
    if (row > 2 && row < 7 && col > 0 && col < 5){
        // if the piece can get up right 2jumped
        if((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col+2] == 9 || board[row-2][col+2] == 7) && board[row-3][col+3] == 1){
            return find_best_move(board, stuff);
        }
        // if the piece can get straight up right 2jumped
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col-1] == 1){
            return find_best_move(board, stuff);
        }
        // if the piece can get straight up left 2jumped
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col+1] == 1){
            return find_best_move(board, stuff);
        }
    }
    // if the piece is at the bottom right quarter of the board:
    if (row > 2 && row < 7 && col < 7 && col > 2){
        // if the piece can get up left 2jumped
        if((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col-2] == 9 || board[row-2][col-2] == 7) && board[row-3][col-3] == 1){
            return find_best_move(board, stuff);
        }
        // if the piece can get straight up left 2jumped
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col+1] == 1){
            return find_best_move(board, stuff);
        }
        // if the piece can get straight up right 2jumped
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col-1] == 1){
            return find_best_move(board, stuff);
        }
    }
    /////////////////////////////////////////////////////////////
    // if there is a Q behind the piece, need to check the opposite direction!
        
    // if the piece is at the top left quarter of the board:
    if (row > 0 && row < 5 && col > 0 && col < 5){
        // if the piece can get down right 2jumped
        if(board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col+2] == 9 || board[row+2][col+2] == 7) && board[row+3][col+3] == 1){
            return find_best_move(board, stuff);
        }
        // if the piece can get straight down right 2jumped
        if (board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col-1] == 1){
            return find_best_move(board, stuff);
        }
        // if the piece can get straight down left 2jumped
        if (board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col+1] == 1){
            return find_best_move(board, stuff);
        }
    }
    // if the piece is at the bottom right quarter of the board:
    if (row > 0 && row < 5 && col < 7 && col > 2){
        // if the piece can get down left 2jumped
        if(board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col-2] == 9 || board[row+2][col-2] == 7) && board[row+3][col-3] == 1){
            return find_best_move(board, stuff);
        }
        // if the piece can get straight down left 2jumped
        if (board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col+1] == 1){
            return find_best_move(board, stuff);
        }
        // if the piece can get straight down right 2jumped
        if (board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col-1] == 1){
            return find_best_move(board, stuff);
        }
    }
    if (stuff.first == 7){
        return det_WGJ(board, stuff);
    }
    else {
        return det_J(board, stuff);
    }
}

pair<int, vector<pair<int,int>> > det_J(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff){
    if (stuff.first == 2){
        stuff.first = 3;
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
                end = make_pair(row-2, col+2);
                stuff.second.push_back(end);
                return stuff;
            }
        }
    }
    return det_WGJ(board, stuff);
}

pair<int, vector<pair<int,int>> > det_WGJ(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff){
    if (stuff.first == 3){
        stuff.first = 4;
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

pair<int, vector<pair<int,int>> > det_SM(const vector<vector<int>>& board, pair<int, vector<pair<int,int>>>& stuff){
    if (stuff.first == 4){
        stuff.first = 5;
    }
    
    pair<int,int> end;
    
    int row = stuff.second[0].first;
    int col = stuff.second[0].second;
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
        if (row > 1 && col < 6 && board[row-1][col+1] == 1 && board[row-2][col+2] == 1) {
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
        if (row > 1 && col > 1 && board[row-1][col-1] == 1 && board[row-2][col-2] == 1) {
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
    
    // if there are no good moves, return 6 to suggest finding the best move
    if (stuff.first == 5){
        stuff.first = 6;
    }
    return find_best_move(board, stuff);
}

// return 7 if the piece cannot move, or else call det_safe_move
pair<int, vector<pair<int,int>> > det_NM(const vector<vector<int>>& board, const pair<int,int>& piece){
    
    pair<int, vector<pair<int,int>> > stuff;
    vector<pair<int,int>> coords = {piece};
    if (stuff.first != 8){
        stuff.first = 7;
    }
    
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
    
    // if the piece is in the middle of the board:
    if (row < 6 && col > 1 && col < 6) {
        // if there is an X or a K to the left and right
        if ( (board[row+1][col+1] == 9 || board[row+1][col+1] == 7) && (board[row+1][col-1] == 9 || board[row+1][col-1] == 7) ){
            return det_WGDJ(board, stuff);
        } // if there is an O or Q to the left and right AND the piece cannot be jumped
        if ( (board[row+1][col+1] != 9 || board[row+1][col+1] != 7) && (board[row+1][col-1] != 9 || board[row+1][col-1] != 7) && board[row+2][col+2] != 1 && board[row+2][col-2] != 1){
            return stuff;
        }
    }
    // if the piece is on the left edge:
    if (row < 6 && col == 0){
        // if there is an X or K to the right
        if (board[row+1][1] == 9 || board[row+1][1] == 7){
            return stuff;
        } // if there is an O or Q to the right and cannot be jumped
        if ((board[row+1][1] == 8 && board[row+2][2] != 1) || (board[row+1][1] == 6 && board[row+2][2] != 1)){
            return stuff;
        }
    }
    // if the piece is on the right edge:
    if (row < 6 && col == 7){
        // if there is an X or K to the left
        if (board[row+1][6] == 9 || board[row+1][6] == 7){
            return stuff;
        } // if there is an O or Q to the left and cannot be jumped
        if ((board[row+1][6] == 8 && board[row+2][5] != 1) || (board[row+1][6] == 6 && board[row+2][5] != 1)){
            return stuff;
        }
    }
    // if the piece is on inner left edge:
    if (row < 6 && col == 1){
        // if there is an X or K to the left or right
        if ((board[row+1][2] == 9 || board[row+1][2] == 7) && (board[row+1][0] == 9 || board[row+1][0] == 7)){
            return stuff;
        } // if there is an O or Q to the right and cannot be jumped AND the left is not free
        if ((board[row+1][2] == 8 || board[row+1][2] == 6) && board[row+2][3] != 1 && board[row+1][0] != 1){
            return stuff;
        }
    }
    // if the piece is on inner right edge:
    if (row < 6 && col == 6){
        // if there is an X or K to the left or right
        if ((board[row+1][7] == 9 || board[row+1][7] == 7) && (board[row+1][5] == 9 || board[row+1][5] == 7)){
            return stuff;
        } // if there is an O or Q to the left and cannot be jumped AND the right is not free
        if ((board[row+1][5] == 8 || board[row+1][5] == 6)  && board[row+2][4] != 1 && board[row+1][7] != 1){
            return stuff;
        }
    }
    // if the piece is in the second to last row:
    if (row == 6 && col < 7){
        // if the right or left is not free
        if (board[row+1][col+1] != 1 && board[row+1][col-1] != 1){
            return stuff;
        }
    }
    // if the piece is in the second to last row on the end:
    if (row == 6 && col == 7){
        // if the left isn't free
        if (board[7][6] != 1){
            return stuff;
        }
    }
    /////////////////////////////////////////////////////////////
    // if the piece is a K, need to check the opposite direction!
    if (board[row][col] == 7){
        // if the piece is in the middle of the board:
        if (row > 6 && col > 1 && col < 6) {
            // if there is an X or a K to the left and right
            if ( (board[row-1][col+1] == 9 || board[row-1][col+1] == 7) && (board[row-1][col-1] == 9 || board[row-1][col-1] == 7) ){
                return stuff;
            } // if there is an O or Q to the left and right AND the piece cannot be jumped
            if ( (board[row-1][col+1] != 9 || board[row-1][col+1] != 7) && (board[row-1][col-1] != 9 || board[row-1][col-1] != 7) && board[row-2][col+2] != 1 && board[row-2][col-2] != 1){
                return stuff;
            }
        }
        // if the piece is on the left edge:
        if (row > 2 && col == 0){
            // if there is an X or K to the right
            if (board[row-1][1] == 9 || board[row-1][1] == 7){
                return stuff;
            } // if there is an O or Q to the right and cannot be jumped
            if ((board[row-1][1] == 8 && board[row-2][2] != 1) || (board[row-1][1] == 6 && board[row-2][2] != 1)){
                return stuff;
            }
        }
        // if the piece is on the right edge:
        if (row > 2 && col == 7){
            // if there is an X or K to the left
            if (board[row-1][6] == 9 || board[row-1][6] == 7){
                return stuff;
            } // if there is an O or Q to the left and cannot be jumped
            if ((board[row-1][6] == 8 && board[row-2][5] != 1) || (board[row-1][6] == 6 && board[row-2][5] != 1)){
                return stuff;
            }
        }
        // if the piece is on inner left edge:
        if (row > 2 && col == 1){
            // if there is an X or K to the left or right
            if ((board[row-1][2] == 9 || board[row-1][2] == 7) && (board[row-1][0] == 9 || board[row+1][0] == 7)){
                return stuff;
            } // if there is an O or Q to the right and cannot be jumped AND the left is not free
            if ((board[row-1][2] == 8 || board[row-1][2] == 6) && board[row-2][3] != 1 && board[row-1][0] != 1){
                return stuff;
            }
        }
        // if the piece is on inner right edge:
        if (row > 2 && col == 6){
            // if there is an X or K to the left or right
            if ((board[row-1][7] == 9 || board[row-1][7] == 7) && (board[row-1][5] == 9 || board[row-1][5] == 7)){
                return stuff;
            } // if there is an O or Q to the left and cannot be jumped AND the right is not free
            if ((board[row-1][5] == 8 || board[row-1][5] == 6)  && board[row-2][4] != 1 && board[row-1][7] != 1){
                return stuff;
            }
        }
        // if the piece is in the third row:
        if (row == 2 && col < 7){
            // if the right or left is not free
            if (board[row-1][col+1] != 1 && board[row-1][col-1] != 1){
                return stuff;
            }
        }
        // if the piece is in the second row on the end:
        if (row == 1 && col == 0){
            // if the left isn't free
            if (board[0][1] != 1){
                return stuff;
            }
        }
    } // if the piece can move:
    return det_DJ(board, stuff);
}

pair<int, vector<pair<int,int>> > find_best_move(vector<vector<int>> board, pair<int, vector<pair<int,int>>>& stuff){
    
    if (stuff.first == 8){
        return stuff;
    }
    
    else{
        int row = stuff.second[0].first;
        int col = stuff.second[0].second;
        
        pair<int, vector<pair<int,int>> > stuff1 = stuff;
        stuff1.first = 8;
        if (row < 7 && col < 7 && col > 0){
            if (board[row+1][col+1] == 1 && board[row+1][col-1] == 1){
                pair<int,int> move1 = make_pair(row+1, col+1);
                stuff1.second.pop_back();
                stuff1.second.push_back(move1);
                stuff1 = det_NM(board, move1);
                pair<int, vector<pair<int,int>> > stuff2 = stuff;
                stuff2.first = 8;
                pair<int,int> move2 = make_pair(row+1, col-1);
                stuff2.second.pop_back();
                stuff2.second.push_back(move2);
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
                    stuff1 = det_NM(board, move1);
                    pair<int, vector<pair<int,int>> > stuff2 = stuff;
                    pair<int,int> move2 = make_pair(row-1, col-1);
                    stuff2.second.pop_back();
                    stuff2.second.push_back(move2);
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
