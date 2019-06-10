#include "Game.h"
#include <iostream>

static inline Direction::Direction inputToDirection(char ch){
    switch (ch){
    case 'w':
        return Direction::UP;
    case 's':
        return Direction::DOWN;
    case 'a':
        return Direction::LEFT;
    case 'd':
        return Direction::RIGHT;
    default:
        return Direction::SITU;
    }
}

static inline bool isDirection(char ch){
    return (ch == 'w')||(ch == 's')||(ch == 'a')||(ch == 'd');
}

static inline bool isBuildInCmd(char ch){
    return (ch == 'b')||(ch == 'q')||(ch == 'r');
}

Game::Game(int level/* = 0 */):
	curLevel(level),
	isFinish(false),
	MAX_LEVEL(5),
	total_step(0){
}

Game::~Game(){
}

void Game::start(){
	v = new Render(30, 40);
    int l = 1; // v->getStartLevel();

    if((l >= 1)&&(l <= 9)){
        curLevel = l-1;
    }
    while(!isFinish){
		/* Start Level */
        initSession();
        startSession();
		/* End Level */
        endSession();
    }
    v->finish();
}

void Game::initSession(){
	/* Initialize Session(Level) -> id, level_buffer */
	LevelParser::Levels::ID id = LevelParser::Levels::ID(curLevel);
	LevelParser::LevelBuffer buffer = ParserUtils::getLevel(id);
    curSession = new Session(buffer.getWidth(),buffer.getHeight(),curLevel,buffer.getBuffer());
    isQuit = false;
}

void Game::startSession(){
    begin = std::clock();

    v->displayMap(curSession->getMap());

	/* Until Session is finished */
    while (!curSession->isFinished())
    {
		v->displayPanel(curSession->getMap());
		/* Get Input & Move*/
        char input = v->getInput();
        if(isDirection(input)){
            Direction::Direction dir = inputToDirection(input);
            curSession->move(dir);

            v->displayMap(curSession->getMap());
        }
        else{ /* Non-move Command */
            handleCmd(input);
        }
    }

    if(!isQuit){
        v->win();
    }

    end = std::clock();
    duration += (double)(end - begin)/CLOCKS_PER_SEC;
}

void Game::endSession(){
    delete curSession;
    curSession = nullptr;
    curLevel++;
    if(curLevel >= MAX_LEVEL){
        isFinish= true;
    }
}

bool Game::isFinished() const{
    return isFinish;
}

double Game::getDuratione() const{
    return duration;
}

void Game::handleCmd(char ch){
    switch(ch){
        case 'q':
            isQuit = true;
            isFinish = true;
            curSession->finish();
            break;
        case 'r':
            curSession->restart();
            v->displayMap(curSession->getMap());
            break;
        case 'b':
            curSession->backToPreviousPlace();
            v->displayMap(curSession->getMap());
            break;
        default:
            break;
    }
}

int Game::getTotalStep() const{
	return total_step;
}

void Game::setTotalStep(int s){
	total_step = s;
}
