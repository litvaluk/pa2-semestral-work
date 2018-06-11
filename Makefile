.DEFAULT_GOAL = all

CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11
LIBS=-lSDL2 -lSDL2_ttf
EXE_NAME=litvaluk

all: compile doc

compile: bar.o block.o creationstate.o infostate.o gameengine.o item.o \
		main.o menustate.o monster.o player.o playstate.o \
		saveselectionstate.o text.o proximityblock.o
	$(LD) -o $(EXE_NAME) $^ $(LIBS)

compile_sanitized: bar.o block.o creationstate.o infostate.o gameengine.o item.o \
		main.o menustate.o monster.o player.o playstate.o \
		saveselectionstate.o text.o proximityblock.o
	$(LD) -fsanitize=address -o $(EXE_NAME) $^ $(LIBS)

run: compile
	./$(EXE_NAME)

doc:
	doxygen Doxyfile

clean:
	@rm -f bar.o block.o creationstate.o infostate.o gameengine.o item.o \
		main.o menustate.o monster.o player.o playstate.o \
		saveselectionstate.o text.o proximityblock.o mazed *~ core
	@rm -f $(EXE_NAME)
	@rm -rf ./doc

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bar.o: src/bar.cpp src/bar.h src/graphicalobject.h
block.o: src/block.cpp src/block.h src/graphicalobject.h
creationstate.o: src/creationstate.cpp src/gameengine.h src/gamestate.h \
 src/creationstate.h src/block.h src/graphicalobject.h src/text.h \
 src/playstate.h src/player.h src/proximityblock.h src/monster.h \
 src/bar.h src/item.h src/menustate.h
gameengine.o: src/gameengine.cpp src/gameengine.h src/gamestate.h
infostate.o: src/infostate.cpp src/gameengine.h src/gamestate.h \
 src/text.h src/graphicalobject.h src/infostate.h src/menustate.h \
 src/block.h
item.o: src/item.cpp src/item.h
main.o: src/main.cpp src/gameengine.h src/menustate.h src/gamestate.h \
 src/text.h src/graphicalobject.h src/block.h
menustate.o: src/menustate.cpp src/gameengine.h src/gamestate.h \
 src/menustate.h src/text.h src/graphicalobject.h src/block.h \
 src/playstate.h src/player.h src/proximityblock.h src/monster.h \
 src/bar.h src/item.h src/creationstate.h src/saveselectionstate.h
monster.o: src/monster.cpp src/block.h src/graphicalobject.h \
 src/monster.h src/proximityblock.h
player.o: src/player.cpp src/block.h src/graphicalobject.h src/player.h \
 src/proximityblock.h
playstate.o: src/playstate.cpp src/gameengine.h src/gamestate.h \
 src/playstate.h src/block.h src/graphicalobject.h src/player.h \
 src/proximityblock.h src/monster.h src/bar.h src/text.h src/item.h \
 src/menustate.h
proximityblock.o: src/proximityblock.cpp src/block.h \
 src/graphicalobject.h src/proximityblock.h
saveselectionstate.o: src/saveselectionstate.cpp src/gameengine.h \
 src/gamestate.h src/menustate.h src/text.h src/graphicalobject.h \
 src/block.h src/saveselectionstate.h src/playstate.h src/player.h \
 src/proximityblock.h src/monster.h src/bar.h src/item.h \
 src/creationstate.h
text.o: src/text.cpp src/graphicalobject.h src/text.h