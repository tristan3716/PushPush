#ifndef TILE_H
#define TILE_H
#include "Enums.h"
#include "Position.h"

class Tile{
    Position pos;
	Tiletype::State type;
    Tiletype::Flag flag;
public:
    Tile();

    Tile(Tiletype::State t);

    Tile(const Tile& tile);

    ~Tile();

    void setPosition(int x, int y);
    void setFlag(Tiletype::Flag f);
	Tiletype::State getState() const;
    Tiletype::State getType() const;
    const Position& getPosition() const;
    Tile& operator=(const Tile& t);
};

#endif //TILE_H
