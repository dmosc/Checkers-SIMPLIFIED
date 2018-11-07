# Checkers-SIMPLIFIED

///Game description
"Checkers simplified" is an awesome and fun alternative to the typical checkers boardgame we all know.
The main objective of the game is to capture all the other player pieces.

Some things to point out!

The 'SIMPLIFIED' part of the name comes from the fact that crowning is not valid on this simplified version
of checkers. Meaning that, if any of the opponent pieces gets to the other side of the board, instead of
crowning that piece, as it is accustomed, it will just stay there, and the player who owns that piece, won't
be able to move it again.

The '=' characters represent the black checkboxes and the left ones are considered the white ones.
The pieces of each player can be distinguished with 'X' and 'O'.

Alternatively, each player must input their move into the console with the following format:
[Y-N] *This question will appear before every move. Just to ensure that each player wants to continue playing.*
[row] [column] [direction]
[1-8] [1-8] [J-K]
***'J' being a diagonal move to the left and 'K' a diagonal move to the right***

!!!WARNING!!!
If the player in turn inputs values for a move that is not TECHNICALLY VALID (OOB, an occupied checkbox, 
trying to eat a piece when the landing spot is occupied), 
the program will simply ignore the current player move and pass the turn to the other player. 
So be careful, and input your values correctly.