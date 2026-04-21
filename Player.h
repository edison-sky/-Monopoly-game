#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<string>

class Property;

class Player {
private:
    std::string name;
    int id;
    double money;
    int currentPosition;
    bool isBankrupt;
    bool inJail;
    int jailTurns;

    Property* ownedProperties[40];
    int propertyCount;

public:
    Player(std::string n, int playerID, double startingMoney);
    ~Player();

    std::string getName() const;
    int getMoney() const;
    int getPosition() const;
    bool checkBankrupt() const;
    bool isInJail() const;

    void move(int steps, int boardSize = 40);
    void teleportTo(int position);
    void addMoney(double amount);
    bool payMoney(double amount);

    void buyProperty(Property* prop);
    void sellProperty(Property* prop);

    void goToJail();
    void releaseFromJail();
    void setBankrupt(bool status);

    void addProperty();       // 買地成功時呼叫，讓數量 +1
    int getOwnedCount() const; // 讓 GameController 呼叫，回傳數量
};

#endif
