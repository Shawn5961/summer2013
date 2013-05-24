# Makefile for CPU project
ARCH = $(shell uname)

ifeq "$(ARCH)" "Linux"
	BIN = game
	LIBS = -lSDLmain -lSDL -lSDL_image
else
	BIN = game.exe
	LIBS = -lmingw32 -lSDLmain -lSDL -lSDL_image
	SHELL = C:/Windows/System32/cmd.exe
endif


CFLAGS = -g -static-libgcc -static-libstdc++
OBJ = main.o functions.o mainmenustate.o worldmapstate.o gameengine.o



default: game

game: $(COMPONENTS) $(LIBRARIES) $(OBJ)
	@echo "* Building $(BIN) *"
	g++ $(CFLAGS) -o $(BIN) $(OBJ) $(LIBS)
	@echo

clean:
	rm -f *.o $(BIN) core