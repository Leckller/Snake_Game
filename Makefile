CXX = g++
CXXFLAGS = -Wall
SRC_DIR = src
BIN_DIR = bin

TARGET = $(BIN_DIR)/snake

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/snake.cpp

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BIN_DIR)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -rf $(BIN_DIR)