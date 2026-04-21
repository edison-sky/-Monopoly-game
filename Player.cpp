#include "Player.h"
#include "Property.h"

Player::Player(std::string n, int playerID, double startingMoney)
    : name(n), id(playerID), money(startingMoney), currentPosition(0),
    isBankrupt(false), inJail(false), jailTurns(0), propertyCount(0) {
    for (int i = 0; i < 40; i++) ownedProperties[i] = nullptr;
}

Player::~Player() {}

std::string Player::getName() const { return name; }
int Player::getMoney() const { return (int)money; }//
int Player::getPosition() const { return currentPosition; }
bool Player::checkBankrupt() const { return isBankrupt; }
bool Player::isInJail() const { return inJail; }

void Player::move(int steps, int boardSize) {
    if (inJail) {
        jailTurns--;
        if (jailTurns <= 0) inJail = false;
        return;
    }
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

void Player::goToJail() { inJail = true; jailTurns = 3; }
void Player::releaseFromJail() { inJail = false; }
void Player::setBankrupt(bool status) { isBankrupt = status; }


int Player::getOwnedCount() const {
    return propertyCount;
}

