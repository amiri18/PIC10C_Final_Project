# Final Project: Checkers Game!
## Game Details:
This is a one player checkers game against the computer that is **displayed on the console**. The game will display the instructions and ask the user to enter in their move, since it is their turn first. Afterward the computer will make its move. The game continues until either the user quits or someone wins. The computer is `Player X` and the user is `Player O`.

### Rules:
- X and O pieces can only move in their respective forward diagonal direction.
- If a piece of Player X makes it to the other side, their piece will get *kinged*, and the X becomes a K. Similarily, if a piece of the user's makes it the other side, their piece will get *queened*, and the O becomes an Q. "Royal" pieces, unlike regular ones, can move fowards AND backwards.
- For a player to "kill" their opponent, they can either single or double jump their piece. *The user's goal is to kill all of the computer's piece's.*
 
## Programming Details:
For my final project I wanted to code another algorithm that worked similar to very basic artificial intelligence. I really enjoyed coding the "dealer" for the card game in the first homework, so I decided to create a checkers game where the user plays against the computer. As of right now the "computer" is not that smart and can be beaten, since it is hard to code for every situation as well as strategies. There also still might be debugging issues, since it is hard to check every single situation, but the code does run successfully for the most part. If I would have had more time, I would have made a better visual representation using Qt or a graphs class for Windows instead of having the display on the console. As far as applying topics that we talked about in class, I explored using an `std::multimap` container as well as its iterators. I would have implemented lambdas, but almost all of the functions I wrote were very long. I also considered making the computer's player class a derivated class, but thought that it wasn't really necessary, although it could be better for the program. Here is a basic break down of my files:
### `main.cpp`
This file contain sthe main while loop that runs tha game, which is less than 100 lines of code (probably around 70 without comments). The while loop gets terminated when either the user enters the character `Q` to quit or someone wins, meaning that the count of a player's pieces equals zero. Within the loop, there is an if statment that uses a modulus `%` to determine whether it is an even turn (Player X) or and odd turn (Player O), so that the players alternate turns. Within the loop, there are several calls to functions. There are a few `display()` functions that print the board and moves to the console, as well as functions such as `validMove`, `pickMove`, and `detMove` (determindMove) that call **several** other fuctions. This way, not all the functions have to be called directly from the main routine.
### `CheckersGame.h` and `CheckersGame.cpp`
These files contain the declarations and definitions for the `Player` class and the `CheckBoard` class. The Player class stores the user's symbol/royal values: 9/7 or 8/6. As explained in the comments of the class, certain numbres correlate to particular characters:

|   9   |   8   |   7   |   6   |   1   |   0   |
| --- | --- | --- | --- | --- | --- |
|   X   |   O   |   K   |   Q   |        |    %   |

This way when using a switch statement, it is easy to print the board, since it is stored in a 2-D vector of type: `std::vector<vector<int,int>>` in the CheckBoard class, that looks like:

      {0,9,0,9,0,9,0,9}
      {9,0,9,0,9,0,9,0}
      {0,9,0,9,0,9,0,9}
      {1,0,1,0,1,0,1,0}
      {0,1,0,1,0,1,0,1}
      {8,0,8,0,8,0,8,0}
      {0,8,0,8,0,8,0,8}
      {8,0,8,0,8,0,8,0}
and calling the `display()` function prints:

         0   1   2   3   4   5   6   7
       +---+---+---+---+---+---+---+---+
     0 |%%%| X |%%%| X |%%%| X |%%%| X |
       +---+---+---+---+---+---+---+---+
     1 | X |%%%| X |%%%| X |%%%| X |%%%|
       +---+---+---+---+---+---+---+---+
     2 |%%%| X |%%%| X |%%%| X |%%%| X |
       +---+---+---+---+---+---+---+---+
     3 |   |%%%|   |%%%|   |%%%|   |%%%|
       +---+---+---+---+---+---+---+---+
     4 |%%%|   |%%%|   |%%%|   |%%%|   |
       +---+---+---+---+---+---+---+---+
     5 | O |%%%| O |%%%| O |%%%| O |%%%|
       +---+---+---+---+---+---+---+---+
     6 |%%%| O |%%%| O |%%%| O |%%%| O |
       +---+---+---+---+---+---+---+---+
     7 | O |%%%| O |%%%| O |%%%| O |%%%|
       +---+---+---+---+---+---+---+---+
