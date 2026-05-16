#ifndef MAP_H
#define MAP_H
#include <string>

class Tile;
class Player;

class Map {
private:
    static const int MAP_SIZE = 40;
    Tile* tiles[MAP_SIZE];
    int totalTiles;

public:
    Map();
    ~Map();

    void initializeMap();

    Tile* getTile(int position) const;

    int calculateNewPosition(int currentPos, int steps) const;

    int getMapSize() const;

    bool isProperty(int position) const;
};

#endif