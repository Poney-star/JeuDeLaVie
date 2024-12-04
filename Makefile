CC = g++

CFLAGS =

TARGET = app

SRC = main.cpp cell.cpp cursor.cpp game.cpp grid.cpp

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