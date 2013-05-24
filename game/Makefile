# Makefile for CPU project
ARCH = $(shell uname)
CXX = g++ $(CFLAGS) $(OPTS) $(INC)
INC = -I include/
CFLAGS = -g -static-libgcc -static-libstdc++
OPTS =
DEBUG = 
OBJ = main.o functions.o mainmenustate.o worldmapstate.o gameengine.o
LIBRARIES = 

ifeq ($(shell uname), Linux)
	BIN = game
	LIBS = -lSDLmain -lSDL -lSDL_image
else
	BIN = game.exe
	LIBS = -l mingw32 -lSDLmain -lSDL -lSDL_image
	SHELL=C:/Windows/System32/cmd.exe 
endif

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
