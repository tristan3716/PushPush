#ifndef ENUMS_H
#define ENUMS_H

namespace Tiletype{
	enum class State{
		BORDER_MAIN = 1,
		BORDER_GAME = 2,
		BORDER_PANEL = 3,
		TITLE_MAIN = 4,
	    FLOOR=10,
	    WALL=11,
	    BOX=12,
	    TARGET=13,
		FLOOR_OUT_SIDE=14,
	    PLAYER=15,
 	    BOX_ON_TARGET=16,
		BLACK = 100
	};

    enum class Flag{
        NONE=9,
		PLAYER=15,
		BOX=12
    };
}

namespace Direction{
    enum Direction{
        UP=0,DOWN=1,LEFT=2,RIGHT=3,SITU=4
    };
}

#endif//ENUMS_H
