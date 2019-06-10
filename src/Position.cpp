#include "Position.h"
Position::Position():x(0),y(0){}
Position::Position(int i,int j):x(i),y(j){}
Position::Position(const Position& pos){
    x = pos.x;
    y = pos.y;
}
Position::~Position(){
}

Position& Position::operator=(const Position& pos){
    x = pos.x;
    y = pos.y;
    return *this;
}

Position& Position::operator+=(const Position& pos){
    x += pos.x;
    y += pos.y;
    return *this;
}

bool Position::operator==(const Position& pos) const{
    return (x == pos.x)&&(y == pos.y);
}

bool Position::operator<(const Position& pos) const{
    if(x < pos.x){
        return true;
    }
    else if(x == pos.x){
        if(y < pos.y){
            return true;
        }
    }
    return false;
}

int Position::getX() const{
    return x;
}

int Position::getY() const{
    return y;
}

void Position::setX(int xx){
    x = xx;
}

void Position::setY(int yy){
    y = yy;
}

const Position Position::of(int x,int y){
    return Position(x,y);
}

Position Direction::Coord[] = {
    Position(0,-1),
    Position(0,1),
    Position(-1,0),
    Position(1,0),
    Position(0,0) // Current
};

const Position Direction::OUT_OF_RANGE = Position(-1,-1);
