#ifndef MOVABLE_H
#define MOVABLE_H
#include "Position.h"
#include "Enums.h"
#include <iostream>
#include <vector>

class Movable{
    Position pos;
public:
    Movable(const Position& position):pos(position){
    }

    void move(Direction::Direction dir){
        pos += Direction::Coord[dir];
    }

    const Position& getPosition() const{
        return pos;
    }

    void setPosition(const Position& p){
        pos = p;
    }

    void back(Direction::Direction dir){
        dir = reverse(dir);
        move(dir);
    }

    static inline Direction::Direction reverse(Direction::Direction dir){
        switch (dir)
        {
            case Direction::UP:
                return Direction::DOWN;
            case Direction::DOWN:
                return Direction::UP;
            case Direction::LEFT:
                return Direction::RIGHT;
            case Direction::RIGHT:
                return Direction::LEFT;
    
            default:
                return Direction::SITU;
        }
    }
};

class Player:public Movable{
    std::vector<Direction::Direction> record;
    std::vector<bool> pushFlag;
public:
    Player():Movable(Position::of(0,0)){
    }
    Player(const Position& position):Movable(position){
    }

    void move(Direction::Direction dir, bool pushOrNot){
        record.push_back(dir);
        pushFlag.push_back(pushOrNot);
        Movable::move(dir);
    }

    Direction::Direction getPreviousDirection(){
        int size = record.size();
        if(size == 0){
            return Direction::SITU;
        }
        Direction::Direction dir = record[size-1];
        record.pop_back();
        return dir;
    }

    bool getPreviousPushFlag(){
        int size = pushFlag.size();
        if(size == 0){
            return false;
        }
        bool flag = pushFlag[size-1];
        pushFlag.pop_back();
        return flag;
    }

    void clear(){
        record.clear();
        pushFlag.clear();
    }
};

class Box: public Movable{
    bool onTarget;
public:
    Box(const Position& position):Movable(position),onTarget(false){
    }

    void moveToTile(Tiletype::State type){
        onTarget = (type == Tiletype::State::TARGET);
    }

    bool getOnTarget() const{
        return onTarget;
    }
};

#endif //MOVABLE_H
