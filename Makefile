# Detect operating system
UNAME_S := $(shell uname -s)

# Compiler
CC = g++

# Target executable name
TARGET = main

# Source directories
SRC_DIRS = . headers scenes

# Find all .cpp files
SOURCES = $(wildcard *.cpp headers/*.cpp scenes/*.cpp)

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Platform-specific settings
ifeq ($(UNAME_S),Linux)
    # Linux settings (Arch Linux)
    CFLAGS = -Wall -std=c++11 -Iheaders -I/usr/include -I/usr/local/include
    LDFLAGS = -L/usr/lib -L/usr/local/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    TARGET_EXT =
else ifeq ($(UNAME_S),Windows_NT)
    # Windows settings (MinGW)
    CFLAGS = -Wall -std=c++11 -Iheaders -Iraylib/include
    LDFLAGS = -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET_EXT = .exe
endif

# Default target
all: $(TARGET)$(TARGET_EXT)

# Link object files to create executable
$(TARGET)$(TARGET_EXT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)$(TARGET_EXT) $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
ifeq ($(UNAME_S),Windows_NT)
	del /Q $(OBJECTS) $(TARGET)$(TARGET_EXT)
else
	rm -f $(OBJECTS) $(TARGET)$(TARGET_EXT)
endif

# Phony targets
.PHONY: all clean
