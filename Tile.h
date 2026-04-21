#ifndef TILE_H
#define TILE_H

#include <string>

class Player; 

class Tile {
protected:
    std::string tileName;
    int position;

public:
    Tile(std::string name, int pos);
    virtual ~Tile();

    virtual void onLand(Player* player) = 0;//加了=0 意思.cpp不實做,由子類別實作

    std::string getName() const;
    int getPosition() const;
};

#endif