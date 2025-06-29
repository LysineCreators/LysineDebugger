# Makefile for Akumade Project

# --- !!! EDIT THIS PATH !!! ---
# Set this to your Boost installation directory.
# The example path is for a vcpkg installation.
BOOST_PATH = C:/Users/CT1105/vcpkg/installed/x64-windows

# --- Compiler and Linker Settings ---

# Compiler
CXX = g++

# Executable name
TARGET = LDP.exe

# Source files
SRCS = main.cpp src/network/network.cpp src/logging/logger.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Compiler flags
# -std=c++17: Use C++17 standard (Beast requires at least C++11, 17 is recommended)
# -Wall: Enable all warnings
# -I: Add directory to include search path
CXXFLAGS = -std=c++17 -Wall -DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0601 -I"$(BOOST_PATH)/include"

# Linker flags
# -L: Add directory to library search path
LDFLAGS = -L"$(BOOST_PATH)/lib"

# Libraries to link
LIBS = -lboost_system-vc143-mt-x64-1_88 -lpthread -lws2_32

# --- Build Rules ---

.PHONY: all clean run

# Default target: build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up built files
clean:
	del "$(TARGET)" "main.o" "src\network\network.o" "src\logging\logger.o" "*.log"

# Rule to run the executable
run: all
	@echo "Running $(TARGET)..."
	@$(TARGET)