The player class also stores the number of regular pieces and the number of royal pieces as well as their locations on the board (in coordinate pairs) using a `std::vector<pair<int,int>>`. The class stores all the possible/potenial moves of each piece in an `std::multipmap`, which is only used for Player X (the computer). I decided to use a multimap because it can sort the each piece and its moves by their "rank." The multimap I used is type  `std::pair<double, vector<pair<int,int>>>`, meaning that its "keys" are the ranks and its "values" are vectors that hold the moves which are coordinate pairs of locations on the board (this and the ranking of the moves will be explained later). The Player class has functions that update the piece locations/terminations when either the user or the computer moves. The class also has functions specifically for Player X which determind all moves and pick the best one. Because there are very specific functionalities for Player X (the computer), I think, in the future, it would be best to make it a derived class in order to conserve memory.

The CheckBoard class mainly stores the gameboard, and has accessor functions which display it and mutator functions which either update it when a player moves, checks if they picked a valid move, and takes care of "killed" pieces. Functions that are made private, are called by other functions in the main routine (mentioned above), so there is no reason to call them publically.

*Note: Please read the function documentation within the header file for a better understanding of how both classes work independently and together.*
### `CheckAI.cpp`
This file contains all the fucntions used by Player X, also referred to as the "AI functions." In order to determine the best moves and rank them there is a system:

- First `det_NM` (determine no moves) is called which sees if the piece can move. If the piece **can** move, the function `det_DJ` (determine double jump) is called from within `det_NM` which checks to see if the piece can jump two of  Player O's pieces.
    - If the piece **can** double jump Player O's pieces, the moves are stored in the vector within the multimap and gives it a key (rank) of 1 (the highest ranking). If the piece **cannot** double jump, the function `det_WGDJ` (determine will get double jumped) is called from within `det_DJ`.
    - If the piece **will** get double jumped, the free spots are saved in the vector and the key is set to 2. Then function `find_best_move` is called (however, later on after all the pieces are set, this can be over written if the function `Find` finds a better move by a different piece to block the double jump). If the piece **will not** get double jumped, the function `det_J` (determine jump) is  called from within `det_WGDJ`.
    - If the piece **can** jump one of Player O's pieces, the move is stored in the vector and the key is set to 3. If the piece **cannot** jump, the function `det_WGJ` (will get jumped) is called from within `det_J`.
    - If the piece **will** get jumped by Player O, the function `find_best_move` is called and the key is set to 4. If the piece **will not** get jumped, the function `det_SM` (determine safe move) is called from within `det_WGJ`.
    - If **there is** a safe move, the move is stored and key is set to 5. If **there is not** a safe move, the key is set to 6 and the function `find_best_move` is called from within `det_SM`.
- And lastly, if the piece **cannot** move (and none of these other functions were called), then the piece is given an initial ranking of 7 (the lowest ranking), but then checks to see if it can get doubled jumped/jumped.

#### Summary of move rankings:

| Can Double Jump | Will Get Double Jumped | Can Jump | Will Get Jumped | Safe Move | Risky Move | Cannot Move |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | 2 | 3 | 4 | 5 | 6 | 7 |


The function `find_best_move`, is a coded algorithm that determines either the piece's only option to move and stores it, OR uses **recursion** to find the better move out of two potential ones. It does this by creating two temporary pieces and running them through the `det_NM` algorithm. The piece that returns with the higher ranking, that move get's played.

In a way this is how the computer can "see" into the future. If this algorithm was called several more times, it could potential see several moves ahead and make more sophisticated moves. This could be something to experiment with later.
#
#
*Note: Not everything is commented, since there is (all together) around 2000 lines of code which are constantly being updated/changed.*
