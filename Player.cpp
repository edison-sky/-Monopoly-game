#include "Player.h"
#include "Property.h"

Player::Player(std::string n, int playerID, double startingMoney)
    : name(n), id(playerID), money(startingMoney), currentPosition(0),
    isBankrupt(false), propertyCount(0) {
    for (int i = 0; i < 40; i++) ownedProperties[i] = nullptr;
}

Player::~Player() {}

std::string Player::getName() const { return name; }
int Player::getMoney() const { return (int)money; }
int Player::getPosition() const { return currentPosition; }
bool Player::checkBankrupt() const { return isBankrupt; }


void Player::move(int steps, int boardSize) {
    currentPosition = (currentPosition + steps) % boardSize;
}

void Player::addMoney(double amount) { money += amount; }

bool Player::payMoney(double amount) {
    if (money < amount) {
        isBankrupt = true;
        return false;
    }
    money -= amount;
    return true;
}

void Player::buyProperty(Property* prop) {
    if (propertyCount < 40) {
        ownedProperties[propertyCount++] = prop;
    }
}

void Player::setBankrupt(bool status) { isBankrupt = status; }

int Player::getOwnedCount() const {
    return propertyCount;
}

