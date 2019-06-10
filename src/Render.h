#ifndef _RENDER_H
#define _RENDER_H
#include <string>
#include <ncurses.h>
#include "Map.h"

namespace texts{
	const chtype getSymbol(Tiletype::State n);
	const std::string title = " PUSH_BOX_GAME ";
}

class Screen{
private:
	int width;
	int height;
	int x;
	int y;
	WINDOW *win;
	WINDOW *border;
public:
	int getWidth() const;
	int getHeight() const;
	void setWidth(int w);
	void setHeight(int h);
	WINDOW *getWin() const;
	WINDOW *getBorder() const;
	Screen& operator=(const Screen& s);
	Screen(int l, int c, int _x, int _y);
	~Screen();
	void makeWindow(WINDOW *parent, int color);
	void setWindowBorder(int color);
	void refresh();
};

class Render{
private:
	int w, h;
	Screen *main;
	Screen *panel;
	Screen *game;
public:
	Render(int _w, int _h);
	~Render();
    void init();

	Render& operator=(const Render& r);

    char getInput();
    int getStartLevel();
    void win();
    void finish();

    void displayMap(const Map& m);
	void displayPanel(const Map& m);
};

#endif /* _RENDER_H */
