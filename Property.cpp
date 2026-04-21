#include "Property.h"
#include "Player.h"
#include <iostream>

// 建構子
Property::Property(std::string name, int pos, double p, double r)
    : Tile(name, pos), price(p), rent(r), owner(nullptr) {
}

void Property::onLand(Player* player) {
    if (player == nullptr) return;

    // 顯示玩家抵達哪一格
    std::cout << "\n>>> [" << player->getName() << "] landed on " << getName() << std::endl;

    if (owner == nullptr) {
        // 情況 1：無人擁有 (Unowned)
        std::cout << "Price: $" << price << " | Your Balance: $" << player->getMoney() << std::endl;
        std::cout << "Would you like to buy it? (y/n): ";

        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (player->payMoney(price)) {
                owner = player;
                player->buyProperty(this);
                std::cout << "Success! You now own this land." << std::endl;
            }
            else {
                std::cout << "Not enough money!" << std::endl;
            }
        }
        else {
            std::cout << "You skipped this property." << std::endl;
        }
    }
    else if (owner != player) {
        // 情況 2：別人的地 (Owned by others)
        std::cout << "Owned by: [" << owner->getName() << "]" << std::endl;
        std::cout << "You must pay rent: $" << rent << std::endl;

        if (player->payMoney(rent)) {
            owner->addMoney(rent);
            std::cout << "Rent paid. Current balance: $" << player->getMoney() << std::endl;
        }
        else {
            std::cout << "BANKRUPT! You cannot afford the rent!" << std::endl;
            owner->addMoney(player->getMoney());
        }
    }
    else {
        // 情況 3：自己的地 (Owned by self)
        std::cout << "Welcome home! This is your property." << std::endl;
    }
}

// 實作其餘的 Getter/Setter
double Property::getPrice() const { return price; }
double Property::getRent() const { return rent; }
Player* Property::getOwner() const { return owner; }
void Property::setOwner(Player* p) { owner = p; }