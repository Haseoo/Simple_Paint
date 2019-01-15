CC = clang++
OBJS = $(shell find $(src/) -name '*.cpp')
COMPILER_FLAGS = -Wall -std=c++11  `pkg-config --cflags --libs gtk+-2.0` `libpng-config --cflags`
LINKER_FLAGS = -lSDL2 `pkg-config --libs gtk+-2.0` `libpng-config --ldflags --libs` 
OBJ_NAME = SimplePaint

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
