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
This file contains the main while loop that runs tha game, that is less than 100 lines of code (probably around 70 without comments). The while loop gets terminated when either the user enters the character `Q` to quit or someone wins, meaning that the count of a player's pieces equals zero. Within the loop, there is an if statment that uses a modulus `%` to determine whether it is an even turn (Player X) or and odd turn (Player O), so that the players alternate turns. Within the loop, there are several calls to functions. There are a few `display()` functions that print the board and moves to the console, as well as functions such as `validMove`, `pickMove`, and `detMove` (determindMove) actually call **several** other fuctions. This way, not all the functions have to be called directly from the main routine.
### `CheckersGame.h` and `CheckersGame.cpp`
This file contains the declarations for the `Player` class and the `CheckBoard` class. The Player class stores the user's symbol/royal values: 9/7 or 8/6. As explained in the comments of the class, certain numbres correlate to particular characters:

|   9   |   8   |   7   |   6   |   1   |   0   |
| --- | --- | --- | --- | --- | --- |
|   X   |   O   |   K   |   Q   |        |    %   |

This way when using a switch statement, it is easy to print the board, since it is stored in a 2-D vector of type: `std::vector<vector<int,int>>` . The player class also stores the number of regular pieces and the number of royal pieces as well as their locations on the board (in coordinate pairs) using a `std::vector<pair<int,int>>`. The class also stores all the possible/potenial moves of each piece in an `std::multipmap`, which is only used for (computer) Player X. I decided to use a multimap because it can "rank" each piece based on each move. The multimap I used is type  `std::pair<double, vector<pair<int,int>>>`, meaning that its "keys" are the ranks and its "values" are vectors which hold the moves which are coordinate pairs of locations on the board (this and the ranking of the moves will be explained later). The Player class has functions that updates the piece locations/terminations when either the user or the computer moves, as well as functions just specifically for Player X, to determind all moves and pick the best one. Because there are very specific functionalities for Player X (the computer), I think, in the future, it would be best to make it a derived class in order to conserve memory.

The CheckBoard class mainly stores the board, and has accessor functions which display it and mutator functions which either update it when a player moves, checks if they picked a valid move, and takes care of "killed" pieces. Functions that are made private, are called by other functions in the main routine (mentioned above), so there is no reason to call them publically.

*Note: Please read the function documentation within the file for a better understanding of how both classes work independently and together.*
### `CheckAI.cpp`
      
*Note: Not everything is commented, since there is (all together) around 2000 lines of code.*
