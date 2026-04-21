#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GameController.h" 

using namespace std;

int main() {

    srand(static_cast<unsigned int>(time(0)));

    cout << "========================================" << endl;
    cout << "      Welcome to C++ OOP Monopoly       " << endl;
    cout << "========================================" << endl;

    GameController game(3);

    while (!game.isGameOver()) {
        game.playRound();
    }
    game.printWinner();
    cout << "\n========================================" << endl;
    cout << "     GAME OVER! Thank you for playing.    " << endl;
    cout << "========================================" << endl;

    return 0;
}