#include "LevelParser.h"

#include <fstream>
#include <iostream>
#include <cstring>

static inline bool isNumber(char ch){
    return (ch <= '9' && ch >= '0');
}
static inline bool isFirstLine(int i){
	return (i == 0);
}
static inline bool isLastLine(std::ifstream& in){
	return (in.eof());
}
static inline std::ifstream openFile(std::string path){
    std::ifstream in(path);
    if(!in.is_open()){
        std::cout<<path<<std::endl;
        std::string e("file open failed");
        throw e;
   }
	return in;
}

using namespace LevelParser;
void Utils::readFile(std::string path, int& w, int& h, std::string& buffer){
	std::ifstream in;
	try{
		in = openFile(path);
	}
	catch(std::string e){
		std::cout << e << std::endl;
		exit(1);
	}
    w = 0;
    h = 0;
    buffer = "";
	
    /* buffer argument */
    const int SIZE = 100;
    char buff[SIZE];

    for(int i = 0; ; i++){
        in.getline(buff,SIZE);
		if (isFirstLine(i)){
			w = strlen(buff);
		}
        std::string temp(buff);
        buffer += temp.substr(0,w);
		if (isLastLine(in)){
			h = i;
			break;		
    	}
	}

    in.close();
}

const LevelBuffer Utils::getLevel(Levels::ID id){
    std::string path = Levels::PATH + Levels::NAME[static_cast<int>(id)];
    int w,h;
    std::string buffer;
	Utils::readFile(path, w, h, buffer);
    return LevelBuffer(w, h, buffer);
}

LevelBuffer::LevelBuffer(int width, int height, const std::string& b):
	w(width),
	h(height),
	buf(b){
}

LevelBuffer::LevelBuffer(const LevelBuffer& mb){
    w = mb.w;
    h = mb.h;
    buf = mb.buf;
}

LevelBuffer& LevelBuffer::operator=(const LevelBuffer& mb){
    w = mb.w;
    h = mb.h;
    buf = mb.buf;
	return *this;
}

const int LevelBuffer::getWidth() const{
    return w;
}

const int LevelBuffer::getHeight() const{
    return h;
}

const std::string& LevelBuffer::getBuffer() const{
    return buf;
}

const std::string LevelBuffer::to_string() const{
    std::string buffer;
    buffer += "(" + std::to_string(w) + "," + std::to_string(h) + ")\n" + buf;
    return buffer;
}

