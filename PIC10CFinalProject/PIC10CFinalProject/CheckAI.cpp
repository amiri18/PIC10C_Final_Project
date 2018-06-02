#include "CheckersGame.h"
#include <iostream>
#include <cmath>
using namespace std;

// return 6 if the piece cannot move, or else call det_safe_move
int det_no_move(const vector<vector<int>>& board, const pair<int,int>& piece){
    int row = piece.first;
    int col = piece.second;
        
    // if the piece is in the middle of the board:
    if (row < 6 && col > 1 && col < 6) {
        // if there is an X or a K to the left and right
        if ( (board[row+1][col+1] == 9 || board[row+1][col+1] == 7) && (board[row+1][col-1] == 9 || board[row+1][col-1] == 7) ){
            return 6;
        } // if there is an O or Q to the left and right AND the piece cannot be jumped
        if ( (board[row+1][col+1] != 9 || board[row+1][col+1] != 7) && (board[row+1][col-1] != 9 || board[row+1][col-1] != 7) && board[row+2][col+2] != 1 && board[row+2][col-2] != 1){
            return 6;
        }
    }
    // if the piece is on the left edge:
    if (row < 6 && col == 0){
        // if there is an X or K to the right
        if (board[row+1][1] == 9 || board[row+1][1] == 7){
            return 6;
        } // if there is an O or Q to the right and cannot be jumped
        if ((board[row+1][1] == 8 && board[row+2][2] != 1) || (board[row+1][1] == 6 && board[row+2][2] != 1)){
            return 6;
        }
    }
    // if the piece is on the right edge:
    if (row < 6 && col == 7){
        // if there is an X or K to the left
        if (board[row+1][6] == 9 || board[row+1][6] == 7){
            return 6;
        } // if there is an O or Q to the left and cannot be jumped
        if ((board[row+1][6] == 8 && board[row+2][5] != 1) || (board[row+1][6] == 6 && board[row+2][5] != 1)){
            return 6;
        }
    }
    // if the piece is on inner left edge:
    if (row < 6 && col == 1){
        // if there is an X or K to the left or right
        if ((board[row+1][2] == 9 || board[row+1][2] == 7) && (board[row+1][0] == 9 || board[row+1][0] == 7)){
            return 6;
        } // if there is an O or Q to the right and cannot be jumped AND the left is not free
        if ((board[row+1][2] == 8 || board[row+1][2] == 6) && board[row+2][3] != 1 && board[row+1][0] != 1){
            return 6;
        }
    }
    // if the piece is on inner right edge:
    if (row < 6 && col == 6){
        // if there is an X or K to the left or right
        if ((board[row+1][7] == 9 || board[row+1][7] == 7) && (board[row+1][5] == 9 || board[row+1][5] == 7)){
            return 6;
        } // if there is an O or Q to the left and cannot be jumped AND the right is not free
        if ((board[row+1][5] == 8 || board[row+1][5] == 6)  && board[row+2][4] != 1 && board[row+1][7] != 1){
            return 6;
            }
    }
    // if the piece is in the second to last row:
    if (row == 6 && col < 7){
        // if the right or left is not free
        if (board[row+1][col+1] != 1 && board[row+1][col-1] != 1){
            return 0;
        }
    }
    // if the piece is in the second to last row on the end:
    if (row == 6 && col == 7){
        // if the left isn't free
        if (board[7][6] != 1){
            return 6;
        }
    }
    /////////////////////////////////////////////////////////////
    // if the piece is a K, need to check the opposite direction!
    if (board[row][col] == 7){
        // if the piece is in the middle of the board:
        if (row > 6 && col > 1 && col < 6) {
            // if there is an X or a K to the left and right
            if ( (board[row-1][col+1] == 9 || board[row-1][col+1] == 7) && (board[row-1][col-1] == 9 || board[row-1][col-1] == 7) ){
                return 6;
            } // if there is an O or Q to the left and right AND the piece cannot be jumped
            if ( (board[row-1][col+1] != 9 || board[row-1][col+1] != 7) && (board[row-1][col-1] != 9 || board[row-1][col-1] != 7) && board[row-2][col+2] != 1 && board[row-2][col-2] != 1){
                return 6;
            }
        }
        // if the piece is on the left edge:
        if (row > 2 && col == 0){
            // if there is an X or K to the right
            if (board[row-1][1] == 9 || board[row-1][1] == 7){
                return 6;
            } // if there is an O or Q to the right and cannot be jumped
            if ((board[row-1][1] == 8 && board[row-2][2] != 1) || (board[row-1][1] == 6 && board[row-2][2] != 1)){
                return 6;
            }
        }
        // if the piece is on the right edge:
        if (row > 2 && col == 7){
            // if there is an X or K to the left
            if (board[row-1][6] == 9 || board[row-1][6] == 7){
                return 6;
            } // if there is an O or Q to the left and cannot be jumped
            if ((board[row-1][6] == 8 && board[row-2][5] != 1) || (board[row-1][6] == 6 && board[row-2][5] != 1)){
                return 6;
            }
        }
        // if the piece is on inner left edge:
        if (row > 2 && col == 1){
            // if there is an X or K to the left or right
            if ((board[row-1][2] == 9 || board[row-1][2] == 7) && (board[row-1][0] == 9 || board[row+1][0] == 7)){
                return 6;
            } // if there is an O or Q to the right and cannot be jumped AND the left is not free
            if ((board[row-1][2] == 8 || board[row-1][2] == 6) && board[row-2][3] != 1 && board[row-1][0] != 1){
                return 6;
            }
        }
        // if the piece is on inner right edge:
        if (row > 2 && col == 6){
            // if there is an X or K to the left or right
            if ((board[row-1][7] == 9 || board[row-1][7] == 7) && (board[row-1][5] == 9 || board[row-1][5] == 7)){
                return 6;
            } // if there is an O or Q to the left and cannot be jumped AND the right is not free
            if ((board[row-1][5] == 8 || board[row-1][5] == 6)  && board[row-2][4] != 1 && board[row-1][7] != 1){
                return 6;
            }
        }
        // if the piece is in the third row:
        if (row == 2 && col < 7){
            // if the right or left is not free
            if (board[row-1][col+1] != 1 && board[row-1][col-1] != 1){
                return 0;
            }
        }
        // if the piece is in the second row on the end:
        if (row == 1 && col == 0){
            // if the left isn't free
            if (board[0][1] != 1){
                return 6;
            }
        }
    } // if the piece can move:
    return det_DJ(board, piece);
}

