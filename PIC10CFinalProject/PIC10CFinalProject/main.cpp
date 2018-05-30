#include <iostream>
#include <cmath>
#include "CheckersGame.h"

using namespace std;

int main() {
    CheckBoard board;
    Player playerO(8, 6, board);
    Player playerX(9, 7, board);
    bool keepGoing = true;
    board.display();
    size_t count = 0;
    while (keepGoing){
        int Crow, Ccol, Nrow, Ncol = 0;
        if (count%2 == 1){
            do {
                cout << "Where do you want to move Player O?\nCurrent Row and Current Column: ";
                cin >> Crow >> Ccol;
                cout << "New Row and New Col: ";
                cin >> Nrow >> Ncol;
                
                if (abs(Nrow-Crow) == 4){
                    int Mrow, Mcol = 0;
                    cout << "Please enter the intermediate move of your double jump.\nMiddle Row and Middle Column: ";
                    cin >> Mrow >> Mcol;
                    if (board.validMove(Crow, Ccol, Mrow, Mcol, playerO, playerX) && board.validMove(Mrow, Mcol, Nrow, Ncol, playerO, playerX)){
                        break;
                    }
                }
            }
            while (!board.validMove(Crow, Ccol, Nrow, Ncol, playerO, playerX));
        
            board.display();
            char quit = ' ';
            cout << "To quit, enter 'Q' or press any key to continue. ";
            cin >> quit;
            if (quit == 'Q'){
                keepGoing = false;
            }
            ++count;
        }
        else {
            do {
                cout << "Where do you want to move Player X?\nCurrent Row and Current Column: ";
                cin >> Crow >> Ccol;
                cout << "New Row and New Col: ";
                cin >> Nrow >> Ncol;
                
                if (abs(Nrow-Crow) == 4){
                    int Mrow, Mcol = 0;
                    cout << "Please enter the intermediate move of your double jump.\nMiddle Row and Middle Column: ";
                    cin >> Mrow >> Mcol;
                    if (board.validMove(Crow, Ccol, Mrow, Mcol, playerX, playerO) && board.validMove(Mrow, Mcol, Nrow, Ncol, playerX, playerO)){
                       break;
                    }
                }
            }
            while (!board.validMove(Crow, Ccol, Nrow, Ncol, playerX, playerO));
            
            board.display();
            char quit = ' ';
            cout << "To quit, enter 'Q' or press any key to continue. ";
            cin >> quit;
            if (quit == 'Q'){
                keepGoing = false;
            }
            ++count;
        }
    }
    
    return 0;
}
