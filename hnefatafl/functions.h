/**
 * @file fonctions.h
 *
 * @brief Declarations of functions for the Hnefatafl game.
 *
 * This file contains the declarations of various functions used in the Hnefatafl game, including
 * board initialization, display, piece movement, capturing, and game state checks.
 *
 * @author JMB - IUT Informatique La Rochelle
 * @date 24/11/2024
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "typeDef.h"


/**
 * @brief Clears the console screen based on the operating system.
 *
 * This function clears the console screen by executing system commands specific to the operating system.
 * On Windows, it uses the "cls" command, while on Linux and macOS, it uses the "clear" command.
 * If the system command fails, an error message is displayed in the console.
 */
void clearConsole();

/**
 * @brief Displays the game logo in ASCII art.
 *
 * This function prints the game logo to the console, which includes ASCII art text and additional
 * information about the game. It displays the logo only once unless explicitly called again.
 */
void displayHnefataflLogo();

/**
 * @brief Asks the user to choose the size of the game board.
 *
 * This function prompts the user to select the desired board size, either 11x11 or 13x13.
 * It then stores the chosen size in the reference variable `aBoardSize` and returns `true`
 * if the input is valid. If the input is invalid (non-integer or incorrect size), it returns `false`.
 *
 * The user is prompted to enter a valid size if an invalid entry is made.
 *
 * @param aBoardSize Reference to the BoardSize variable to store the selected board size.
 * @return `true` if a valid size is chosen, `false` otherwise.
 *
 * @note Valid sizes are 11 for LITTLE (11x11) and 13 for BIG (13x13).
 */
bool chooseSizeBoard(BoardSize& aBoardSize);

/**
 * @brief Dynamically creates a game board.
 *
 * This function allocates memory dynamically for a game board represented by
 * a 2D array of `Cell`. It creates an array of pointers, each pointing to an
 * array of `Cell`, effectively forming a 2D grid. If memory allocation fails
 * at any point, it cleans up any already allocated memory to avoid leaks and
 * returns `false`.
 *
 * @param aBoard Reference to the Board object. `itsSize` should specify the
 *               number of rows and columns for the game board.
 * @return `true` if the board is successfully created, `false` otherwise.
 *
 * @note In case of failure, all previously allocated memory is freed before returning `false`.
 */
bool createBoard(Board& aBoard);

/**
 * @brief Frees the memory allocated for the game board.
 *
 * This function frees the dynamically allocated memory for the game board
 * represented by a 2D array of `Cell`. It deletes each row in the array,
 * then deletes the array itself, and finally sets the `itsCells` pointer to `nullptr`
 * to prevent any accidental access to invalid memory locations. If the board has already
 * been freed, the function does nothing.
 *
 * @param aBoard Reference to the Board object containing the game board.
 *               The `itsCells` pointer will be set to `nullptr` after freeing
 * @param aBoard.itsSize The size of the game board (either LITTLE or BIG).
 *
 * @note If the board has already been freed, this function will simply return without doing anything.
 */
void deleteBoard(Board& aBoard);

/**
 * @brief Displays the game board with the positions of pieces and labels.
 *
 * This function displays the game board, labeling columns with numbers and rows
 * with letters to allow easier reference for the player. The board shows the
 * positions of various game pieces (shields, swords, king, castle, fortresses).
 *
 * @param aBoard The game board object containing the grid of cells.
 * @param aBoard.itsSize The size of the game board, either LITTLE or BIG.
 *
 * @note The function handles both small (11x11) and large (13x13) board sizes
 *       and adjusts the display accordingly.
 */
void displayBoard(const Board& aBoard);

/**
 * @brief Initializes the game board with the specified size.
 *
 * This function initializes the game board, placing the fortresses, king,
 * castle, shields, and swords in appropriate positions based on the chosen
 * board size. The board is represented as a 2D array of cells.
 *
 * @param aBoard The board object that contains a 2D array (`itsCells`) representing the game board.
 * @param aBoard.itsSize The size of the game board (either LITTLE or BIG).
 *
 * @note The function adjusts shield and sword positions based on the board size.
 */