int det_safe_move(const vector<vector<int>>& board, const pair<int,int>& piece){
    return 5;
}

int det_willGetDJ(const vector<vector<int>>& board, const pair<int,int>& piece){
    int row = piece.first;
    int col = piece.second;
    // if the piece is at the bottom left quarter of the board:
    if (row > 2 && row < 7 && col > 0 && col < 5){
        // if the piece can get up right 2jumped
        if((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col+2] == 9 || board[row-2][col+2] == 7) && board[row-3][col+3] == 1){
            return 2;
        }
        // if the piece can get straight up right 2jumped
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col-1] == 1){
            return 2;
        }
        // if the piece can get straight up left 2jumped
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col+1] == 1){
            return 2;
        }
    }
    // if the piece is at the bottom right quarter of the board:
    if (row > 2 && row < 7 && col < 7 && col > 2){
        // if the piece can get up left 2jumped
        if((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col-2] == 9 || board[row-2][col-2] == 7) && board[row-3][col-3] == 1){
            return 2;
        }
        // if the piece can get straight up left 2jumped
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row-1][col-1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col+1] == 1){
            return 2;
        }
        // if the piece can get straight up right 2jumped
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row-1][col+1] == 1 && (board[row-2][col] == 9 || board[row-2][col] == 7) && board[row-3][col-1] == 1){
            return 2;
        }
    }
    /////////////////////////////////////////////////////////////
    // if there is a Q behind the piece, need to check the opposite direction!
        
    // if the piece is at the top left quarter of the board:
    if (row > 0 && row < 5 && col > 0 && col < 5){
        // if the piece can get down right 2jumped
        if(board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col+2] == 9 || board[row+2][col+2] == 7) && board[row+3][col+3] == 1){
            return 2;
        }
        // if the piece can get straight down right 2jumped
        if (board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col-1] == 1){
            return 2;
        }
        // if the piece can get straight down left 2jumped
        if (board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col+1] == 1){
            return 2;
        }
    }
    // if the piece is at the bottom right quarter of the board:
    if (row > 0 && row < 5 && col < 7 && col > 2){
        // if the piece can get down left 2jumped
        if(board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col-2] == 9 || board[row+2][col-2] == 7) && board[row+3][col-3] == 1){
            return 2;
        }
        // if the piece can get straight down left 2jumped
        if (board[row-1][col+1] == 6 && board[row+1][col-1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col+1] == 1){
            return 2;
        }
        // if the piece can get straight down right 2jumped
        if (board[row-1][col-1] == 6 && board[row+1][col+1] == 1 && (board[row+2][col] == 9 || board[row+2][col] == 7) && board[row+3][col-1] == 1){
            return 2;
        }
    }
    return det_safe_move(board, piece);
}

