# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall
OBJ = driver.o person.o
TARGET = main.exe

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compiling driver.cpp
driver.o: driver.cpp person.h
	$(CXX) $(CXXFLAGS) -c driver.cpp

# Compiling person.cpp
person.o: person.cpp person.h
	$(CXX) $(CXXFLAGS) -c person.cpp

# Cleaning up generated files
clean:
	del $(OBJ) $(TARGET)
