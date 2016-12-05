CC := g++
FLAGS := -std=c++11 -g
INC_DIR := include
SRC_DIR := src
BIN_DIR := bin
BUILD_DIR := build
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/buildMap.o $(BUILD_DIR)/main.o
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@

$(BUILD_DIR)/buildMap.o: $(SRC_DIR)/buildMap.cpp $(INC_DIR)/buildMap.hpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $< -c -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/Path.hpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $< -c -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
