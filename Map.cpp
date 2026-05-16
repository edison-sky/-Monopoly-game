#include "Map.h"
#include "Property.h"

Map::Map() : totalTiles(40) {
    initializeMap();
}

Map::~Map() {
    for (int i = 0; i < MAP_SIZE; i++) delete tiles[i];
}

void Map::initializeMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        tiles[i] = new Property("land" + std::to_string(i), i, 200.0 + i * 10, 100.0 + i * 5);
    }
}

Tile* Map::getTile(int position) const { return tiles[position % MAP_SIZE]; }
int Map::getMapSize() const { return MAP_SIZE; }