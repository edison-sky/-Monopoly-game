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

    Property* ownedProperties[40];
    int propertyCount;

public:
    Player(std::string n, int playerID, double startingMoney);
    ~Player();

    std::string getName() const;
    int getMoney() const;
    int getPosition() const;
    bool checkBankrupt() const;

    void move(int steps, int boardSize = 40);
    void teleportTo(int position);
    void addMoney(double amount);
    bool payMoney(double amount);

    void buyProperty(Property* prop);
    void sellProperty(Property* prop);

    void setBankrupt(bool status);

    void addProperty();       
    int getOwnedCount() const; 
};

#endif
