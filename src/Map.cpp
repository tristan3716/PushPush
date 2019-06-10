#include "Map.h"
#include "Position.h"
#include <iostream>

static Box& getBox(const Position& p, std::vector<Box>& boxs);

Map::Map(int w, int h)
    :width(w),height(h),player(Position::of(-100,-100)),
    OUT_SIDE_TILE(Tiletype::State::FLOOR_OUT_SIDE),
	step(0), push(0){
}

void Map::setStep(int s){
	step = s;
}
void Map::setPush(int s){
	push = s;
}

void Map::increaseStep(){
	step++;
}
void Map::increasePush(){
	push++;
}

void Map::decreaseStep(){
	step--;
}
void Map::decreasePush(){
	push--;
}

int Map::getStep() const{
	return step;
}
int Map::getPush() const{
	return push;
}

Map::~Map(){
    boxs.clear();
    tileMap.clear();
}

int Map::getWidth() const{
    return width;
}

int Map::getHeight() const{
    return height;
}

void Map::initMap(std::string str){
    char ch;
	Tiletype::State state;
    boxs.clear();
    player.clear();

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            Position pos(j,i);
            Box box(pos);
            ch = str.at(i * width + j);
            state = (Tiletype::State)(ch - '0' + 10);
            Tile tile(state);

			using namespace Tiletype;
            switch (state)
            {
			case State::PLAYER:
                player.setPosition(pos);
                tile.setFlag(Flag::PLAYER);
                break;
            case State::BOX:
            case State::BOX_ON_TARGET:
                boxs.push_back(box);
                tile.setFlag(Flag::BOX);
                break;
            default:
                break;
            }
            tile.setPosition(j,i);
            tileMap[pos] = tile;
        }
    }
}

Tiletype::State Map::getStateOf(const Position& pos) const{
    std::map<Position,Tile>::const_iterator iter;
    iter = tileMap.find(pos);
    if(iter == tileMap.end()){
        return Tiletype::State::FLOOR_OUT_SIDE;
    }
    else {
        return iter->second.getState();
    }
}

void Map::move(Direction::Direction dir){
    Position shadow = player.getPosition();
    shadow += Direction::Coord[dir];

    Tile& prev = getTile(player.getPosition());
    Tile& tile = getTile(shadow);
	using namespace Tiletype;
    switch (tile.getState())
    {
    case State::FLOOR:
    case State::TARGET:
        prev.setFlag(Flag::NONE);
        tile.setFlag(Flag::PLAYER);
        player.move(dir,false);
        break;
    case State::FLOOR_OUT_SIDE:
    case State::WALL:
        break;
    case State::BOX:
    case State::BOX_ON_TARGET:
        moveBox(tile,dir);
        player.move(dir,true);
        prev.setFlag(Flag::NONE);
        tile.setFlag(Flag::PLAYER);
        break;
    
    default:
        break;
    }
}

void Map::back(){
	using namespace Tiletype;
    Direction::Direction dir = player.getPreviousDirection();
    bool flag = player.getPreviousPushFlag();
    Position shadow = player.getPosition();
    Tile& trial = getTile(player.getPosition());
    trial.setFlag(Flag::NONE);
    player.back(dir);
    Tile& trial1 = getTile(player.getPosition());
    trial1.setFlag(Flag::PLAYER);
    shadow += Direction::Coord[dir];
    Tile& trial2 = getTile(shadow);
    State s = trial2.getState();
    if(flag && (s == State::BOX || s == State::BOX_ON_TARGET)){
        Box& b = getBox(shadow,boxs);
        trial2.setFlag(Flag::NONE);
        b.back(dir);
		decreasePush();
        Tile& trial3 = getTile(b.getPosition());
        trial3.setFlag(Flag::BOX);
        b.moveToTile(trial3.getType());
    }
}

const std::vector<Box>& Map::getBoxs() const{
    return boxs;
}

Tile& Map::getTile(const Position& p){
    std::map<Position,Tile>::iterator iter;
    iter = tileMap.find(p);

    if(iter == tileMap.end()){
        return OUT_SIDE_TILE;
    }
    else {
        return iter->second;
    }
}

void Map::moveBox(Tile& situ, Direction::Direction dir){
	using namespace Tiletype;
    Position shadow = situ.getPosition();
    shadow += Direction::Coord[dir];
    Tile& next = getTile(shadow);
    switch (next.getState())
    {
    case State::FLOOR_OUT_SIDE:
    case State::WALL:
    case State::BOX:
    case State::BOX_ON_TARGET:
        return;
    default:
        break;
    }
	increasePush();
    Box& b = getBox(situ.getPosition(),boxs);

    /* record */
    b.move(dir);
    b.moveToTile(next.getType());
    situ.setFlag(Flag::NONE);
    next.setFlag(Flag::BOX);
}

const Position& Map::getPlayerPosition() const{
    return player.getPosition();
}

static Box& getBox(const Position& p, std::vector<Box>& boxs){
    std::vector<Box>::iterator iter;
    for(iter = boxs.begin();iter != boxs.end(); iter++){
        if(iter->getPosition() == p){
            return *iter;
        }
    }
    std::string e("failed to find Box");
    throw e;
}

