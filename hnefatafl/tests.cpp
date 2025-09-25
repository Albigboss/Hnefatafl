/**
 * @file tests.cpp
 *
 * @brief Implementation of test functions for testing the fonctions implemented in 'fonctions.cpp'.
 *
 * This file contains the implementation of test functions used to verify and validate
 * the functionality of the functions implemented in 'fonctions.cpp.'
 * These test functions are designed to thoroughly test various aspects of the code
 * in 'fonctions.cpp' to ensure that it performs as expected.
 * They cover a range of scenarios and edge cases, helping to identify and resolve
 * any potential issues or bugs in the codebase.
 * The tests are conducted on different board sizes and configurations,
 * providing comprehensive coverage to guarantee the reliability and correctness
 * of the functions in 'fonctions.cpp.'
 * Overall, 'test.cpp' plays a crucial role in maintaining code quality and robustness by confirming
 * that the functions it tests meet their intended specifications."
 *
 * @author JMB - IUT Informatique La Rochelle
 * @date 24/11/2024
 */

#include <iostream>
#include <sstream>

#include "typeDef.h"
#include "functions.h"

using namespace std;

void resetBoard(Cell**& aBoard, const BoardSize& aBoardSize);
Cell** cb(const BoardSize& aBoardSize);
void db(Cell**& aBoard,const BoardSize& aBoardSize);

/**
 * @brief Test function for the chooseSizeBoard function.
 *
 * This function tests the chooseSizeBoard function by simulating user input and
 * checking the returned values.
 */
void test_chooseSizeBoard()
{
    cout << "********* Start testing of chooseSizeBoard *********" << endl;
    int pass = 0; // Count of tests passed
    int failed = 0; // Count of tests failed

    // Redirect std::cin to a stringstream 'input'
    stringstream input;
    streambuf* OldBuf = cin.rdbuf(input.rdbuf());

    BoardSize yourBoardSize; // Variable to store the selected board size

    // Test 1: Simulate user input "11"
    input << "11\n";
    if (chooseSizeBoard(yourBoardSize) && yourBoardSize == LITTLE)
    {
        cout << endl << "PASS \t: " << "11" << endl << endl;
        pass++;
    }
    else
    {
        cout << endl <<  "FAIL! \t: " << "\n\tActual false " << yourBoardSize << "\n\texpected true and 11" << endl << endl;
        failed++;
    }

    // Test 2: Simulate user input "13"
    input << "13\n";
    if (chooseSizeBoard(yourBoardSize) && yourBoardSize == BIG)
    {
        cout << endl << "PASS \t: " << "13" << endl << endl;
        pass++;
    }
    else
    {
        cout << endl <<  "FAIL! \t: " << "\n\tActual false" << yourBoardSize << "\n\texpected true and 13" << endl << endl;
        failed++;
    }

    // Test 3: Simulate user input "12"
    input << "12\n";
    if (!chooseSizeBoard(yourBoardSize))
    {
        cout << endl << "PASS \t: " << "12" << endl << endl;
        pass++;
    }
    else
    {
        cout << endl <<  "FAIL! \t: " << "\n\tActual true" << "\n\texpected false" << endl;
        failed++;
    }

    // Test 4: Simulate user input "2d" (invalid input)
    input << "2d\n";
    if (!chooseSizeBoard(yourBoardSize))
    {
        cout << endl << "PASS \t: " << "2d" << endl << endl;
        pass++;
    }
    else
    {
        cout << endl <<  "FAIL! \t: " << "\n\tActual true" << "\n\texpected false" << endl << endl;
        failed++;
    }

    // Restore the initial streambuf of std::cin (output to console)
    cin.rdbuf(OldBuf);

    // Display test results
    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of chooseSizeBoard *********" << endl << endl;
}


/**
 * @brief Test function for the createBoard function.
 *
 * This function tests the createBoard function by verifying that boards are correctly allocated
 * for different sizes.
 */
void test_createBoard() {
    cout << "********* Start testing of createBoard *********" << endl;
    int pass = 0;
    int failed = 0;

    // Test for LITTLE board size
    Board littleBoard = {nullptr, LITTLE};
    if (createBoard(littleBoard)) {
        cout << "PASS \t: LITTLE board created correctly." << endl;
        pass++;
        deleteBoard(littleBoard);
    } else {
        cout << "FAIL! \t: LITTLE board not allocated correctly." << endl;
        failed++;
    }

    // Test for BIG board size
    Board bigBoard = {nullptr, BIG};
    if (createBoard(bigBoard)) {
        cout << "PASS \t: BIG board created correctly." << endl;
        pass++;
        deleteBoard(bigBoard);
    } else {
        cout << "FAIL! \t: BIG board not allocated correctly." << endl;
        failed++;
    }

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of createBoard *********" << endl;
}


/**
 * @brief Test function for the deleteBoard function.
 *
 * This function tests the deleteBoard function by ensuring that boards are correctly deleted
 * and pointers are set to nullptr after deletion.
 */
void test_deleteBoard() {
    cout << "********* Start testing of deleteBoard *********" << endl;
    int pass = 0; // Count of tests passed
    int failed = 0; // Count of tests failed

    try {
        // Test for LITTLE board size
        Board littleBoard = {nullptr, LITTLE};
        littleBoard.itsCells = cb(LITTLE);
        deleteBoard(littleBoard);

        if (littleBoard.itsCells == nullptr) {
            cout << "PASS \t: LITTLE board deleted correctly." << endl;
            pass++;
        } else {
            cout << "FAIL! \t: LITTLE board not deleted correctly." << endl;
            failed++;
        }

        // Test for BIG board size
        Board bigBoard = {nullptr, BIG};
        bigBoard.itsCells = cb(BIG);
        deleteBoard(bigBoard);

        if (bigBoard.itsCells == nullptr) {
            cout << "PASS \t: BIG board deleted correctly." << endl;
            pass++;
        } else {
            cout << "FAIL! \t: BIG board not deleted correctly." << endl;
            failed++;
        }
    } catch (const exception& e) {
        cout << "FAIL! \t: Exception caught during deleteBoard: "
             << e.what()
             <<"."<<endl;
        failed++;
    }

    // Display test results
    cout <<"Totals:"<<pass<<"passed,"<<failed<<"failed"<<endl;

    cout<<"*********Finished testing of delete Board*********"<<endl<<endl;

}


/**
 * @brief Test function for the initializeBoard function.
 *
 * This function tests the initializeBoard function by comparing the generated board with expected board configurations.
 */