int det_DJ(const vector<vector<int>>& board, const pair<int,int>& piece){
    int row = piece.first;
    int col = piece.second;
    // if the piece is in the top left quarter of the board:
    if (row < 4 && col < 4){
        // check down right 2jump
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row+2][col+2] == 1 && (board[row+3][col+3] == 8 || board[row+3][col+3] == 6) && board[row+4][col+4] == 1){
            return 1;
        } // check straight down right 2jump
        if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row+2][col+2] == 1 && (board[row+3][col+1] == 8 || board[row+3][col+1] == 6) && board[row+4][col] == 1){
            return 1;
        } // if the piece is in the third or fourth column
        if (col == 3 || col == 2){
            // check straight down left 2jump
            if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row+2][col-2] == 1 && (board[row+3][col-1] == 8 || board[row+3][col-1] == 6) && board[row+4][col] == 1){
                return 1;
            }
        }
    }
    // if the piece is in the top right quarter of the board:
    if (row < 4 && col > 3){
        // check down left 2jump
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row+2][col-2] == 1 && (board[row+3][col-3] == 8 || board[row+3][col-3] == 6) && board[row+4][col-4] == 1){
            return 1;
        } // check straight down left 2jump
        if ((board[row+1][col-1] == 8 || board[row+1][col-1] == 6) && board[row+2][col-2] == 1 && (board[row+3][col-1] == 8 || board[row+3][col-1] == 6) && board[row+4][col] == 1){
            return 1;
        } // if the piece is in the fifth or sixth column
        if (col == 4 || col == 5){
            // check straight down right 2jump
            if ((board[row+1][col+1] == 8 || board[row+1][col+1] == 6) && board[row+2][col+2] == 1 && (board[row+3][col+1] == 8 || board[row+3][col+1] == 6) && board[row+4][col] == 1){
                return 1;
            }
        }
    }
    /////////////////////////////////////////////////////////////
    // if the piece is a K, need to check the opposite direction!
    if (board[row][col] == 7) {
        // if the piece is in the bottom left quarter of the board:
        if (row > 3 && col < 4){
            // check up right 2jump
            if ((board[row-1][col+1] == 8 || board[row-1][col+1] == 6) && board[row-2][col+2] == 1 && (board[row-3][col+3] == 8 || board[row-3][col+3] == 6) && board[row-4][col+4] == 1){
                return 1;
            } // check straight up right 2jump
            if ((board[row-1][col+1] == 8 || board[row-1][col+1] == 6) && board[row-2][col+2] == 1 && (board[row-3][col+1] == 8 || board[row-3][col+1] == 6) && board[row-4][col] == 1){
                return 1;
            } // if the piece is in the third or fourth column
            if (col == 3 || col == 2){
                // check straight up left 2jump
                if ((board[row-1][col-1] == 8 || board[row-1][col-1] == 6) && board[row-2][col-2] == 1 && (board[row-3][col-1] == 8 || board[row-3][col-1] == 6) && board[row-4][col] == 1){
                    return 1;
                }
            }
        }
        // if the piece is in the bottom right quarter of the board:
        if (row > 3 && col > 3){
            // check up left 2jump
            if ((board[row-1][col-1] == 8 || board[row-1][col-1] == 6) && board[row-2][col-2] == 1 && (board[row-3][col-3] == 8 || board[row-3][col-3] == 6) && board[row-4][col-4] == 1){
                return 1;
            } // check straight up left 2jump
            if ((board[row-1][col-1] == 8 || board[row-1][col-1] == 6) && board[row-2][col-2] == 1 && (board[row-3][col-1] == 8 || board[row-3][col-1] == 6) && board[row-4][col] == 1){
                return 1;
            } // if the piece is in the fifth or sixth column
            if (col == 4 || col == 5){
                // check straight up right 2jump
                if ((board[row-1][col+1] == 8 || board[row-1][col+1] == 6) && board[row-2][col+2] == 1 && (board[row-3][col+1] == 8 || board[row-3][col+1] == 6) && board[row-4][col] == 1){
                    return 1;
                }
            }
        }
    }
    return det_willGetDJ(board, piece);
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
