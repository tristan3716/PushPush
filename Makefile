CPP=g++
CPPFLAGS=
LDLIBS=-lncursesw
SRCDIR=./src
BINDIR=./bin

.SUFFIXES: .cpp .o .h

SRC = $(wildcard $(SRCDIR)/*.cpp main.cpp)
OBJS = $(addprefix $(BINDIR)/, $(notdir $(SRC:.cpp=.o)))

TARGET = sokoban

all: $(BINDIR)/$(TARGET)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(CPP) $(CPPFLAGS) -c -o $@ $(SRCDIR)/$*.cpp $(LDLIBS) -Wall

$(BINDIR)/main.o: $(SRCDIR)/main.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $? $(LDLIBS)

$(BINDIR)/$(TARGET): $(OBJS)
	$(CPP) -o $@ $(OBJS) $(LDLIBS)

run: $(BINDIR)/$(TARGET)
	(cd $(BINDIR);./$(TARGET))

# DEPENDENCY
$(BINDIR)/Game.o : \
	$(BINDIR)/Session.o $(BINDIR)/Render.o $(BINDIR)/LevelParser.o
$(BINDIR)/LevelParser.o : 
$(BINDIR)/Map.o : $(SRCDIR)/Movable.h $(BINDIR)/Tile.o
$(BINDIR)/Position.o : 
$(BINDIR)/Session.o : $(SRCDIR)/Map.h
$(BINDIR)/Tile.o : $(SRCDIR)/Enums.h $(SRCDIR)/Position.h
$(BINDIR)/Render.o : $(SRCDIR)/getch.h $(SRCDIR)/Enums.h

.PHONY:clean
clean:
	rm -f $(BINDIR)/*

