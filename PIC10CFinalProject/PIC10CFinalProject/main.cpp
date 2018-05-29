#include <iostream>
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
        if (count%2 == 1){
            int Crow = 0;
            int Ccol = 0;
            int Nrow = 0;
            int Ncol = 0;
            cout << "Where do you want to move Player O?\nCurrent Row and Current Column: ";
            cin >> Crow >> Ccol;
            cout << "New Row and New Col: ";
            cin >> Nrow >> Ncol;
            board.move(Crow, Ccol, Nrow, Ncol, playerO);
            board.didKill(Crow, Ccol, Nrow, Ncol, playerX);
            board.display();
            char quit = 'N';
            cout << "To quit, enter 'Q' or press any key to continue ";
            cin >> quit;
            if (quit == 'Q'){
                keepGoing = false;
            }
            ++count;
        }
        else {
            int Crow = 0;
            int Ccol = 0;
            int Nrow = 0;
            int Ncol = 0;
            cout << "Where do you want to move Player X?\nCurrent Row and Current Column: ";
            cin >> Crow >> Ccol;
            cout << "New Row and New Col: ";
            cin >> Nrow >> Ncol;
            board.move(Crow, Ccol, Nrow, Ncol, playerX);
            board.didKill(Crow, Ccol, Nrow, Ncol, playerO);
            board.display();
            char quit = 'N';
            cout << "To quit, enter 'Q' or press any key to continue ";
            cin >> quit;
            if (quit == 'Q'){
                keepGoing = false;
            }
            ++count;
        }
        
    }
    

    return 0;
}

