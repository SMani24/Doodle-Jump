# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# SFML Libraries
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Directories and Files
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = doodle_jump

# Default rule to build the game
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compiling individual source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)