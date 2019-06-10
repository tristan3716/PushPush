#ifndef GAME_H
#define GAME_H

#include "Session.h"
#include "Render.h"
#include "LevelParser.h"
#include <ctime>

class Game{
    int curLevel;
    bool isFinish;
    const int MAX_LEVEL;
    clock_t begin,end;
    double duration;
    bool isQuit;
	int total_step;
    Session *curSession;
	Render *v;

    void handleCmd(char ch);
public:
    Game(int level = 0);
    ~Game();

    void start();
	void setTotalStep(int s);
	int getTotalStep() const;

    void initSession();
    void startSession();
    void endSession();
    bool isFinished() const;
    double getDuratione() const;
};

#endif //GAME_H
