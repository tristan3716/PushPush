#include "Render.h"
#include "Enums.h"
#include "getch.h"

#include <locale.h> // setlocale()
#include <ncurses.h> // console gui library

static const int BLOCK_WIDTH = 2;
static const int BLOCK_HEIGHT = 1;

static inline bool isDirection(char ch){
    return (ch == 'w')||(ch == 's')||(ch == 'a')||(ch == 'd');
}

static inline bool isBuildInCmd(char ch){
    return (ch == 'b')||(ch == 'q')||(ch == 'r');
}

static inline bool isAcceptInput(char ch){
    return isDirection(ch)||isBuildInCmd(ch);
}

const chtype texts::getSymbol(Tiletype::State n){
	using namespace Tiletype;
	switch(n){
		case State::WALL:
			return '#';
		case State::FLOOR:
		case State::FLOOR_OUT_SIDE:
			return ' ';
		case State::BOX:
			return '$';
		case State::TARGET:
			return '%';
		case State::BOX_ON_TARGET:
			return '%';
		case State::PLAYER:
			return '@';
		default:
			return ' ';
	}
}

char Render::getInput(){
    char ret;
    bool accept = false;
    while (!accept) {
		ret = my_getch();
        accept = isAcceptInput(ret);
    }
    return ret;
}

int Render::getStartLevel(){
    int level = 0;
    while(level < '1' || level > '9'){
		level = static_cast<int>(my_getch());
    }
    return level - '0';
}

void Render::displayMap(const Map& map){
	wclear(game->getWin());
	int w = map.getWidth();
    int h = map.getHeight();

    for(int i = 0; i < h*BLOCK_HEIGHT; i++){
        for(int j = 0; j < w*BLOCK_WIDTH; j++){
            Position p(j/BLOCK_WIDTH,i);

			using namespace Tiletype;
			State n = map.getStateOf(p);
			switch(n){
				case State::WALL:
					wattron(game->getWin(), COLOR_PAIR(State::WALL));
					break;
				case State::FLOOR:
				case State::FLOOR_OUT_SIDE:
					wattron(game->getWin(), COLOR_PAIR(State::FLOOR));
					break;
				case State::BOX:
					wattron(game->getWin(), COLOR_PAIR(State::BOX));
					break;
				case State::PLAYER:
					wattron(game->getWin(), COLOR_PAIR(State::PLAYER));
					break;
				case State::TARGET:
					wattron(game->getWin(), COLOR_PAIR(State::TARGET));
					break;
				case State::BOX_ON_TARGET:
					wattron(game->getWin(), COLOR_PAIR(State::BOX_ON_TARGET));
					break;

				default:
					wattron(game->getWin(), COLOR_PAIR(State::FLOOR));
					
			}
			mvwaddch(game->getWin(), 1+i, j+1, texts::getSymbol(n));
		}
		game->refresh();
    }
}

namespace getColorState2Color{
	static inline int c(Tiletype::State s){
		return static_cast<int>(s);
	}
}

void Screen::setWindowBorder(int color){
	wbkgd(border, COLOR_PAIR(color));
	box(border, 0, 0);
	wrefresh(border);
}

void Render::win(){ 
	/* Win Ceremony */
	using Color = Tiletype::State;
	using namespace getColorState2Color;
	for(int i=0; i<6; i++){
		main->setWindowBorder(c(Color::BORDER_GAME));
		panel->setWindowBorder(c(Color::BORDER_GAME));
		usleep(50000);
		main->setWindowBorder(c(Color::BORDER_MAIN));
		game->setWindowBorder(c(Color::BORDER_GAME));
		panel->setWindowBorder(c(Color::BORDER_PANEL));
		usleep(50000);
	}
}

void Screen::makeWindow(WINDOW *parent, int color){
	border = subwin(parent, width, height, x, y);
	setWindowBorder(color);

	win = newwin(width-2, height-2, x+1, y+1);
	wrefresh(getWin());
}