void initializeBoard(Board& aBoard);

/**
 * @brief Checks if a position is valid within the game board.
 *
 * This function verifies whether the provided position, defined by a `Position` structure,
 * falls within the valid bounds of the game board. The validity is determined based on the
 * board's size, ensuring the row and column indices are within the appropriate range.
 * The function returns `true` if the position is within the board's dimensions, and `false`
 * otherwise.
 *
 * @param aPos The `Position` structure to check, containing the row and column indices.
 * @param aBoard The game board, which contains the size information (number of rows and columns).
 *
 * @return True if the position is within the valid range of the board, false otherwise.
 *
 * @note This function assumes that the row and column indices are zero-based (i.e., 0 ≤ row, column < size).
 */
bool isValidPosition(const Position& aPos, const Board& aBoard);

/**
 * @brief Retrieves and validates a position entered by the user in the format of a letter followed by a number.
 *
 * This function prompts the user to enter a position on the game board in the format of a letter (A-Z) followed
 * by a number (1-based index). It validates the input to ensure that:
 * - The first character is a letter (A-Z).
 * - The remaining characters are digits representing a number (1-based column index).
 * - The resulting position is within the bounds of the game board.
 *
 * If the input is valid, the function updates the provided `Position` structure with the row and column indices.
 * If the input is invalid, an error message is displayed, and the function returns `false`.
 *
 * @param aPosition A reference to a `Position` structure that will be updated with the user's input if valid.
 * @param aBoard The game board, used to validate that the input position is within the board's bounds.
 *
 * @return True if the input is valid and the `aPosition` structure is updated; false otherwise.
 *
 * @note The input format must be a single letter followed by one or more digits (e.g., "A1", "C3").
 */
bool getPositionFromInput(Position& aPosition, const Board& aBoard);

/**
 * @brief Check if a specific cell on the game board is empty.
 *
 * This function checks if a particular cell on the game board is empty. A cell is considered
 * empty if it does not contain any game pieces, i.e., its `itsPieceType` is set to `NONE`.
 * The position of the cell to check is provided as input.
 *
 * @param aBoard The game board represented as a 2D array of `Cell` structures.
 * @param aPos The `Position` of the cell to check for emptiness, specifying its row and column.
 *
 * @return True if the cell is empty (contains no game pieces), false if it contains a game piece.
 *
 * @note This function only checks the `itsPieceType` field of the cell, not its `itsCellType`.
 */
bool isEmptyCell(const Board& aBoard, const Position& aPos);

/**
 * @brief Check if a selected move is valid for the current player.
 *
 * This function verifies whether a selected move, from the starting position to the ending position,
 * is valid for the current player. It checks several conditions such as:
 * - Whether the starting position contains a piece of the active player
 *   (either a SWORD for the ATTACK player or a SHIELD/KING for the DEFENSE player).
 * - Whether the move is along the same row or column (horizontal or vertical movement).
 * - Whether there are any obstacles (other pieces or fortresses) in the path of the move.
 *
 * Additionally, the function ensures that fortresses are not crossed by the player,
 * unless the player is the KING, in which case it is allowed.
 *
 * @param aGame The current game context, including the active player and the game board.
 * @param aMove The move to be validated, including the starting and ending positions.
 * @return True if the move is valid according to the game's rules, false otherwise.
 */
bool isValidMovement(const Game& aGame, const Move& aMove);

/**
 * @brief Move a game piece on the game board.
 *
 * This function executes a move by transferring a game piece from the starting position
 * to the ending position on the game board. The piece's type at the starting position
 * is copied to the ending position, and the starting position is then cleared (set to NONE).
 *
 * **Note:** This function assumes that the move is valid. The caller must ensure that
 * the positions involved are valid and conform to the rules of the game before calling
 * this function. For example, this should typically be done after validating the move
 * with functions like `isValidMovement`.
 *
 * @param aGame The `Game` object representing the current game state,
 *        including the board and other game information.
 * @param aMove The `Move` object containing the starting and ending positions for the piece movement.
 */
void movePiece(Game& aGame, const Move& aMove);

