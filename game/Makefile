# Makefile for CPU project
SHELL=C:/Windows/System32/cmd.exe
CXX = g++ $(CFLAGS) $(OPTS) $(INC)
INC = -I include/
CFLAGS = -g 
LIBS = -lmingw32 -lSDLmain -lSDL -lSDL_image
OPTS =
DEBUG = 
OBJ = test.o mainmenustate.o gameengine.o
LIBRARIES = 
BIN = test  

default: test

debug: CXX += -DDEBUG -g
debug: DEBUG = debug
debug: $(BIN)

test: $(COMPONENTS) $(LIBRARIES) $(OBJ)
	@echo "*****************************************************"
	@echo "*** Building $(BIN)"
	@echo "*****************************************************"
	$(CXX) $(CFLAGS) -o $(BIN) $(OBJ) $(LIBS)
	@echo