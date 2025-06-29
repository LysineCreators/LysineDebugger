# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source file
MAIN_SRC = main.cpp

# Executable
MAIN_EXEC = main.exe

.PHONY: all clean run

# Default target
all: $(MAIN_EXEC)

# Rule to build the main executable
$(MAIN_EXEC): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to clean up generated files
clean:
	-del $(MAIN_EXEC) *.log 2>nul

# Rule to run the executable
run: all
	@echo "Running $(MAIN_EXEC)..."
	@$(MAIN_EXEC)
