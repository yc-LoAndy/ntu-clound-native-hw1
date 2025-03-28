CC = g++
CFLAGS = -Wall -Wextra -fsanitize=address -g -std=c++17 -I ./include -I ./include/model
LDFLAGS = -fsanitize=address
SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJ = $(patsubst src/%.cpp,src/%.o,$(SRC))
TARGET = bin/app

all: prepare $(TARGET) clean

prepare:
	@if [ ! -d bin ]; then \
		mkdir bin; \
	fi

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o src/*/*.o

clean-all:
	rm -f src/*.o src/*/*.o
	if [ -d bin ]; then \
		rm -r bin; \
	fi

run:
	$(TARGET)