/**
 * @brief Remove captured pieces from the game board.
 *
 * This function identifies and removes pieces that have been captured as a result
 * of the current move. It evaluates the cells adjacent to the ending position of the move
 * in all four cardinal directions (up, down, left, and right) and applies the game rules
 * to determine if a capture occurs. Captured pieces are removed from the board.
 *
 * **Capture Rules**:
 * - A piece is captured if it is surrounded by opposing pieces or special cells (e.g., fortress or castle),
 *   depending on the player's role (ATTACK or DEFENSE).
 * - Attackers (SWORD) can capture defenders (SHIELD) when surrounded.
 * - Defenders (SHIELD or KING) can capture attackers (SWORD) when surrounded.
 *
 * @param aGame The `Game` object representing the current state of the game.
 * @param aMove The `Move` object containing the ending position of the player's move.
 *
 * **Note**:
 * - The function assumes the move has already been validated and executed.
 * - It modifies the game board to reflect any captures.
 */
void capturePieces(Game& aGame, const Move& aMove);

/**
 * @brief Switch the current player in the game.
 *
 * This function toggles the active player in the game. If the current player
 * is `itsPlayer1`, it changes to `itsPlayer2`, and if it is `itsPlayer2`, it switches back to `itsPlayer1`.
 * This ensures alternate turns between the two players.
 *
 * **Usage**:
 * - This function is typically called at the end of a turn to prepare for the next player's move.
 *
 * @param aGame Reference to the `Game` object whose `itsCurrentPlayer` attribute will be updated.
 *
 * **Postconditions**:
 * - `itsCurrentPlayer` will point to the player who is next in turn.
 */
void switchCurrentPlayer(Game& aGame);

/**
 * @brief Check if there are any attackers (swords) left on the game board.
 *
 * This function iterates through all the cells of the game board to determine
 * if there are any remaining attacker pieces (`SWORD`). If at least one such piece
 * is found, the function returns `true`; otherwise, it returns `false`.
 *
 * **Usage**:
 * - This function can be used to determine if the attacking player has any remaining pieces,
 *   which is useful for checking end-game conditions.
 *
 * @param aBoard The game board represented as a `Board` structure containing a 2D array of `Cell` structures.
 * @return True if there are any `SWORD` pieces left on the board, false otherwise.
 */
bool isSwordLeft(const Board& aBoard);

/**
 * @brief Get the position of the king on the game board.
 *
 * This function scans the game board to locate the position of the king (`KING`).
 * If the king is found, its position (row and column) is returned as a `Position` structure.
 * If the king is not present on the board, the function returns the default invalid position `{-1, -1}`.
 *
 * **Usage**:
 * - This function is useful for game logic that requires knowing the king's location,
 *   such as checking for victory conditions or evaluating potential moves.
 *
 * @param aBoard The game board represented as a `Board` structure containing a 2D array of `Cell` structures.
 * @return The `Position` of the king if found, or `{-1, -1}` if the king is absent.
 */
Position getKingPosition(const Board& aBoard);

/**
 * @brief Check if the king has escaped to a fortress.
 *
 * This function determines whether the king has successfully escaped by reaching a fortress cell.
 * It retrieves the king's current position using the `getKingPosition` function and verifies
 * whether the cell at that position is of type `FORTRESS`.
 *
 * **Usage**:
 * - This function is essential for determining if the defending player has won the game by
 *   safely moving the king to one of the fortress cells.
 *
 * @param aBoard The game board represented as a `Board` structure containing a 2D array of `Cell` structures.
 * @return `true` if the king is on a fortress cell, `false` otherwise.
 */
bool isKingEscaped(const Board& aBoard);

/**
 * @brief Check if the king is captured by four surrounding elements (attackers, borders, or special cells).
 *
 * This function determines whether the king is captured by evaluating the four neighboring positions
 * (up, down, left, right). The king is considered captured if all four adjacent positions are either:
 * - Outside the board (border),
 * - Occupied by an attacker (SWORD),
 * - A fortress cell,
 * - A castle cell.
 *
 * **Usage**:
 * - This function helps determine if the attacking player has won by capturing the king.
 *
 * @param aBoard The game board represented as a `Board` structure containing a 2D array of `Cell` structures.
 * @return `true` if the king is captured by four elements, `false` otherwise.
 */
