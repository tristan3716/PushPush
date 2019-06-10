#ifndef MAP_H
#define MAP_H
#include "Movable.h"
#include "Tile.h"
#include <map>

class Map{
private:
    const int width,height;
    Player player;
    std::vector<Box> boxs;
    std::map<Position,Tile> tileMap;
    Tile OUT_SIDE_TILE;

	int step;
	int push;

    Tile& getTile(const Position& p);
    void moveBox(Tile& situ, Direction::Direction dir);

public:
    Map(int w, int h);
    ~Map();
	
	void setStep(int s);
	void setPush(int s);
	void increaseStep();
	void increasePush();
	void decreaseStep();
	void decreasePush();
	int getPush() const;
	int getStep() const;

    int getWidth() const;
    int getHeight() const;
    void initMap(std::string str);

	Tiletype::State getStateOf(const Position& pos) const;
    void move(Direction::Direction dir);
    const std::vector<Box>& getBoxs() const;
    const Position& getPlayerPosition() const;
    void back();
};

#endif //MAP_H
