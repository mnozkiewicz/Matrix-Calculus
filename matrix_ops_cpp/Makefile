CXX = g++
CXXFLAGS = -std=c++14 -Iinclude -Wall -Wextra -O2

SRC = $(wildcard src/*.cpp)  # Source files (excluding main.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o) build/main.o  # Object files go to "build/"
EXEC = build/main  # Name of the executable

# Default target
all: build $(EXEC)

# Build the final executable
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)

# Rule for compiling all .cpp files inside "src/"
build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Special rule for compiling main.cpp (since it's not inside "src/")
build/main.o: main.cpp | build
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

# Ensure the build directory exists
build:
	mkdir -p build

# Clean up build files
clean:
	rm -rf build

run: build/main
	build/main

# Phony targets (not associated with files)
.PHONY: all clean run