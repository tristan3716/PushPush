#include "Tile.h"
#include <iostream>

Tile::Tile():type(Tiletype::State::FLOOR),flag(Tiletype::Flag::NONE){
    // std::cout<<"call Tile()"<<std::endl;
}

Tile::Tile(Tiletype::State t):type(t),flag(Tiletype::Flag::NONE){
    // std::cout<<"call Tile(TileType t)"<<std::endl;
}

Tile::Tile(const Tile& tile):pos(tile.pos),type(tile.type),flag(tile.flag){
    // std::cout<<"call Tile(const Tile& t)"<<std::endl;
}

Tile::~Tile(){
    /* destructor */
}

void Tile::setPosition(int x, int y){
    pos.setX(x);
    pos.setY(y);
}

void Tile::setFlag(Tiletype::Flag f){
    flag = f;
}

Tiletype::State Tile::getType() const{
    return type;
}

Tiletype::State Tile::getState() const{
	using namespace Tiletype;
    if(flag == Tiletype::Flag::NONE){
        switch (type)
        {
        case State::WALL:
        case State::FLOOR:
        case State::TARGET:
        case State::FLOOR_OUT_SIDE:
            return type;
        default:
            return State::FLOOR;
        }
    }
    else if(flag == Flag::BOX){
        if(type == State::TARGET){
            return State::BOX_ON_TARGET;
        }
        else{
            return State::BOX;
        }
    }
    else if(flag == Flag::PLAYER){
        return State::PLAYER;
    }
    return State::FLOOR_OUT_SIDE;
}

const Position& Tile::getPosition() const{
    return pos;
}

Tile& Tile::operator=(const Tile& t){
    type = t.type;
    flag = t.flag;
    pos = t.pos;
    // std::cout<<"call operator="<<std::endl;
	return *this;
}