static inline void initColor(void){
		using Color = Tiletype::State;
		using namespace getColorState2Color;
	
		init_pair(c(Color::BORDER_MAIN), COLOR_RED, COLOR_BLACK);
		init_pair(c(Color::BORDER_GAME), COLOR_YELLOW, COLOR_BLACK);
		init_pair(c(Color::BORDER_PANEL), COLOR_WHITE, COLOR_BLACK);
		init_pair(c(Color::TITLE_MAIN), COLOR_WHITE, COLOR_BLACK);
		init_pair(c(Color::BLACK), COLOR_BLACK, COLOR_BLACK);
		init_pair(c(Color::WALL), COLOR_WHITE, COLOR_WHITE);
		init_pair(c(Color::FLOOR), COLOR_BLACK, COLOR_BLACK);
		init_pair(c(Color::TARGET), COLOR_RED, COLOR_BLACK);
		init_pair(c(Color::BOX), COLOR_YELLOW, COLOR_YELLOW);
		init_pair(c(Color::BOX_ON_TARGET), COLOR_RED, COLOR_YELLOW);
		init_pair(c(Color::PLAYER), COLOR_WHITE, COLOR_BLUE);
}

Render::Render(int _w, int _h)
	:w(_w), h(_h){
	setlocale(LC_ALL, "");

	initscr();
	curs_set(0);
	noecho();
	refresh();

	{
		using Color = Tiletype::State;
		using namespace getColorState2Color;
		/* Set Color-set */
		start_color();
		initColor();

		/* Make Window & Set Border*/
		main = new Screen(LINES, COLS, 0, 0);
		main->makeWindow(stdscr, c(Color::BORDER_MAIN));

		game = new Screen(LINES-2, 2*LINES-2, 1, 2);
		game->makeWindow(main->getWin(), c(Color::BORDER_GAME));

		panel = new Screen(LINES-2, COLS-2*LINES-3, 1, 2*LINES+1);
		panel->makeWindow(main->getWin(), c(Color::BORDER_PANEL));

		/* Print Tile */
		wattron(main->getBorder(), COLOR_PAIR(c(Color::TITLE_MAIN)));
		mvwaddstr(main->getBorder(), 0, COLS/2-texts::title.length()/2, texts::title.c_str());
		wrefresh(main->getBorder());
	}
}

Render& Render::operator=(const Render& r){
	main = r.main;
	panel = r.panel;
	game = r.game;
	w = r.w;
	h = r.h;
	return *this;
}

Screen& Screen::operator=(const Screen& s){
	win = s.getWin();
	border = s.getBorder();
	width = s.getWidth();
	height = s.getHeight();
	return *this;
}

void Render::finish(){
	delwin(main->getWin());
	delwin(main->getBorder());
	delwin(game->getWin());
	delwin(game->getBorder());
	delwin(panel->getWin());
	delwin(panel->getBorder());

	endwin();
}

Screen::Screen(int l, int c, int _x, int _y):
	width(l), height(c), x(_x), y(_y){
}

void Screen::refresh(){
	wrefresh(this->win);
	wrefresh(this->border);
}

WINDOW *Screen::getWin() const{
	return win;
}

WINDOW *Screen::getBorder() const{
	return border;
}

int Screen::getWidth() const{
	return width;
}

int Screen::getHeight() const{
	return height;
}

void Render::displayPanel(const Map& m){
	wclear(panel->getWin());
	std::string step;
	step = "- Information -";
	mvwaddstr(panel->getWin(), 0, 1, step.c_str());
	step.clear();

	step = "Step : " + std::to_string(m.getStep());
	mvwaddstr(panel->getWin(), 1, 1, step.c_str());
	step.clear();

	step = "Push : " + std::to_string(m.getPush());
	mvwaddstr(panel->getWin(), 2, 1, step.c_str());
	step.clear();
	
	step = "- Command -\n\n   m o v e\n      w\n    a s d";
	mvwaddstr(panel->getWin(), 5, 1, step.c_str());
	step.clear();

	step = "Undo : b\n   Reset : r\n   Quit : q";
	mvwaddstr(panel->getWin(), 11, 3, step.c_str());


	wrefresh(panel->getWin());
}
