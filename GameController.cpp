#include "GameController.h"
#include "Property.h" 
#include "Tile.h"
#include "Player.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

GameController::GameController(int playerCount) : totalPlayers(playerCount), currentPlayerIndex(0) {
    for (int i = 0; i < 3; i++) {
        players[i] = new Player("Player " + std::to_string(i + 1), i, 1500.0);
    }
}

GameController::~GameController() {
    for (int i = 0; i < 3; i++) {
        if (players[i] != nullptr) {
            delete players[i];
        }
    }
}

void GameController::playRound() {
    Player* p = players[currentPlayerIndex];

    if (p->checkBankrupt()) {
        nextTurn();
        return;
    }

    cout << "\n--- Current Turn: [" << p->getName() << "] (Balance: $" << p->getMoney() << ") ---" << std::endl;
    cout << "Press Enter to roll dice...";

    std::cin.clear(); 
    std::cin.ignore(100, '\n'); 

    int steps = rollDice();
    p->move(steps, gameMap.getMapSize());

    Tile* t = gameMap.getTile(p->getPosition());
    t->onLand(p);

    nextTurn();
}

int GameController::rollDice() {
    int d = (rand() % 6) + 1;
    std::cout << ">> Rolled: " << d << "!" << std::endl;
    return d;
}

void GameController::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % 3;
}

bool GameController::isGameOver() {
    int activeCount = 0;
    for (int i = 0; i < 3; i++) {
        if (!players[i]->checkBankrupt()) {
            activeCount++;
        }
    }

    return activeCount <= 1;
}

void GameController::printWinner() {
    int winnerID = -1;
    int maxLand = -1;
    double maxMoney = -1.0;

    cout << "\n================================" << endl;
    cout << "          GAME OVER             " << endl;
    cout << "================================" << endl;

    for (int i = 0; i < 3; i++) {
        int landCount = players[i]->getOwnedCount();
        double currentMoney = players[i]->getMoney();

        cout << "Player " << (i + 1) << ": ";
        if (players[i]->checkBankrupt()) {
            cout << landCount << " lands, $" << currentMoney << " [BANKRUPT]" << endl;
        }
        else {
            cout << landCount << " lands, $" << currentMoney << " [ALIVE]" << endl;
        }

        if (players[i]->checkBankrupt()) {
            continue;
        }

        if (landCount > maxLand) {
            maxLand = landCount;
            maxMoney = currentMoney;
            winnerID = i + 1;
        }
        else if (landCount == maxLand) {
            if (currentMoney > maxMoney) {
                maxMoney = currentMoney;
                winnerID = i + 1;
            }
        }
    }

    cout << "--------------------------------" << endl;

    if (winnerID != -1) {
        cout << " WINNER IS PLAYER NO. " << winnerID << "!" << endl;
    }
    else {
        cout << " NO WINNER FOUND! " << endl;
    }
    cout << "================================" << endl;
}
