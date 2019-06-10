#include "Session.h"
#include <iostream>

static inline bool isWrongPlace(Tiletype::State s){
    return (s == Tiletype::State::FLOOR_OUT_SIDE)||(s == Tiletype::State::WALL);
}

static inline bool isBox(Tiletype::State s){
    return (s == Tiletype::State::BOX)||(s == Tiletype::State::BOX_ON_TARGET);
}

static inline bool isFloor(Tiletype::State s){
    return (s == Tiletype::State::FLOOR)||(s == Tiletype::State::TARGET);
}

bool RULE::isWin(const Map& m){
    const std::vector<Box> boxs = m.getBoxs();
    std::vector<Box>::const_iterator iter;
    for(iter = boxs.cbegin();iter != boxs.cend(); iter++){
        if(!iter->getOnTarget()){
            return false;
        }
    }
	return true;
}

bool RULE::isRightMove(const Map& m, Direction::Direction dir){
    Position shadow = m.getPlayerPosition();
    shadow += Direction::Coord[dir];
	Tiletype::State state = m.getStateOf(shadow);
    if(isFloor(state)){
        return true;
    }
    else if(isWrongPlace(state)){
        return false;
    }
    else if(isBox(state)){
        shadow += Direction::Coord[dir];
        state = m.getStateOf(shadow);
        if(isWrongPlace(state)||isBox(state)){
            return false;
        }
        else if(isFloor(state)){
            return true;
        }
    }
    return false;
}

Session::Session(int width,int height,int l,const std::string& s):map(width,height),level(l){
    map.setStep(0);
	map.setPush(0);
    isFinish = false;
    map.initMap(s);
    mapBuffer = s;
}

Session::~Session(){
}

void Session::move(Direction::Direction dir){
    bool flag = RULE::isRightMove(map,dir);
    if(!flag||isFinish){
        return;
    }

    map.move(dir);
    map.increaseStep();

    flag = RULE::isWin(map);
    if(flag){
        finish();
    }
}

const Map& Session::getMap() const{
    return map;
}

void Session::finish(){
    isFinish = true;
}

bool Session::isFinished() const{
    return isFinish;
}

void Session::backToPreviousPlace(){
	if (map.getStep() > 0)
		map.decreaseStep();
    map.back();
}

void Session::restart(){
	map.setStep(0);
	map.setPush(0);
    map.initMap(mapBuffer);
}