void test_initializeBoard()
{
    cout << "********* Start testing of initializeBoard *********" << endl;
    int pass = 0; // Count of tests passed
    int failed = 0; // Count of tests failed

    // Test on a small board
    Cell** bLittle = cb(LITTLE);
    BoardSize little = LITTLE;

    // Initialize the board with empty cells
    resetBoard(bLittle, little);

    // Set positions for fortresses (exits)
    bLittle[0][0].itsCellType = FORTRESS;
    bLittle[0][little-1].itsCellType = FORTRESS;
    bLittle[little-1][0].itsCellType = FORTRESS;
    bLittle[little-1][little-1].itsCellType = FORTRESS;

    // Set positions for the king and castle
    Position kingPos = { (little - 1) / 2, (little - 1) / 2 };
    bLittle[kingPos.itsRow][kingPos.itsCol] = {CASTLE, KING};

    // Set positions for shields (defenders)
    Position shieldsPositionsLittle[] = {
                                         { kingPos.itsRow - 1, kingPos.itsCol },
                                         { kingPos.itsRow + 1, kingPos.itsCol },
                                         { kingPos.itsRow, kingPos.itsCol - 1 },
                                         { kingPos.itsRow, kingPos.itsCol + 1 },
                                         { kingPos.itsRow - 1, kingPos.itsCol - 1 },
                                         { kingPos.itsRow + 1, kingPos.itsCol + 1 },
                                         { kingPos.itsRow - 1, kingPos.itsCol + 1 },
                                         { kingPos.itsRow + 1, kingPos.itsCol - 1 },
                                         { kingPos.itsRow - 2, kingPos.itsCol },
                                         { kingPos.itsRow + 2, kingPos.itsCol },
                                         { kingPos.itsRow, kingPos.itsCol - 2 },
                                         { kingPos.itsRow, kingPos.itsCol + 2 },
                                         };

    for (const Position& pos : shieldsPositionsLittle) {
        bLittle[pos.itsRow][pos.itsCol].itsPieceType = SHIELD;
    }

    // Set positions for swords (attackers)
    Position swordsPositionsLittle[] = {
                                        { kingPos.itsRow, 0 },
                                        { kingPos.itsRow - 1, 0 },
                                        { kingPos.itsRow - 2, 0 },
                                        { kingPos.itsRow + 1, 0 },
                                        { kingPos.itsRow + 2, 0 },
                                        { kingPos.itsRow, 1 },
                                        { kingPos.itsRow, little-1},
                                        { kingPos.itsRow - 1, little-1 },
                                        { kingPos.itsRow - 2, little-1 },
                                        { kingPos.itsRow + 1, little-1 },
                                        { kingPos.itsRow + 2, little-1 },
                                        { kingPos.itsRow, little-2 },
                                        { 0, kingPos.itsCol },
                                        { 0, kingPos.itsCol - 1 },
                                        { 0, kingPos.itsCol - 2 },
                                        { 0, kingPos.itsCol + 1 },
                                        { 0, kingPos.itsCol + 2 },
                                        { 1, kingPos.itsCol },
                                        { little-1, kingPos.itsCol },
                                        { little-1, kingPos.itsCol - 1 },
                                        { little-1, kingPos.itsCol - 2 },
                                        { little-1, kingPos.itsCol + 1 },
                                        { little-1, kingPos.itsCol + 2 },
                                        { little-2, kingPos.itsCol },
                                        };

    for (const Position& pos : swordsPositionsLittle) {
        bLittle[pos.itsRow][pos.itsCol].itsPieceType = SWORD;
    }

    Board yourLittleBoard = {nullptr, LITTLE};
    yourLittleBoard.itsCells = cb(LITTLE);
    initializeBoard(yourLittleBoard);


    // Compare the generated board with the expected configuration
    for (int i = 0; i < little; ++i) {
        for (int j = 0; j < little; ++j) {
            if (yourLittleBoard.itsCells[i][j].itsCellType != bLittle[i][j].itsCellType
                || yourLittleBoard.itsCells[i][j].itsPieceType != bLittle[i][j].itsPieceType)
            {
                failed++;
            }
        }
    }
    if (failed) {
        cout << "FAIL ! \t: " << failed << " different cases" << endl;
        cout << endl << "\tActual " << endl;
        //displayBoard(yourLittleBoard);
        cout << endl << "\tExpected " << endl;
        //displayBoard({bLittle, little});
        cout << endl;
    }
    else
    {
        cout << "PASS ! \t: " << endl;
        //displayBoard(yourLittleBoard);
        cout << endl;
        pass++;
    }

    db(bLittle,LITTLE);
    db(yourLittleBoard.itsCells,LITTLE);


    // Test on a big board
    Cell** bBig = cb(BIG);
    BoardSize big = BIG;

    // Initialize the board with empty cells
    resetBoard(bBig, big);

    // Set positions for fortresses (exits)
    bBig[0][0].itsCellType = FORTRESS;
    bBig[0][big-1].itsCellType = FORTRESS;
    bBig[big-1][0].itsCellType = FORTRESS;
    bBig[big-1][big-1].itsCellType = FORTRESS;

    // Set positions for the king and castle
    kingPos = { (big - 1) / 2, (big - 1) / 2 };
    bBig[kingPos.itsRow][kingPos.itsCol] = {CASTLE, KING};

    // Set positions for shields (defenders)
    Position shieldsPositionsBIG[] = {
                                      { kingPos.itsRow - 1, kingPos.itsCol },
                                      { kingPos.itsRow + 1, kingPos.itsCol },
                                      { kingPos.itsRow, kingPos.itsCol - 1 },
                                      { kingPos.itsRow, kingPos.itsCol + 1 },
                                      { kingPos.itsRow - 2, kingPos.itsCol },
                                      { kingPos.itsRow + 2, kingPos.itsCol },
                                      { kingPos.itsRow, kingPos.itsCol + 2 },
                                      { kingPos.itsRow, kingPos.itsCol - 2 },
                                      { kingPos.itsRow - 3, kingPos.itsCol },
                                      { kingPos.itsRow + 3, kingPos.itsCol },
                                      { kingPos.itsRow, kingPos.itsCol - 3 },
                                      { kingPos.itsRow, kingPos.itsCol + 3 },
                                      };

    for (const Position& pos : shieldsPositionsBIG) {
        bBig[pos.itsRow][pos.itsCol].itsPieceType = SHIELD;
    }

    // Set positions for swords (attackers)
    Position swordsPositionsBIG[] = {
                                     { kingPos.itsRow, 0 },
                                     { kingPos.itsRow - 1, 0 },
                                     { kingPos.itsRow - 2, 0 },
                                     { kingPos.itsRow + 1, 0 },
                                     { kingPos.itsRow + 2, 0 },
                                     { kingPos.itsRow, 1 },
                                     { kingPos.itsRow, big-1},
                                     { kingPos.itsRow - 1, big-1 },
                                     { kingPos.itsRow - 2, big-1 },
                                     { kingPos.itsRow + 1, big-1 },
                                     { kingPos.itsRow + 2, big-1 },
                                     { kingPos.itsRow, big-2 },
                                     { 0, kingPos.itsCol },
                                     { 0, kingPos.itsCol - 1 },
                                     { 0, kingPos.itsCol - 2 },
                                     { 0, kingPos.itsCol + 1 },
                                     { 0, kingPos.itsCol + 2 },
                                     { 1, kingPos.itsCol },
                                     { big-1, kingPos.itsCol },
                                     { big-1, kingPos.itsCol - 1 },
                                     { big-1, kingPos.itsCol - 2 },
                                     { big-1, kingPos.itsCol + 1 },
                                     { big-1, kingPos.itsCol + 2 },
                                     { big-2, kingPos.itsCol },
                                     };

    for (const Position& pos : swordsPositionsBIG) {
        bBig[pos.itsRow][pos.itsCol].itsPieceType = SWORD;
    }

    Board yourBigBoard = {nullptr, BIG};
    yourBigBoard.itsCells = cb(BIG);
    initializeBoard(yourBigBoard);

    // Compare the generated board with the expected configuration
    for (int i = 0; i < big; ++i) {
        for (int j = 0; j < big; ++j) {
            if (yourBigBoard.itsCells[i][j].itsCellType != bBig[i][j].itsCellType
                || yourBigBoard.itsCells[i][j].itsPieceType != bBig[i][j].itsPieceType)
            {
                failed++;
            }
        }
    }
    if (failed) {
        cout << "FAIL ! \t: " << failed << " different cases" << endl;
        cout << endl << "\tActual " << endl;
        //displayBoard(yourBigBoard);
        cout << endl << "\tExpected " << endl;
        //displayBoard({bBig, big});
        cout << endl;
    }
    else
    {
        cout << "PASS ! \t: " << endl;
        //displayBoard(yourBigBoard);
        cout << endl;
        pass++;
    }

    db(bBig,LITTLE);
    db(yourBigBoard.itsCells,LITTLE);


    // Display test results
    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of initializeBoard *********" << endl << endl;
}


