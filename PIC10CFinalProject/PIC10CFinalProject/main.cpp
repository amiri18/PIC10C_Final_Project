#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include "CheckersGame.h"

using namespace std;

int main() {
    // seed the random function
    srand(static_cast<unsigned int>(time(NULL)));
    
    // create the checkerboard
    CheckBoard board;
    
    // create both players
    Player playerO(8, 6, board); // user
    Player playerX(9, 7, board); // AI (computer)
    
    // bool type for the game while loop
    // loop will be terminated when:
    // either the player "quits" the game or someone loses
    bool keepGoing = true;
    
    // display the board to the user
    displayIntro();
    board.display();
    // variable makes the loop alternate between players
    size_t count = 1;
    
    // keep playing the game while player wants to keep going AND no one has lost
    while (keepGoing && !board.pieceCountZero()){
        int Crow, Ccol, Nrow, Ncol = 0; // row/column variables
        
        if (count%2 == 1){ // user's turn during odd numbers
            do { // do while the user inters a valid move
                
                // ask the user to enter in move
                cout << "Where do you want to move Player O?\nCurrent Row and Current Column: ";
                cin >> Crow >> Ccol; // current location
                cout << "New Row and New Col: ";
                cin >> Nrow >> Ncol; // new location
                
                // if they want to double jump
                if (abs(Nrow-Crow) == 4){
                    int Mrow, Mcol = 0; // row/column variables
                    cout << "Please enter the intermediate move of your double jump.\nMiddle Row and Middle Column: ";
                    cin >> Mrow >> Mcol; // get the middle location
                    if (board.validMove(Crow, Ccol, Mrow, Mcol, playerO, playerX) && board.validMove(Mrow, Mcol, Nrow, Ncol, playerO, playerX)){
                        // if they gave valid moves, go on to Player X
                        break;
                    }
                }
            }
            while (!board.validMove(Crow, Ccol, Nrow, Ncol, playerO, playerX));
            
            // display the board with the moved piece
            board.display();
            
            // if the user wants to stop the game, enter 'Q'
            string quit = "";
            cout << "To quit, enter 'Q' or press any key to continue. ";
            getline(cin, quit);
            getline(cin, quit);
            if (quit == "Q"){
                keepGoing = false;
            } // if not keep going
            ++count;
        }
        
        else { // the AI's turn during even numbers
            cout << "It's playerX's move: \n";
            // determine all moves on the current game board
            playerX.det_moves(board.getBoard());
            playerX.getMoves(); // debugging feature for now
            // pick the best move
            playerX.pickMove(board, playerO);
            // display the board with the new move
            board.display();
            playerX.displayMove();
            
            // if the user wants to stop the game, enter 'Q'
            string quit = "";
            cout << "To quit, enter 'Q' or press any key to continue. ";
            getline(cin, quit);
            if (quit == "Q"){
                keepGoing = false;
            } // if not keep going
            ++count;
        }
    }
    
    return 0;
}
