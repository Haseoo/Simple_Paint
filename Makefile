CC = clang++
OS_NAME := $(shell uname -s)
ifeq ($(OS_NAME),Darwin)
	OBJS = $(shell find src -iname "*.cpp")
endif
ifeq ($(OS_NAME),Linux)
	OBJS = $(shell find $(src/) -name '*.cpp')
endif
COMPILER_FLAGS = -Wall -std=c++11  `pkg-config --cflags --libs gtk+-2.0` `libpng-config --cflags`
LINKER_FLAGS = -lSDL2 `pkg-config --libs gtk+-2.0` `libpng-config --ldflags --libs` 
OBJ_NAME = SimplePaint

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