/**
 * @brief Test function for the isValidPosition function.
 *
 * This function tests the isValidPosition function for different board sizes, valid positions, and invalid positions.
 * It counts the number of tests passed and failed and displays the results.
 */
void test_isValidPosition()
{
    cout << "********* Start testing of isValidPosition *********" << endl;
    int pass = 0; // Count of tests passed
    int failed = 0; // Count of tests failed

    BoardSize sizes[2] = {LITTLE, BIG}; // Board sizes to test

    for (BoardSize size : sizes)
    {
        if (size == LITTLE) cout << "LITTLE board :" << endl;
        else cout << "BIG board :" << endl;

        // Valid positions to test
        Position validPositionsToTest[] =
            {
             {0, 0},
             {0, size-1},
             {size-1, 0},
             {size-1, size-1},
             };

        // Invalid positions to test
        Position invalidPositionsToTest[] =
            {
             {-1, 0},
             {0, -1},
             {size, 0},
             {0, size},
             };

        // Test valid positions
        for(Position aPos : validPositionsToTest){
            if (isValidPosition(aPos, {nullptr, size}))
            {
                cout << "PASS \t: " << aPos.itsRow << " " << aPos.itsCol << " is a valid position." << endl;
                pass++;
            }
            else
            {
                cout << "FAIL! \t: " << aPos.itsRow << " " << aPos.itsCol << "\n\tActual invalid position " <<
                    "\n\tExpected valid position" << endl;
                failed++;
            }
        }

        // Test invalid positions
        for(Position aPos : invalidPositionsToTest){
            if (!isValidPosition(aPos, {nullptr, size}))
            {
                cout << "PASS \t: " << aPos.itsRow << " " << aPos.itsCol << " is an invalid position." << endl;
                pass++;
            }
            else
            {
                cout << "FAIL! \t: " << aPos.itsRow << " " << aPos.itsCol << "\n\tActual valid position " <<
                    "\n\tExpected invalid position" << endl;
                failed++;
            }
        }
    }

    // Display test results
    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of isValidPosition *********" << endl << endl;
}


/**
 * @brief Test function for the getPositionFromInput function.
 *
 * This function tests the getPositionFromInput function by providing various input strings and comparing the
 * returned positions with expected positions.
 */
void test_getPositionFromInput() {
    cout << "********* Start testing of getPositionFromInput *********" << endl;

    int pass = 0; // Count of tests passed
    int failed = 0; // Count of tests failed

    struct TestCase {
        string input;
        bool expectedResult;
        int expectedRow;
        int expectedCol;
        BoardSize boardSize;
    };

    TestCase testCases[] = {
        {"A1", true, 0, 0, LITTLE},
        {"K11", true, 10, 10, LITTLE},
        {"A1", true, 0, 0, BIG},
        {"M13", true, 12, 12, BIG},
        {"L11", false, -1, -1, LITTLE}, // Row ut of bounds for LITTLE
        {"K12", false, -1, -1, LITTLE}, // Column out of bounds for LITTLE
        {"N13", false, -1, -1, BIG}, // Row ut of bounds for BIG
        {"C14", false, -1, -1, BIG}, // Column out of bounds for BIG
        {"1A", false, -1, -1, LITTLE}, // Invalid format
        {"AA", false, -1, -1, BIG}, // Invalid format
    };

    for (const TestCase& testCase : testCases) {
        Position position;

        istringstream input(testCase.input);
        cin.rdbuf(input.rdbuf());

        bool result = getPositionFromInput(position, {nullptr, testCase.boardSize});

        cout << "Test Case:" << endl;
        cout << "  Input        : " << testCase.input << endl;
        cout << "  Board Size   : " << (testCase.boardSize == LITTLE ? "LITTLE" : "BIG") << endl;
        cout << "  Expected     : " << (testCase.expectedResult ? "Valid" : "Invalid") << endl;
        cout << "  Result       : " << (result ? "Valid" : "Invalid") << endl;

        bool passed = (result == testCase.expectedResult);

        if (result && testCase.expectedResult) {
            cout << "  Expected Pos : (" << testCase.expectedRow << ", " << testCase.expectedCol << ")" << endl;
            cout << "  Obtained Pos : (" << position.itsRow << ", " << position.itsCol << ")" << endl;
            if (position.itsRow != testCase.expectedRow || position.itsCol != testCase.expectedCol) {
                cout << "  Status       : FAILED (Position mismatch)" << endl;
                passed = false;
            }
        }

        if (passed) {
            pass++;
            cout << "  Status       : PASSED" << endl;
        } else {
            failed++;
            cout << "  Status       : FAILED" << endl;
        }

        cout << endl;
    }

    cout << "********* Test Summary *********" << endl;
    cout << "Total Tests    : " << (pass + failed) << endl;
    cout << "Passed         : " << pass << endl;
    cout << "Failed         : " << failed << endl;
    cout << "Success Rate   : " << (pass * 100.0 / (pass + failed)) << "%" << endl;
}



/**
 * @brief Test function for the isEmptyCell function.
 *
 * This function tests the isEmptyCell function for different cell types and positions.
 * It counts the number of tests passed and failed and displays the results.
 */
void test_isEmptyCell()
{
    cout << "********* Start testing of isEmptyCell *********" << endl;
    int pass = 0; // Count of tests passed
    int failed = 0; // Count of tests failed

    Cell** b = cb(BIG);
    resetBoard(b, BIG); // Reset the board to BIG size
    b[0][0] = {NORMAL, SWORD};
    b[0][1] = {NORMAL, SHIELD};
    b[0][2] = {NORMAL, KING};
    b[1][0] = {FORTRESS, KING};
    b[1][1] = {FORTRESS, NONE};
    b[2][0] = {CASTLE, KING};
    b[2][1] = {CASTLE, NONE};

    // Display the board for reference
    //displayBoard({b, BIG});

    // Positions with non-empty cells to test
    Position nonEmptyPositionsToTest[] =
        {
            {0, 0},
            {0, 1},
            {0, 2},
            {1, 0},
            {2, 0}
        };

    // Positions with empty cells to test
    Position emptyPositionsToTest[] =
        {
            {0, 3},
            {1, 1},
            {2, 1}
        };

    // Expected results for each position
    string posToTest[] = {
        "A1 -> NORMAL / SWORD",
        "A2 -> NORMAL / SHIELD",
        "A3 -> NORMAL / KING",
        "B1 -> FORTRESS / KING",
        "C1 -> CASTLE / KING",
        "A4 -> NORMAL / NONE",
        "B2 -> FORTRESS / NONE",
        "C2 -> CASTLE / NONE"
    };

    int nTest = 0; // Test counter
    for(Position aPos : nonEmptyPositionsToTest){
        if (!isEmptyCell({b, BIG}, aPos))
        {
            cout << "PASS \t: " << posToTest[nTest++] << " is not empty." << endl;
            pass++;
        }
        else
        {
            cout << "FAIL! \t: " << posToTest[nTest++] << "\n\tActual is empty " <<
                "\n\tExpected is not empty" << endl;
            failed++;
        }
    }

    for(Position aPos : emptyPositionsToTest){
        if (isEmptyCell({b, BIG}, aPos))
        {
            cout << "PASS \t: " << posToTest[nTest++] << " is empty." << endl;
            pass++;
        }
        else
        {
            cout << "FAIL! \t: " << posToTest[nTest++] << "\n\tActual is not empty " <<
                "\n\tExpected is empty" << endl;
            failed++;
        }
    }

    db(b,BIG);

    // Display test results
    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of isEmptyCell *********" << endl << endl;
}

