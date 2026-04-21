#ifndef PROPERTY_H
#define PROPERTY_H

#include "Tile.h"

class Player;

class Property : public Tile {
private:
    double price;
    double rent;
    Player* owner;

public:
    Property(std::string name, int pos, double p, double r);

    virtual void onLand(Player* player) override;

    double getPrice() const;
    double getRent() const;
    Player* getOwner() const;

    void setOwner(Player* player);
};

#endif
