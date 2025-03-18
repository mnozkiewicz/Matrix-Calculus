CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2

SRC = matrix.cpp multiplications.cpp  # Source files
OBJ = $(SRC:.cpp=.o)      # Object files (.o) corresponding to each source (.cpp)
EXEC = matrix_program      # Name of the executable

# The default target, builds the executable
all: $(EXEC)

# building the executable
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)

# Rule for compiling .cpp files to .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files (object files and executable)
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets (not associated with files)
.PHONY: all clean