#include <iostream>

#if defined(_WIN32) and defined(_WIN64)
    #include <windows.h>
#endif

#include "functions.h"
#include "typeDef.h"

using namespace std;

/**
 * @brief main function of the game.
 *
 * This function is used to start the game or the tests or the demonstration by
 * uncommenting the necessary line.
 *
 * @return 0 if the execution worked correctly
 */
int main()
{
    #if defined(_WIN32) and defined(_WIN64)
        SetConsoleOutputCP(CP_UTF8);
    #endif

    /*
     *playGame -> jouer au jeu
     *playTests -> lancer les tests
     *firstDemo -> lancer les demonstrations
    */

    playGame();
    //playTests();
    //firstDemo();

    return 0;
}
