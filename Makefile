CXX = g++
CXXFLAGS = -g -Wall -pthread -I. -Werror -Wpedantic

PROJ_FILES = $(wildcard *.cpp)

OBJ_FILES = $(PROJ_FILES:.cpp=.o)

all: labwork1

$(OBJ_FILES): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

labwork1: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o labwork1 $(OBJ_FILES)

cleanall:
	rm -f *.o labwork1 Rotated90Clockwise.bmp Rotate90CounterClockwise.bmp GaussianBlur.bmp
