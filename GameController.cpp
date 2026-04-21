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
        if (players[i] != nullptr) {//如果沒delete,即使解構其被指向的記憶體也還是被鎖著
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

    std::cout << "\n--- Current Turn: [" << p->getName() << "] (Balance: $" << p->getMoney() << ") ---" << std::endl;
    std::cout << "Press Enter to roll dice...";


    std::cin.clear(); // 清除輸入錯誤帶來的卡住
    std::cin.ignore(100, '\n'); //清掉緩衝區的\n

    int steps = rollDice();
    p->move(steps, gameMap.getMapSize());

    // Get the tile object at current position
    Tile* t = gameMap.getTile(p->getPosition());

    // Trigger the landing event (defined in Property or other Tile classes)
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
    // Game ends if only 1 player remains
    return activeCount <= 1;
}

void GameController::printWinner() {
    int winnerID = -1;
    int maxLand = -1;
    double maxMoney = -1.0;

    cout << "\n================================" << endl;
    cout << "          GAME OVER             " << endl;
    cout << "================================" << endl;

    // 遍歷所有玩家來找出贏家
    for (int i = 0; i < 3; i++) {
        // 假設 Player 有 getOwnedCount() 和 getMoney()
        int landCount = players[i]->getOwnedCount();
        double currentMoney = players[i]->getMoney();


        cout << "Player " << (i + 1) << ": " << landCount << " lands, $" << currentMoney << endl;

        // 贏家判斷邏輯：
        // 1. 地產比較多的人贏
        // 2. 如果地產一樣多，錢比較多的人贏
        if (landCount > maxLand) {
            maxLand = landCount;
            maxMoney = currentMoney;
            winnerID = i + 1; // 編號通常從 1 開始
        }
        else if (landCount == maxLand) {
            if (currentMoney > maxMoney) {
                maxMoney = currentMoney;
                winnerID = i + 1;
            }
        }
    }

    cout << "--------------------------------" << endl;
    cout << " WINNER IS PLAYER NO. " << winnerID << "!" << endl;
    cout << "================================" << endl;
}