#include "Tile.h"
#include "Player.h"

Tile::Tile(std::string name, int pos) : tileName(name), position(pos) {}

Tile::~Tile() {}

std::string Tile::getName() const { return tileName; }
int Tile::getPosition() const { return position; }