/**
 * @brief Test function for the isValidMovement function.
 *
 * This function tests the isValidMovement function for different types of moves
 * (ATTACK and DEFENSE) and various scenarios, including piece types and board cell types.
 * It counts the number of tests passed and failed and displays the results.
 */
void test_isValidMovement()
{
    cout << "********* Start testing of isValidMovement *********" << endl;
    int pass = 0; // Count of tests passed
    int failed = 0; // Count of tests failed

    Game game;
    game.itsBoard.itsSize = LITTLE;
    game.itsBoard.itsCells = cb(LITTLE);
    game.itsCurrentPlayer = &game.itsPlayer1;

    resetBoard(game.itsBoard.itsCells,LITTLE);

    // Attack: Try to move the king - should fail
    game.itsBoard.itsCells[1][1].itsPieceType = KING;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{1, 1}, {2, 1}}))
    {
        cout << "PASS \t: " << "Attack can't move the king in B2! " << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Attack move the king ! " << "\n\texpected Attack can't move the king in B2 !" << endl;
        failed++;
    }

    // Attack: Try to move a shield - should fail
    game.itsBoard.itsCells[2][2].itsPieceType = SHIELD;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{2, 2}, {2, 3}}))
    {
        cout << "PASS \t: " << "Attack can't move a shield in C3 !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Attack move a shield ! " << "\n\texpected Attack can't move a shield in C3 !" << endl;
        failed++;
    }

    // Attack: Try to move a sword - should pass
    game.itsBoard.itsCells[3][3].itsPieceType = SWORD;
    //displayBoard(game.itsBoard);
    if(isValidMovement(game, {{3, 3}, {2, 3}}))
    {
        cout << "PASS \t: " << "Attack can move a sword in C3 to B3 !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Attack can't move a sword ! " << "\n\texpected Attack can move a sword in C3 to B3 !" << endl;
        failed++;
    }

    // Attack: Try to move from an empty cell - should fail
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{4, 4}, {5, 4}}))
    {
        cout << "PASS \t: " << "Attack can't move from an empty cell in E5 !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Attack can move from an empty cell ! " << "\n\texpected Attack can't move from an empty cell in E5 !" << endl;
        failed++;
    }

    // Defense: Try to move the king - should pass
    game.itsCurrentPlayer = &game.itsPlayer2;
    game.itsBoard.itsCells[1][1].itsPieceType = KING;
    //displayBoard(game.itsBoard);
    if(isValidMovement(game, {{1, 1}, {2, 1}}))
    {
        cout << "PASS \t: " << "Defense can move the king in B2 to B1 !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Defense can't move the king ! " << "\n\texpected Defense can move the king in B2 to B1 !" << endl;
        failed++;
    }

    // Defense: Try to move a shield - should pass
    game.itsBoard.itsCells[2][2].itsPieceType = SHIELD;
    //displayBoard(game.itsBoard);
    if(isValidMovement(game, {{2, 2}, {2, 5}}))
    {
        cout << "PASS \t: " << "Defense can move a shield in C3 to C6 !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Defense can't move a shield ! " << "\n\texpected Defense can move a shield in C3 to C6 !" << endl;
        failed++;
    }

    // Defense: Try to move a sword - should fail
    game.itsBoard.itsCells[3][3].itsPieceType = SWORD;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{3, 3}, {2, 3}}))
    {
        cout << "PASS \t: " << "Defense can't move a sword in D4!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Defense can move a sword ! " << "\n\texpected Defense can't move a sword in D4 !" << endl;
        failed++;
    }

    // Defense: Try to move from an empty cell - should fail
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{9, 8}, {9, 4}}))
    {
        cout << "PASS \t: " << "Defense can't move from an empty cell in J9 !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Defense can move from an empty cell ! " << "\n\texpected Defense can't move from an empty cell in J9 !" << endl;
        failed++;
    }

    // Try to move a piece not in the same row or column - should fail
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{2, 2}, {6, 1}}))
    {
        cout << "PASS \t: " << "Movement from C3 to G2 is impossible if it's not the same row or the same column!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual move from C3 to G2 is possible ! " << "\n\texpected Movement from C3 to G2 is impossible if it's not the same row or the same column!" << endl;
        failed++;
    }

    // Piece in the way - SWORD attack
    game.itsCurrentPlayer = &game.itsPlayer1;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[3][3].itsPieceType = SWORD;
    game.itsBoard.itsCells[5][3].itsPieceType = SHIELD;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{3, 3}, {7, 3}}))
    {
        cout << "PASS \t: " << "Movement D4 to H4 is impossible a piece is in the way!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual move is possible ! " << "\n\texpected Movement D4 to H4 is impossible a piece is in the way!" << endl;
        failed++;
    }

    // Piece in the way - SHIELD defense
    game.itsCurrentPlayer = &game.itsPlayer2;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[3][3].itsPieceType = SHIELD;
    game.itsBoard.itsCells[3][6].itsPieceType = SWORD;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{3, 3}, {3, 7}}))
    {
        cout << "PASS \t: " << "Movement D4 to D8 is impossible a piece is in the way!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual move is possible ! " << "\n\texpected Movement D4 to D8 is impossible a piece is in the way!" << endl;
        failed++;
    }

    // Piece in the way - KING attack
    game.itsCurrentPlayer = &game.itsPlayer1;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[4][7].itsPieceType = SWORD;
    game.itsBoard.itsCells[4][2].itsPieceType = KING;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{4, 7}, {4, 2}}))
    {
        cout << "PASS \t: " << "Movement E8 to E3 is impossible a piece is in the way!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual move is possible ! " << "\n\texpected Movement E8 to E3 is impossible a piece is in the way!" << endl;
        failed++;
    }

    // Fortress in the way - ATTACK
    game.itsCurrentPlayer = &game.itsPlayer1;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[0][7].itsPieceType = SWORD;
    game.itsBoard.itsCells[0][0].itsCellType = FORTRESS;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{0, 7}, {0, 0}}))
    {
        cout << "PASS \t: " << "Movement A8 to A1 is impossible to cross a fortress!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual move is possible ! " << "\n\texpected Movement A8 to A1 is impossible to cross a fortress!" << endl;
        failed++;
    }

    // Fortress in the way - DEFENSE
    game.itsCurrentPlayer = &game.itsPlayer2;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[LITTLE-1][7].itsPieceType = SHIELD;
    game.itsBoard.itsCells[LITTLE-1][LITTLE-1].itsCellType = FORTRESS;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{LITTLE-1, 7}, {LITTLE-1, LITTLE-1}}))
    {
        cout << "PASS \t: " << "Movement K8 to K11 is impossible to cross a fortress!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual move is possible ! " << "\n\texpected Movement K8 to K11 is impossible to cross a fortress!" << endl;
        failed++;
    }

    // Castle in the way - DEFENSE
    game.itsCurrentPlayer = &game.itsPlayer2;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[5][7].itsPieceType = SHIELD;
    game.itsBoard.itsCells[5][5].itsCellType = CASTLE;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{5, 7}, {5, 2}}))
    {
        cout << "PASS \t: " << "Movement F8 to F3 is impossible to cross the castle!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual move is possible ! " << "\n\texpected Movement F8 to F3 is impossible to cross the castle!" << endl;
        failed++;
    }

    // Castle in the way - ATTACK
    game.itsCurrentPlayer = &game.itsPlayer1;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[7][5].itsPieceType = SWORD;
    game.itsBoard.itsCells[5][5].itsCellType = CASTLE;
    //displayBoard(game.itsBoard);
    if(!isValidMovement(game, {{7, 5}, {5, 5}}))
    {
        cout << "PASS \t: " << "Movement H6 to F6 is impossible to cross the castle!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual move is possible ! " << "\n\texpected Movement H6 to F6 is impossible to cross the castle!" << endl;
        failed++;
    }

    // King finishing on a castle - DEFENSE
    game.itsCurrentPlayer = &game.itsPlayer2;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[7][5].itsPieceType = KING;
    game.itsBoard.itsCells[5][5].itsCellType = CASTLE;
    //displayBoard(game.itsBoard);
    if(isValidMovement(game, {{7, 5}, {5, 5}}))
    {
        cout << "PASS \t: " << "Movement H6 to F6 is possible if it's the king!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Movement H6 to F6 is impossible ! " << "\n\texpected Movement H6 to F6 is possible if it's the king" << endl;
        failed++;
    }

    // King finishing on a fortress - DEFENSE
    game.itsCurrentPlayer = &game.itsPlayer2;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[4][0].itsPieceType = KING;
    game.itsBoard.itsCells[LITTLE-1][0].itsCellType = FORTRESS;
    //displayBoard(game.itsBoard);
    if(isValidMovement(game, {{4, 0}, {LITTLE-1, 0}}))
    {
        cout << "PASS \t: " << "Movement E1 to K1 is possible if it's the king!" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Movement E1 to K1 is impossible ! " << "\n\texpected Movement E1 to K1 is possible if it's the king" << endl;
        failed++;
    }

    db(game.itsBoard.itsCells,LITTLE);

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of isValidMovement *********" << endl << endl;
}

