CC = g++

CCFLAGS = -std=c++17 -Wall -Wextra -g

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = sfmltest
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $(TARGET) $(SFML_LIBS)

clean: 
	rm -f $(TARGET)

run: 
	./$(TARGET)

.PHONY: all clean run