bool isKingCaptured(const Board& aBoard);

/**
 * @brief Recursively check if the king is blocked.
 *
 * This function determines if the king is completely surrounded and has no valid moves.
 * It uses recursion to explore neighboring cells and checks whether the king can escape
 * to any free position. If all potential moves are blocked, the king is considered "captured."
 *
 * @param aBoard The game board represented as a structure containing a 2D array of Cell structures.
 * @param aKingPos The position of the king. Defaults to {-1, -1} to find the king's position initially.
 * @return `true` if the king is completely blocked, `false` if it can move to at least one valid position.
 */
//bool isKingCaptured(const Board& aBoard, Position aKingPos = {-1, -1});

/**
 * @brief Determines if the game has finished.
 *
 * This function evaluates the current game state to determine if the game has ended.
 * The game is considered finished if any of the following conditions are met:
 * - The king has been captured.
 * - There are no swords (attackers) left on the board.
 * - The king has successfully escaped to a fortress.
 *
 * @param aGame A constant reference to the Game object being evaluated.
 * @return True if the game is finished, otherwise false.
 */
bool isGameFinished(const Game& aGame);

/**
 * @brief Determines the winner of the game.
 *
 * This function evaluates the current game state to determine the winner, if the game has finished.
 * - If the king has been captured, the attacker (Player 1) is declared the winner.
 * - If the king has escaped, or all swords (attackers) have been eliminated, the defender (Player 2) is declared the winner.
 * - If the game is not yet finished, the function returns `nullptr`.
 *
 * **Usage**:
 * - This function should be called after verifying that the game has ended using `isGameFinished`.
 *
 * @param aGame A constant reference to the `Game` object representing the current game state.
 * @return A pointer to the winning `Player` object, or `nullptr` if the game is not finished.
 */
Player* whoWon(const Game& aGame);

/**
 * @brief playGame is the function where the game is played.
 *
 * This function calls others function to run the game correctly
 * For exemple, this function calls isValidMovement until it return true
 * Then it checks if a piece was captured and if the game is finished.
 *
 * When a game is over, it is asked you if you want to start another one
 */
void playGame();


/**
 * @brief menu is the function that display the menu of the game
 *
 * @return true if the users wants to play
 * @return false if the answer is not in the possible ones
 * @return  display the rules if they want to
 * @return exit(0) if the users decided to quit
 */
bool menu();

/**
 * @brief displayRules is the function that display the rules of the game.
 * It is divided into three parts to make it more visible
 */
void displayRules();

/**
 * @brief playerName is the function that ask the players what name they want to play with
 * @param aGame Reference to the `Game` object whose `itsPlayer1` and 'itsPlayer2' attributes will be updated.
 */
void playerName(Game& aGame);

/**
 * @brief playTests is the function that launch the test given by the software architect.
 *
 * It also display how many tests passed and how many failed.
 * Some cout of this function had been commented for more readability.
 */
void playTests();

/**
 * @brief firstDemo is the function for the first demonstration
 *
 * Used to show the moves and the finish conditions only
 *
 * ⚠This function required to be used cautiously beacause it did not respect some
 * aspects of the game like the playerchange⚠
 *
 *If it finished normaly, it will be asked to press enter to start the second demo.
 */
void firstDemo();

/**
 * @brief secondDemo is the function for the second demonstration
 *
 * Used to show the moves and the finish conditions only
 *
 * ⚠This function required to be used cautiously beacause it did not respect some
 * aspects of the game like the playerchange⚠
 *
 *If it finished normaly, it will be asked to press enter to start the third demo.
 */
void secondDemo();

/**
 * @brief thirdDemo is the function for the third demonstration
 *
 * Used to show the moves and the finish conditions only
 *
 * ⚠This function required to be used cautiously beacause it did not respect some
 * aspects of the game like the playerchange⚠
 *
 *If it finished normaly, it will be asked to start the game or to quit
 */
void thirdDemo();



#endif // FUNCTIONS_H
