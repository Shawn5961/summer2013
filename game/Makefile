# Makefile for CPU project
SHELL=C:/Windows/System32/cmd.exe
CXX = g++ $(CFLAGS) $(OPTS) $(INC)
INC = -I include/
CFLAGS = -g -static-libgcc -static-libstdc++
LIBS = -lmingw32 -lSDLmain -lSDL -lSDL_image
OPTS =
DEBUG = 
OBJ = main.o functions.o mainmenustate.o worldmapstate.o gameengine.o
LIBRARIES = 
BIN = game.exe  

default: test

debug: CXX += -DDEBUG -g
debug: DEBUG = debug
debug: $(BIN)

test: $(COMPONENTS) $(LIBRARIES) $(OBJ)
	@echo "* Building $(BIN) *"
	$(CXX) $(CFLAGS) -o $(BIN) $(OBJ) $(LIBS)
	@echo
	
clean:
	rm -f *.o $(BIN) core