/**
 * @brief Test the movePiece function with different board sizes and piece types.
 *
 * This function tests the movePiece function by setting up various scenarios
 * with different board sizes (LITTLE and BIG) and different piece types (SWORD, SHIELD, KING).
 * It verifies whether pieces are correctly moved on the board.
 */
void test_movePiece()
{
    // Display the start of the movePiece testing.
    cout << "********* Start testing of movePiece *********" << endl;

    // Initialize pass and failed counters.
    int pass = 0;
    int failed = 0;

    // Create an array of board sizes to test (LITTLE and BIG).
    BoardSize sizes[2] = {LITTLE, BIG};

    // Iterate through the board sizes.
    for (BoardSize size : sizes)
    {
        // Display the current board size being tested.
        if (size == LITTLE)
            cout << "LITTLE board :" << endl;
        else
            cout << "BIG board :" << endl;

        // Create a 2D array representing the board.
        Game game;
        game.itsBoard = {cb(size), size};

        // Initialize the board.
        resetBoard(game.itsBoard.itsCells, size);

        // Place a fortress at the upper-right corner and a castle at the lower-left corner.
        game.itsBoard.itsCells[0][size - 1].itsCellType = FORTRESS;
        game.itsBoard.itsCells[size - 1][0].itsCellType = CASTLE;

        // Define start and end positions for piece movements.
        Position pos[5] = {{0, 0}, {0, size - 1}, {size - 1, size - 1}, {size - 1, 0}, {0, 0}};

        // Define piece types to test: SWORD, SHIELD, and KING.
        PieceType piecesTypes[3] = {SWORD, SHIELD, KING};

        // Iterate through piece types.
        for (PieceType itsPieceType : piecesTypes)
        {
            // Display the current piece type being tested.
            if (itsPieceType == SWORD)
                cout << "SWORD movements :" << endl;
            else if (itsPieceType == SHIELD)
                cout << "SHIELD movements :" << endl;
            else
                cout << "KING movements :" << endl;

            // Place the piece on the board.
            game.itsBoard.itsCells[0][0].itsPieceType = itsPieceType;
            //displayBoard(game.itsBoard);

            // Iterate through possible movements (from 0 to 3).
            for (int i = 0; i < 4; ++i)
            {
                // Perform the piece movement.
                movePiece(game, {pos[i], pos[i + 1]});
                //displayBoard(game.itsBoard);

                // Check if the piece has been moved correctly.
                if (game.itsBoard.itsCells[pos[i].itsRow][pos[i].itsCol].itsPieceType == NONE &&
                    game.itsBoard.itsCells[pos[i + 1].itsRow][pos[i + 1].itsCol].itsPieceType == itsPieceType)
                {
                    // Display a pass message.
                    cout << "PASS \t: " << (char)(pos[i].itsRow + 'A') << pos[i].itsCol + 1 << " to "
                         << (char)(pos[i + 1].itsRow + 'A') << pos[i + 1].itsCol + 1 << endl << endl;
                    pass++;
                }
                else
                {
                    // Display a fail message.
                    cout << "FAIL! \t: " << (char)(pos[i].itsRow + 'A') << pos[i].itsCol + 1 << " to "
                         << (char)(pos[i + 1].itsRow + 'A') << pos[i + 1].itsCol + 1 << endl << endl;
                    failed++;
                }
            }
        }
    db(game.itsBoard.itsCells,size);
    }

    // Display the total pass and failed counts.
    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;

    // Display the end of the movePiece testing.
    cout << "********* Finished testing of movePiece *********" << endl << endl;
}

/**
 * @brief Test the capturePieces function with various scenarios.
 *
 * This function tests the capturePieces function by setting up different scenarios
 * to capture pieces on the board. It covers scenarios involving attacks and defenses,
 * capturing pieces with various configurations, and checking the results.
 */
