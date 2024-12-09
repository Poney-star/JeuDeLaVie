CC = g++

CFLAGS = -Wall -g

TARGET = app.exe

SRC = main.cpp graphicsManager.cpp textBox.cpp grid.cpp game.cpp cursor.cpp cell.cpp button.cpp

LIB = -lsfml-graphics -lsfml-window -lsfml-system 

OBJ = $(SRC:.cpp=.o)

run: $(TARGET)
	./$(TARGET)

compile: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIB)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< $(LIB)

.PHONY: clean
clean: 
	rm -f *.o $(TARGET)