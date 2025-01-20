# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall
OBJ = driver.o person.o ABLL.o
TARGET = main.exe

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compiling driver.cpp
driver.o: driver.cpp person.h ABLL.h
	$(CXX) $(CXXFLAGS) -c driver.cpp

# Compiling person.cpp
person.o: person.cpp person.h
	$(CXX) $(CXXFLAGS) -c person.cpp

ABLL.o: ABLL.cpp ABLL.h
	$(CXX) $(CXXFLAGS) -c ABLL.cpp

# Cleaning up generated files
clean:
	del $(OBJ) $(TARGET)