void test_capturePieces()
{
    cout << "********* Start testing of capturePieces *********" << endl;
    int pass = 0;
    int failed = 0;

    Game game;
    game.itsBoard.itsCells = cb(LITTLE);

    // Attack capture scenario
    game.itsCurrentPlayer = &game.itsPlayer1;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[4][5].itsPieceType = SHIELD;
    game.itsBoard.itsCells[6][5].itsPieceType = SHIELD;
    game.itsBoard.itsCells[5][6].itsPieceType = SHIELD;
    game.itsBoard.itsCells[3][5].itsPieceType = SWORD;
    game.itsBoard.itsCells[7][5].itsCellType = FORTRESS;
    game.itsBoard.itsCells[5][7].itsCellType = CASTLE;

    game.itsBoard.itsCells[5][2].itsPieceType = SWORD;

    //displayBoard(game.itsBoard);
    cout << "ATTACK move SWORD in F3 to F6" << endl;
    movePiece(game,{{5,2},{5,5}});
    capturePieces(game, {{5,2},{5,5}});
    //displayBoard(game.itsBoard);

    // Verify captured pieces
    if(game.itsBoard.itsCells[4][5].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SHIELD in E6 was captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in E6 was not captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[6][5].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SHIELD in G6 was captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in G6 was not captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[5][6].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SHIELD in F7 was captured" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in F7 was not captured" << endl << endl;
        failed++;
    }

    // Defense capture scenario with SHIELD
    game.itsCurrentPlayer = &game.itsPlayer2;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[4][5].itsPieceType = SWORD;
    game.itsBoard.itsCells[6][5].itsPieceType = SWORD;
    game.itsBoard.itsCells[5][6].itsPieceType = SWORD;
    game.itsBoard.itsCells[7][5].itsPieceType = SHIELD;
    game.itsBoard.itsCells[5][7].itsCellType = FORTRESS;
    game.itsBoard.itsCells[3][5].itsCellType = CASTLE;

    game.itsBoard.itsCells[5][2].itsPieceType = SHIELD;
    game.itsBoard.itsCells[5][0].itsPieceType = KING;
    game.itsBoard.itsCells[5][1].itsPieceType = SWORD;


    //displayBoard(game.itsBoard);
    cout << "DEFENSE move SHIELD in F3 to F6" << endl;
    movePiece(game,{{5,2},{5,5}});
    capturePieces(game,{{5,2},{5,5}});
    //displayBoard(game.itsBoard);

    // Verify captured pieces
    if(game.itsBoard.itsCells[4][5].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SWORD in E6 was captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in E6 was not captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[6][5].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SWORD in G6 was captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in G6 was not captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[5][6].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SWORD in F7 was captured" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in F7 was not captured" << endl << endl;
        failed++;
    }

    cout << "DEFENSE move SHIELD in F6 to F3" << endl;
    movePiece(game,{{5,5},{5,2}});
    capturePieces(game,{{5,5},{5,2}});
    //displayBoard(game.itsBoard);

    // Verify captured pieces
    if(game.itsBoard.itsCells[5][1].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SWORD in F2 was captured" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in F2 was not captured" << endl << endl;
        failed++;
    }

    // Defense capture scenario with KING
    game.itsCurrentPlayer = &game.itsPlayer2;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[4][5].itsPieceType = SWORD;
    game.itsBoard.itsCells[6][5].itsPieceType = SWORD;
    game.itsBoard.itsCells[5][6].itsPieceType = SWORD;
    game.itsBoard.itsCells[3][5].itsPieceType = SHIELD;
    game.itsBoard.itsCells[7][5].itsCellType = FORTRESS;
    game.itsBoard.itsCells[5][7].itsCellType = CASTLE;

    game.itsBoard.itsCells[5][2].itsPieceType = KING;

    //displayBoard(game.itsBoard);
    cout << "DEFENSE move KING in F3 to F6" << endl;
    movePiece(game,{{5,2},{5,5}});
    capturePieces(game,{{5,2},{5,5}});
    //displayBoard(game.itsBoard);

    // Verify captured pieces
    if(game.itsBoard.itsCells[4][5].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SWORD in E6 was captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in E6 was not captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[6][5].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SWORD in G6 was captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in G6 was not captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[5][6].itsPieceType == NONE)
    {
        cout << "PASS \t: " << "SWORD in F7 was captured" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in F7 was not captured" << endl << endl;
        failed++;
    }

    // Attack capture scenario with no pieces captured
    game.itsCurrentPlayer = &game.itsPlayer1;
    resetBoard(game.itsBoard.itsCells, LITTLE);
    game.itsBoard.itsCells[4][5].itsPieceType = SHIELD;
    game.itsBoard.itsCells[3][5].itsPieceType = KING;
    game.itsBoard.itsCells[3][5].itsCellType = CASTLE;

    game.itsBoard.itsCells[6][5].itsPieceType = SHIELD;
    game.itsBoard.itsCells[5][6].itsPieceType = SWORD;

    game.itsBoard.itsCells[5][1].itsPieceType = SWORD;

    game.itsBoard.itsCells[5][0].itsPieceType = SHIELD;

    game.itsBoard.itsCells[4][1].itsPieceType = SHIELD;
    game.itsBoard.itsCells[3][1].itsPieceType = SHIELD;

    game.itsBoard.itsCells[6][1].itsPieceType = SHIELD;
    game.itsBoard.itsCells[7][1].itsPieceType = KING;

    //displayBoard(game.itsBoard);
    cout << "ATTACK move SWORD in F2 to F6" << endl;
    movePiece(game,{{5,1},{5,5}});
    capturePieces(game,{{5,1},{5,5}});
    //displayBoard(game.itsBoard);

    // Verify no pieces captured
    if(game.itsBoard.itsCells[4][5].itsPieceType == SHIELD)
    {
        cout << "PASS \t: " << "SHIELD in E6 was not captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in E6 was captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[6][5].itsPieceType == SHIELD)
    {
        cout << "PASS \t: " << "SHIELD in G6 was not captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in G6 was captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[5][6].itsPieceType == SWORD)
    {
        cout << "PASS \t: " << "SWORD in F7 was not captured" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in F7 was captured" << endl << endl;
        failed++;
    }

    cout << "ATTACK move SWORD in F6 to F1" << endl;
    movePiece(game,{{5,5},{5,1}});
    capturePieces(game,{{5,5},{5,1}});
    //displayBoard(game.itsBoard);

    // Verify no pieces captured
    if(game.itsBoard.itsCells[5][0].itsPieceType == SHIELD)
    {
        cout << "PASS \t: " << "SHIELD in F1 was not captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in F1 was captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[4][1].itsPieceType == SHIELD)
    {
        cout << "PASS \t: " << "SHIELD in E2 was not captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in E2 was captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[6][1].itsPieceType == SHIELD)
    {
        cout << "PASS \t: " << "SHIELD in G2 was not captured" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in G2 was captured" << endl << endl;
        failed++;
    }

    // Defense capture scenario with no pieces captured
    game.itsCurrentPlayer = &game.itsPlayer2;
    resetBoard(game.itsBoard.itsCells, LITTLE);

    game.itsBoard.itsCells[6][5].itsPieceType = SHIELD;
    game.itsBoard.itsCells[5][6].itsPieceType = SWORD;

    game.itsBoard.itsCells[5][1].itsPieceType = SHIELD;

    game.itsBoard.itsCells[5][0].itsPieceType = SWORD;

    game.itsBoard.itsCells[4][1].itsPieceType = SWORD;
    game.itsBoard.itsCells[3][1].itsPieceType = SWORD;

    //displayBoard(game.itsBoard);
    cout << "DEFENSE move SHIELD in F2 to F6" << endl;
    movePiece(game,{{5,1},{5,5}});
    capturePieces(game,{{5,1},{5,5}});
    //displayBoard(game.itsBoard);

    // Verify no pieces captured
    if(game.itsBoard.itsCells[6][5].itsPieceType == SHIELD)
    {
        cout << "PASS \t: " << "SHIELD in G6 was not captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SHIELD in G6 was captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[5][6].itsPieceType == SWORD)
    {
        cout << "PASS \t: " << "SWORD in F7 was not captured" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in F7 was captured" << endl << endl;
        failed++;
    }

    cout << "DEFENSE move SHIELD in F6 to F1" << endl;
    movePiece(game,{{5,5},{5,1}});
    capturePieces(game,{{5,5},{5,1}});
    //displayBoard(game.itsBoard);

    // Verify no pieces captured
    if(game.itsBoard.itsCells[5][0].itsPieceType == SWORD)
    {
        cout << "PASS \t: " << "SWORD in F1 was not captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in F1 was captured" << endl;
        failed++;
    }
    if(game.itsBoard.itsCells[4][1].itsPieceType == SWORD)
    {
        cout << "PASS \t: " << "SWORD in E2 was not captured" << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "SWORD in E2 was captured" << endl;
        failed++;
    }

    db(game.itsBoard.itsCells,LITTLE);

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of movePiece *********" << endl << endl;
}


/**
 * @brief Tests the switchCurrentPlayer function.
 *
 * This function tests if the switchCurrentPlayer function correctly switches
 * between players in a game.
 */
void test_switchCurrentPlayer() {
    cout << "********* Start testing of switchCurrentPlayer *********" << endl;
    int pass = 0;
    int failed = 0;

    Game game;
    game.itsCurrentPlayer = &game.itsPlayer1;

    // Test: Switch from Player 1 to Player 2
    switchCurrentPlayer(game);
    if (game.itsCurrentPlayer == &game.itsPlayer2) {
        cout << "PASS \t: Switched from Player 1 to Player 2" << endl;
        pass++;
    } else {
        cout << "FAIL! \t: Did not switch from Player 1 to Player 2" << endl;
        failed++;
    }

    // Test: Switch from Player 2 back to Player 1
    switchCurrentPlayer(game);
    if (game.itsCurrentPlayer == &game.itsPlayer1) {
        cout << "PASS \t: Switched from Player 2 back to Player 1" << endl;
        pass++;
    } else {
        cout << "FAIL! \t: Did not switch from Player 2 back to Player 1" << endl;
        failed++;
    }

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of switchCurrentPlayer *********" << endl;
}


/**
 * @brief Test function for isSwordLeft.
 *
 * This function tests the behavior of the isSwordLeft function to determine if swords are present on the board.
 * It performs two test cases:
 * 1. Ensures that isSwordLeft correctly detects the absence of swords.
 * 2. Ensures that isSwordLeft correctly detects the presence of swords.
 */
void test_isSwordLeft()
{
    cout << "********* Start testing of isSwordLeft *********" << endl;
    int pass = 0;
    int failed = 0;

    BoardSize size = LITTLE;
    Cell** b = cb(size);

    // Reset the game board
    resetBoard(b, size);

    // Place a SHIELD piece and define a CASTLE and FORTRESS
    b[1][1].itsPieceType = SHIELD;
    b[8][8].itsCellType = CASTLE;
    b[size - 1][size - 1].itsCellType = FORTRESS;

    //displayBoard({b, size});

    // Test case 1: No swords present on the board
    if (!isSwordLeft({b, size}))
    {
        cout << "PASS \t: " << "No more sword !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual Staying swords !" << "\n\texpected No more sword !" << endl;
        failed++;
    }

    // Add a SWORD piece
    b[8][4].itsPieceType = SWORD;

    //displayBoard({b, size});

    // Test case 2: Swords are present on the board
    if (isSwordLeft({b, size}))
    {
        cout << "PASS \t: " << "Staying swords !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual No more sword !" << "\n\texpected Staying swords !" << endl;
        failed++;
    }

    db(b,size);

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of isSwordLeft *********" << endl << endl;
}

/**
 * @brief Test function for getKingPosition.
 *
 * This function tests the behavior of the getKingPosition function to retrieve the position of the king on the board.
 * It performs multiple test cases for different board sizes and positions of the king.
 */
void test_getKingPosition()
{
    cout << "********* Start testing of getKingPosition *********" << endl;
    int pass = 0;
    int failed = 0;

    // Define board sizes to test
    BoardSize sizes[2] = {LITTLE, BIG};

    for (BoardSize size : sizes)
    {
        if (size == LITTLE) cout << "LITTLE board :" << endl;
        else cout << "BIG board :" << endl;

        Board b = {nullptr, size};
        b.itsCells = cb(size);

        // Positions to compare the king's position with
        Position posToCompares[] = {
            { (size - 1) / 2, (size - 1) / 2 },  // Middle of the board
            {0, 0},                              // Top-left corner
            {size - 1, 7},                       // Rightmost column, bottom row
            {4, 4}                               // Custom position
        };

        // Initialize the board and test for each position
        initializeBoard(b);
        for(Position posToCompare : posToCompares)
        {
            b.itsCells[posToCompare.itsRow][posToCompare.itsCol].itsPieceType = KING;
            //displayBoard(b);

            // Get the position of the king
            Position posToTest = getKingPosition(b);

            // Compare the actual position with the expected position
            if (posToTest.itsRow == posToCompare.itsRow && posToTest.itsCol == posToCompare.itsCol)
            {
                cout << "PASS \t: " << (char)(posToCompare.itsRow+'A') << posToCompare.itsCol+1 << endl << endl;
                pass++;
            }
            else
            {
                cout << "FAIL! \t: " << "\n\tActual " << (char)(posToTest.itsRow+'A') << posToTest.itsCol+1
                     << "\n\texpected " << (char)(posToCompare.itsRow+'A') << posToCompare.itsCol+1 << endl << endl;
                failed++;
            }

            // Reset the board for the next test case
            b.itsCells[posToCompare.itsRow][posToCompare.itsCol].itsPieceType = NONE;
        }
    db(b.itsCells,size);
    }

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of getKingPosition *********" << endl << endl;
}

/**
 * @brief Test function for isKingEscaped.
 *
 * This function tests the behavior of the isKingEscaped function to check if the king has escaped from the board.
 * It performs multiple test cases for different board sizes and king positions.
 */
void test_isKingEscaped()
{
    cout << "********* Start testing of isKingEscaped *********" << endl;
    int pass = 0;
    int failed = 0;

    // Define board sizes to test
    BoardSize sizes[2] = {LITTLE, BIG};

    for (BoardSize size : sizes)
    {
        if (size == LITTLE) cout << "LITTLE board :" << endl;
        else cout << "BIG board :" << endl;

        Board b = {nullptr, size};
        b.itsCells = cb(size);

        // Initialize the board
        initializeBoard(b);

        // Positions where the king has not escaped
        Position posKingNotEscaped[] = {
            {(size-1)/2, (size-1)/2},  // Middle of the board
            {3, 3}                     // Custom position
        };

        for(Position pos : posKingNotEscaped)
        {
            b.itsCells[pos.itsRow][pos.itsCol].itsPieceType = KING;
            //displayBoard(b);

            // Check if the king has not escaped
            if(!isKingEscaped(b))
            {
                cout << "PASS \t: " << "King is not escaped !" << endl << endl;
                pass++;
            }
            else
            {
                cout << "FAIL! \t: " << "\n\tActual King is escaped !" << "\n\texpected King is not escaped !" << endl;
                failed++;
            }

            // Reset the board for the next test case
            b.itsCells[pos.itsRow][pos.itsCol].itsPieceType = NONE;
        }

        // Positions where the king has escaped
        Position posKingEscaped[] = {
            {0, 0},                 // Top-left corner
            {size-1, 0},            // Top-right corner
            {size-1, size-1},       // Bottom-right corner
            {0, size-1}             // Bottom-left corner
        };

        for(Position pos : posKingEscaped)
        {
            b.itsCells[pos.itsRow][pos.itsCol].itsPieceType = KING;
            //displayBoard(b);

            // Check if the king has escaped
            if(isKingEscaped(b))
            {
                cout << "PASS \t: " << "King is escaped !" << endl << endl;
                pass++;
            }
            else
            {
                cout << "FAIL! \t: " << "\n\tActual King is not escaped !" << "\n\texpected King is escaped !" << endl;
                failed++;
            }

            // Reset the board for the next test case
            b.itsCells[pos.itsRow][pos.itsCol].itsPieceType = NONE;
        }
        db(b.itsCells,size);
    }

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of isKingEscaped *********" << endl << endl;
}

/**
 * @brief Test function for isKingCaptured.
 *
 * This function tests the behavior of the isKingCaptured function to check if the king is captured by attackers.
 * It performs multiple test cases for different scenarios on a specified board size (LITTLE).
 */
void test_isKingCaptured()
{
    cout << "********* Start testing of isKingCaptured *********" << endl;
    int pass = 0;
    int failed = 0;

    // Specify the board size for testing
    BoardSize size= LITTLE;
    Board b = {nullptr, size};
    b.itsCells = cb(size);

    // Scenario: King captured by 4 attackers
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SWORD;
    b.itsCells[3][2].itsPieceType = SWORD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }

    // Scenario: King captured by 3 attackers and the border
    resetBoard(b.itsCells,size);
    b.itsCells[0][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SWORD;
    b.itsCells[0][1].itsPieceType = SWORD;
    b.itsCells[0][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }


    // Scenario: King captured by 3 attackers and the castle
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SWORD;
    b.itsCells[3][2].itsPieceType = SWORD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsCellType = CASTLE;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }

    // Scenario: King captured by 2 attackers, a border and a fortress
    resetBoard(b.itsCells,size);
    b.itsCells[size-1][2].itsPieceType = KING;
    b.itsCells[size-2][2].itsPieceType = SWORD;
    b.itsCells[size-1][1].itsCellType = FORTRESS;
    b.itsCells[size-1][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }

    // Scenario: King not captured if there is a free cell
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[3][2].itsPieceType = SWORD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is not captured
    if(!isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is not captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king captured ! " << "\n\texpected king is not captured !" << endl;
        failed++;
    }

    // Scenario: King not captured if there is a defender
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SWORD;
    b.itsCells[3][2].itsPieceType = SHIELD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is not captured
    if(!isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is not captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king captured ! " << "\n\texpected king is not captured !" << endl;
        failed++;
    }

    db(b.itsCells,size);

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of isKingCaptured *********" << endl << endl;
}

/**
 * @brief Test function for isKingCapturedV2.
 *
 * This function tests the behavior of the isKingCapturedV2 function to check if the king is captured by attackers
 * with advanced scenarios. It performs multiple test cases for different scenarios on a specified board size (LITTLE).
 */
void test_isKingCapturedV2()
{
    cout << "********* Start testing of isKingCapturedV2 *********" << endl;
    int pass = 0;
    int failed = 0;

    // Specify the board size for testing
    BoardSize size= LITTLE;
    Board b = {nullptr, size};
    b.itsCells = cb(size);

    // Scenario: King captured by 4 attackers
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SWORD;
    b.itsCells[3][2].itsPieceType = SWORD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }

    // Scenario: King captured by 3 attackers and the border
    resetBoard(b.itsCells,size);
    b.itsCells[0][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SWORD;
    b.itsCells[0][1].itsPieceType = SWORD;
    b.itsCells[0][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }


    // Scenario: King captured by 3 attackers and the castle
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SWORD;
    b.itsCells[3][2].itsPieceType = SWORD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsCellType = CASTLE;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }

    // Scenario: King captured by 2 attackers, a border and a fortress
    resetBoard(b.itsCells,size);
    b.itsCells[size-1][2].itsPieceType = KING;
    b.itsCells[size-2][2].itsPieceType = SWORD;
    b.itsCells[size-1][1].itsCellType = FORTRESS;
    b.itsCells[size-1][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }

    // Scenario: King not captured if there is a free cell
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[3][2].itsPieceType = SWORD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is not captured
    if(!isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is not captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king captured ! " << "\n\texpected king is not captured !" << endl;
        failed++;
    }

    // Scenario: King not captured if there is a defender
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SWORD;
    b.itsCells[3][2].itsPieceType = SHIELD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is not captured
    if(!isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is not captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king captured ! " << "\n\texpected king is not captured !" << endl;
        failed++;
    }

    // Scenario: Not captured if closed by a combination of attackers, a fortress, and a FORTRESS but with an empty space
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SHIELD;
    b.itsCells[0][2].itsPieceType = SHIELD;
    b.itsCells[0][1].itsPieceType = SHIELD;
    b.itsCells[1][1].itsPieceType = SWORD;
    b.itsCells[0][3].itsPieceType = SWORD;
    b.itsCells[0][0].itsCellType = FORTRESS;
    b.itsCells[3][2].itsPieceType = SWORD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsPieceType = SHIELD;
    b.itsCells[3][3].itsPieceType = SWORD;
    b.itsCells[1][3].itsPieceType = SWORD;
    b.itsCells[2][4].itsPieceType = SHIELD;
    b.itsCells[3][4].itsPieceType = SHIELD;
    b.itsCells[4][4].itsCellType = CASTLE;
    b.itsCells[1][4].itsPieceType = SWORD;
    b.itsCells[2][5].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is not captured
    if(!isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is not captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is captured ! " << "\n\texpected king is not captured !" << endl;
        failed++;
    }

    // Scenario: Captured if closed by a combination of attackers, a fortress, and a FORTRESS
    resetBoard(b.itsCells,size);
    b.itsCells[2][2].itsPieceType = KING;
    b.itsCells[1][2].itsPieceType = SHIELD;
    b.itsCells[0][2].itsPieceType = SHIELD;
    b.itsCells[0][1].itsPieceType = SHIELD;
    b.itsCells[1][1].itsPieceType = SWORD;
    b.itsCells[0][3].itsPieceType = SWORD;
    b.itsCells[0][0].itsCellType = FORTRESS;
    b.itsCells[3][2].itsPieceType = SWORD;
    b.itsCells[2][1].itsPieceType = SWORD;
    b.itsCells[2][3].itsPieceType = SHIELD;
    b.itsCells[3][3].itsPieceType = SWORD;
    b.itsCells[1][3].itsPieceType = SWORD;
    b.itsCells[2][4].itsPieceType = SHIELD;
    b.itsCells[3][4].itsPieceType = SHIELD;
    b.itsCells[3][5].itsPieceType = SWORD;
    b.itsCells[4][4].itsCellType = CASTLE;
    b.itsCells[1][4].itsPieceType = SWORD;
    b.itsCells[2][5].itsPieceType = SWORD;

    //displayBoard(b);

    // Check if the king is captured
    if(isKingCaptured(b))
    {
        cout << "PASS \t: " << "king is captured !" << endl << endl;
        pass++;
    }
    else
    {
        cout << "FAIL! \t: " << "\n\tActual king is not captured ! " << "\n\texpected king is captured !" << endl;
        failed++;
    }

    db(b.itsCells,size);

    cout << "Totals: " << pass << " passed, " << failed << " failed" << endl;
    cout << "********* Finished testing of isKingCapturedV2 *********" << endl << endl;
}



void resetBoard(Cell**& aBoard, const BoardSize& aBoardSize)
{
    // Iterate over each row and column of the board
    for (int i = 0; i < aBoardSize; ++i) {
        for (int j = 0; j < aBoardSize; ++j) {
            // Set the cell to a normal state with no piece
            aBoard[i][j] = {NORMAL, NONE};
        }
    }
}

Cell** cb(const BoardSize& aBoardSize) {
    Cell** board = new Cell*[aBoardSize];
    for (int i = 0; i < aBoardSize; ++i) {
        board[i] = new Cell[aBoardSize];
    }
    return board;
}

void db(Cell**& aBoard,const BoardSize& aBoardSize) {
    for (int i = 0; i < aBoardSize; ++i) {
        delete[] aBoard[i];
    }
    delete[] aBoard;
    aBoard = nullptr;
}
