#ifndef SESSION_H
#define SESSION_H

#include "Map.h"

namespace RULE{
    bool isWin(const Map& m);
    bool isRightMove(const Map& m, Direction::Direction dir);
}

class Session{
private:
    Map map;
    const int level;
    bool isFinish;
    std::string mapBuffer;
public:
    Session(int width,int height,int l,const std::string& s);
    ~Session();

    void move(Direction::Direction dir);
    const Map& getMap() const;
    void finish();
    bool isFinished() const;
    void backToPreviousPlace();
    void restart();
};

#endif //SESSION_H
