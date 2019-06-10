#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include <string>

namespace LevelParser{
	namespace Levels{
    	static const std::string NAME[] = {
        	"1.lv",
        	"2.lv",
        	"3.lv",
        	"4.lv",
        	"5.lv",
        	"6.lv",
        	"7.lv",
        	"8.lv",
        	"9.lv",
        	"myLevel.lv"
    	};

    	static const std::string PATH = "../levels/";

    	enum class ID{
        	Level1 = 1,
        	Level2 = 2,
       		Level3 = 3,
      	 	Level4 = 4,
        	Level5 = 5,
    	    Level6 = 6,
    	    Level7 = 7,
    	    Level8 = 8,
    	    Level9 = 9,
    	    MYLevel = 10
    	};
	}
    class LevelBuffer{
	private:
        int w, h;
        std::string buf;
    public:
        LevelBuffer(int width, int height, const std::string& b);

        LevelBuffer(const LevelBuffer& mb);

        LevelBuffer& operator=(const LevelBuffer& mb);
        
        const int getWidth() const;
        const int getHeight() const;
        const std::string& getBuffer() const;

        const std::string to_string() const;
    };

	namespace Utils{
		void readFile(std::string path, int& w, int& h, std::string& buffer);
    	const LevelBuffer getLevel(Levels::ID id);
	}
};
namespace ParserUtils = LevelParser::Utils;

#endif /* LEVEL_PARSER_H */
