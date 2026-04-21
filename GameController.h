#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Player.h"
#include "Map.h"

class GameController {
private:
    Player* players[3];
    Map gameMap;
    int currentPlayerIndex;
    int totalPlayers;

public:
    GameController(int playerCount);
    ~GameController();
    void nextTurn();   
    void playRound();     
    bool isGameOver();    
    void printWinner();
    
    int rollDice();
};

#endif